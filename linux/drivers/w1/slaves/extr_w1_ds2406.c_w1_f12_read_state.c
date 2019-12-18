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
typedef  int u16 ;
struct w1_slave {TYPE_1__* master; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_3__ {int /*<<< orphan*/  bus_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int W1_F12_FUNC_READ_STATUS ; 
 int crc16_byte (int,int) ; 
 struct w1_slave* kobj_to_w1_slave (struct kobject*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w1_read_block (TYPE_1__*,int*,int) ; 
 scalar_t__ w1_reset_select_slave (struct w1_slave*) ; 
 int /*<<< orphan*/  w1_write_block (TYPE_1__*,int*,int) ; 

__attribute__((used)) static ssize_t w1_f12_read_state(
	struct file *filp, struct kobject *kobj,
	struct bin_attribute *bin_attr,
	char *buf, loff_t off, size_t count)
{
	u8 w1_buf[6]={W1_F12_FUNC_READ_STATUS, 7, 0, 0, 0, 0};
	struct w1_slave *sl = kobj_to_w1_slave(kobj);
	u16 crc=0;
	int i;
	ssize_t rtnval=1;

	if (off != 0)
		return 0;
	if (!buf)
		return -EINVAL;

	mutex_lock(&sl->master->bus_mutex);

	if (w1_reset_select_slave(sl)) {
		mutex_unlock(&sl->master->bus_mutex);
		return -EIO;
	}

	w1_write_block(sl->master, w1_buf, 3);
	w1_read_block(sl->master, w1_buf+3, 3);
	for (i=0; i<6; i++)
		crc=crc16_byte(crc, w1_buf[i]);
	if (crc==0xb001) /* good read? */
		*buf=((w1_buf[3]>>5)&3)|0x30;
	else
		rtnval=-EIO;

	mutex_unlock(&sl->master->bus_mutex);

	return rtnval;
}