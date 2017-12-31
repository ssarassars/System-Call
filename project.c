#include <linux/module.h> // Must be included in all kernel modules
#include <linux/init.h> // Needed for specifying the initialization and cleanup functions
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include <linux/time.h>
#include <linux/sysinfo.h>
#include <linux/string.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL"); // If your module isn't GPL-licensed, it will "taint" the kernel
MODULE_AUTHOR("3000 Project");
MODULE_DESCRIPTION("USER INFORMATION SECURITY MODULE");

static int __init user_init(void)
{
int i;

 for(i=0; i<3; i++){

        struct timeval timeOfDay;
        struct task_struct *task;
        struct tm tv2;
        int tmp3, tmp2, tmp1, date, count=0;
        
        for_each_process(task){
              count++;
              printk(KERN_INFO "pid: %d | pname: %s | state: %ld\n", task->pid, task->comm, task->state);
        }
         
        printk("Number of Processes: %d\n", count);

	do_gettimeofday(&timeOfDay);
	time_to_tm(timeOfDay.tv_sec, 0, &tv2);

	printk(KERN_INFO "Current User ID: %d\n", get_current_user()->uid.val);

        printk("TIME: %.2lu:%.2lu:%.2lu \r\n",
                   (timeOfDay.tv_sec / 3600) % (24) - 4,
                   (timeOfDay.tv_sec / 60) % (60),
                   timeOfDay.tv_sec % 60);

	tmp3 = tv2.tm_year;
        tmp2 = tv2.tm_mon;
        tmp1 = tv2.tm_yday;
      
        date = tmp1%30;

        printk(KERN_INFO "Year: %d\n Month: %d\n Day: %d\n", tmp3 + 1900, tmp2 + 1, date + 1);
        msleep(5000);
}

        return 0;
}

static void __exit user_exit(void)
{
        printk(KERN_INFO "Exiting USER module.\n");
}

module_init(user_init);
module_exit(user_exit);
