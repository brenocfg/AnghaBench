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
struct mxc_rtc_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct mxc_rtc_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mxc_rtc_alarm_irq_enable_locked (struct mxc_rtc_data*,unsigned int) ; 
 int mxc_rtc_lock (struct mxc_rtc_data*) ; 
 int mxc_rtc_unlock (struct mxc_rtc_data*) ; 

__attribute__((used)) static int mxc_rtc_alarm_irq_enable(struct device *dev, unsigned int enable)
{
	struct mxc_rtc_data *pdata = dev_get_drvdata(dev);
	int ret = mxc_rtc_lock(pdata);

	if (ret)
		return ret;

	mxc_rtc_alarm_irq_enable_locked(pdata, enable);
	return mxc_rtc_unlock(pdata);
}