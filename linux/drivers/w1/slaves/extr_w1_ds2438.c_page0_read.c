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
typedef  int /*<<< orphan*/  u8 ;
struct w1_slave {TYPE_1__* master; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  bus_mutex; } ;

/* Variables and functions */
 int DS2438_PAGE_SIZE ; 
 int EINVAL ; 
 int EIO ; 
 struct w1_slave* kobj_to_w1_slave (struct kobject*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ **,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ w1_ds2438_get_page (struct w1_slave*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t page0_read(struct file *filp, struct kobject *kobj,
			  struct bin_attribute *bin_attr, char *buf,
			  loff_t off, size_t count)
{
	struct w1_slave *sl = kobj_to_w1_slave(kobj);
	int ret;
	u8 w1_buf[DS2438_PAGE_SIZE + 1 /*for CRC*/];

	if (off != 0)
		return 0;
	if (!buf)
		return -EINVAL;

	mutex_lock(&sl->master->bus_mutex);

	/* Read no more than page0 size */
	if (count > DS2438_PAGE_SIZE)
		count = DS2438_PAGE_SIZE;

	if (w1_ds2438_get_page(sl, 0, w1_buf) == 0) {
		memcpy(buf, &w1_buf, count);
		ret = count;
	} else
		ret = -EIO;

	mutex_unlock(&sl->master->bus_mutex);

	return ret;
}