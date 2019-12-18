#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
struct w1_slave {TYPE_1__* master; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  bus_mutex; } ;

/* Variables and functions */
 int EFAULT ; 
 int EIO ; 
 char W1_F29_FUNC_READ_PIO_REGS ; 
 char W1_F29_FUNC_WRITE_COND_SEARCH_REG ; 
 char W1_F29_REG_CONTROL_AND_STATUS ; 
 unsigned int W1_F29_RETRIES ; 
 struct w1_slave* kobj_to_w1_slave (struct kobject*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 char w1_read_8 (TYPE_1__*) ; 
 scalar_t__ w1_reset_resume_command (TYPE_1__*) ; 
 scalar_t__ w1_reset_select_slave (struct w1_slave*) ; 
 int /*<<< orphan*/  w1_write_block (TYPE_1__*,char*,int) ; 

__attribute__((used)) static ssize_t status_control_write(struct file *filp, struct kobject *kobj,
				    struct bin_attribute *bin_attr, char *buf,
				    loff_t off, size_t count)
{
	struct w1_slave *sl = kobj_to_w1_slave(kobj);
	u8 w1_buf[4];
	unsigned int retries = W1_F29_RETRIES;

	if (count != 1 || off != 0)
		return -EFAULT;

	mutex_lock(&sl->master->bus_mutex);

	if (w1_reset_select_slave(sl))
		goto error;

	while (retries--) {
		w1_buf[0] = W1_F29_FUNC_WRITE_COND_SEARCH_REG;
		w1_buf[1] = W1_F29_REG_CONTROL_AND_STATUS;
		w1_buf[2] = 0;
		w1_buf[3] = *buf;

		w1_write_block(sl->master, w1_buf, 4);
		if (w1_reset_resume_command(sl->master))
			goto error;

		w1_buf[0] = W1_F29_FUNC_READ_PIO_REGS;
		w1_buf[1] = W1_F29_REG_CONTROL_AND_STATUS;
		w1_buf[2] = 0;

		w1_write_block(sl->master, w1_buf, 3);
		if (w1_read_8(sl->master) == *buf) {
			/* success! */
			mutex_unlock(&sl->master->bus_mutex);
			return 1;
		}
	}
error:
	mutex_unlock(&sl->master->bus_mutex);

	return -EIO;
}