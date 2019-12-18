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
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  W1_1C_REG_LOGIC_STATE ; 
 struct w1_slave* kobj_to_w1_slave (struct kobject*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int w1_f1C_read (struct w1_slave*,int /*<<< orphan*/ ,size_t,char*) ; 

__attribute__((used)) static ssize_t pio_read(struct file *filp, struct kobject *kobj,
			struct bin_attribute *bin_attr, char *buf, loff_t off,
			size_t count)

{
	struct w1_slave *sl = kobj_to_w1_slave(kobj);
	int ret;

	/* check arguments */
	if (off != 0 || count != 1 || buf == NULL)
		return -EINVAL;

	mutex_lock(&sl->master->mutex);
	ret = w1_f1C_read(sl, W1_1C_REG_LOGIC_STATE, count, buf);
	mutex_unlock(&sl->master->mutex);

	return ret;
}