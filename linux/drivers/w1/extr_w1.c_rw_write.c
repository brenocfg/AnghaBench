#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct w1_slave {TYPE_1__* master; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 struct w1_slave* kobj_to_w1_slave (struct kobject*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ w1_reset_select_slave (struct w1_slave*) ; 
 int /*<<< orphan*/  w1_write_block (TYPE_1__*,char*,size_t) ; 

__attribute__((used)) static ssize_t rw_write(struct file *filp, struct kobject *kobj,
			struct bin_attribute *bin_attr, char *buf, loff_t off,
			size_t count)
{
	struct w1_slave *sl = kobj_to_w1_slave(kobj);

	mutex_lock(&sl->master->mutex);
	if (w1_reset_select_slave(sl)) {
		count = 0;
		goto out_up;
	}

	w1_write_block(sl->master, buf, count);

out_up:
	mutex_unlock(&sl->master->mutex);
	return count;
}