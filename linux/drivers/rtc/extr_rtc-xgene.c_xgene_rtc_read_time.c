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
struct xgene_rtc_dev {scalar_t__ csr_base; } ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RTC_CCVR ; 
 struct xgene_rtc_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (int /*<<< orphan*/ ,struct rtc_time*) ; 

__attribute__((used)) static int xgene_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct xgene_rtc_dev *pdata = dev_get_drvdata(dev);

	rtc_time64_to_tm(readl(pdata->csr_base + RTC_CCVR), tm);
	return 0;
}