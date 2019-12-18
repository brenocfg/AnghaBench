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
struct msc {scalar_t__ mode; int /*<<< orphan*/  buf_mutex; scalar_t__ mbuf; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 scalar_t__ MSC_MODE_MULTI ; 
 struct msc* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  msc_win_switch (struct msc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
win_switch_store(struct device *dev, struct device_attribute *attr,
		 const char *buf, size_t size)
{
	struct msc *msc = dev_get_drvdata(dev);
	unsigned long val;
	int ret;

	ret = kstrtoul(buf, 10, &val);
	if (ret)
		return ret;

	if (val != 1)
		return -EINVAL;

	mutex_lock(&msc->buf_mutex);
	/*
	 * Window switch can only happen in the "multi" mode.
	 * If a external buffer is engaged, they have the full
	 * control over window switching.
	 */
	if (msc->mode != MSC_MODE_MULTI || msc->mbuf)
		ret = -ENOTSUPP;
	else
		msc_win_switch(msc);
	mutex_unlock(&msc->buf_mutex);

	return ret ? ret : size;
}