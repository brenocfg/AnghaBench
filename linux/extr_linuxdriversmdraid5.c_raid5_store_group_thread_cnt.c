#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct r5worker_group {struct r5worker_group* workers; } ;
struct r5conf {unsigned int worker_cnt_per_group; int group_cnt; int /*<<< orphan*/  device_lock; struct r5worker_group* worker_groups; } ;
struct mddev {struct r5conf* private; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 size_t PAGE_SIZE ; 
 int alloc_thread_groups (struct r5conf*,unsigned int,int*,int*,struct r5worker_group**) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct r5worker_group*) ; 
 scalar_t__ kstrtouint (char const*,int,unsigned int*) ; 
 int mddev_lock (struct mddev*) ; 
 int /*<<< orphan*/  mddev_resume (struct mddev*) ; 
 int /*<<< orphan*/  mddev_suspend (struct mddev*) ; 
 int /*<<< orphan*/  mddev_unlock (struct mddev*) ; 
 int /*<<< orphan*/  raid5_wq ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
raid5_store_group_thread_cnt(struct mddev *mddev, const char *page, size_t len)
{
	struct r5conf *conf;
	unsigned int new;
	int err;
	struct r5worker_group *new_groups, *old_groups;
	int group_cnt, worker_cnt_per_group;

	if (len >= PAGE_SIZE)
		return -EINVAL;
	if (kstrtouint(page, 10, &new))
		return -EINVAL;
	/* 8192 should be big enough */
	if (new > 8192)
		return -EINVAL;

	err = mddev_lock(mddev);
	if (err)
		return err;
	conf = mddev->private;
	if (!conf)
		err = -ENODEV;
	else if (new != conf->worker_cnt_per_group) {
		mddev_suspend(mddev);

		old_groups = conf->worker_groups;
		if (old_groups)
			flush_workqueue(raid5_wq);

		err = alloc_thread_groups(conf, new,
					  &group_cnt, &worker_cnt_per_group,
					  &new_groups);
		if (!err) {
			spin_lock_irq(&conf->device_lock);
			conf->group_cnt = group_cnt;
			conf->worker_cnt_per_group = worker_cnt_per_group;
			conf->worker_groups = new_groups;
			spin_unlock_irq(&conf->device_lock);

			if (old_groups)
				kfree(old_groups[0].workers);
			kfree(old_groups);
		}
		mddev_resume(mddev);
	}
	mddev_unlock(mddev);

	return err ?: len;
}