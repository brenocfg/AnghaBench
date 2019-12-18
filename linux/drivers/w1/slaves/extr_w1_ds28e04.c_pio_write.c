#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct w1_slave {TYPE_1__* master; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  ack ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int W1_F1C_ACCESS_WRITE ; 
 struct w1_slave* kobj_to_w1_slave (struct kobject*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w1_read_block (TYPE_1__*,int*,int) ; 
 scalar_t__ w1_reset_select_slave (struct w1_slave*) ; 
 int /*<<< orphan*/  w1_write_block (TYPE_1__*,int*,int) ; 

__attribute__((used)) static ssize_t pio_write(struct file *filp, struct kobject *kobj,
			 struct bin_attribute *bin_attr, char *buf, loff_t off,
			 size_t count)

{
	struct w1_slave *sl = kobj_to_w1_slave(kobj);
	u8 wrbuf[3];
	u8 ack;

	/* check arguments */
	if (off != 0 || count != 1 || buf == NULL)
		return -EINVAL;

	mutex_lock(&sl->master->mutex);

	/* Write the PIO data */
	if (w1_reset_select_slave(sl)) {
		mutex_unlock(&sl->master->mutex);
		return -1;
	}

	/* set bit 7..2 to value '1' */
	*buf = *buf | 0xFC;

	wrbuf[0] = W1_F1C_ACCESS_WRITE;
	wrbuf[1] = *buf;
	wrbuf[2] = ~(*buf);
	w1_write_block(sl->master, wrbuf, 3);

	w1_read_block(sl->master, &ack, sizeof(ack));

	mutex_unlock(&sl->master->mutex);

	/* check for acknowledgement */
	if (ack != 0xAA)
		return -EIO;

	return count;
}