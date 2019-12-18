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
typedef  int /*<<< orphan*/  time64_t ;
struct rtc_time {int dummy; } ;
struct mxc_rtc_data {scalar_t__ ioaddr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SRTC_LPSCMR ; 
 struct mxc_rtc_data* dev_get_drvdata (struct device*) ; 
 int mxc_rtc_lock (struct mxc_rtc_data*) ; 
 int /*<<< orphan*/  mxc_rtc_sync_lp_locked (struct device*,scalar_t__) ; 
 int mxc_rtc_unlock (struct mxc_rtc_data*) ; 
 int /*<<< orphan*/  rtc_tm_to_time64 (struct rtc_time*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mxc_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct mxc_rtc_data *pdata = dev_get_drvdata(dev);
	time64_t time = rtc_tm_to_time64(tm);
	int ret;

	ret = mxc_rtc_lock(pdata);
	if (ret)
		return ret;

	writel(time, pdata->ioaddr + SRTC_LPSCMR);
	mxc_rtc_sync_lp_locked(dev, pdata->ioaddr);
	return mxc_rtc_unlock(pdata);
}