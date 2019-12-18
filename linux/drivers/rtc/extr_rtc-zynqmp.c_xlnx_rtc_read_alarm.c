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
struct xlnx_rtc_dev {scalar_t__ reg_base; } ;
struct rtc_wkalrm {int enabled; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RTC_ALRM ; 
 int RTC_INT_ALRM ; 
 scalar_t__ RTC_INT_MASK ; 
 struct xlnx_rtc_dev* dev_get_drvdata (struct device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xlnx_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct xlnx_rtc_dev *xrtcdev = dev_get_drvdata(dev);

	rtc_time64_to_tm(readl(xrtcdev->reg_base + RTC_ALRM), &alrm->time);
	alrm->enabled = readl(xrtcdev->reg_base + RTC_INT_MASK) & RTC_INT_ALRM;

	return 0;
}