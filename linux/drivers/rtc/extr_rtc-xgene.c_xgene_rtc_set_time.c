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
typedef  int /*<<< orphan*/  u32 ;
struct xgene_rtc_dev {scalar_t__ csr_base; } ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RTC_CLR ; 
 struct xgene_rtc_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 scalar_t__ rtc_tm_to_time64 (struct rtc_time*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int xgene_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct xgene_rtc_dev *pdata = dev_get_drvdata(dev);

	/*
	 * NOTE: After the following write, the RTC_CCVR is only reflected
	 *       after the update cycle of 1 seconds.
	 */
	writel((u32)rtc_tm_to_time64(tm), pdata->csr_base + RTC_CLR);
	readl(pdata->csr_base + RTC_CLR); /* Force a barrier */

	return 0;
}