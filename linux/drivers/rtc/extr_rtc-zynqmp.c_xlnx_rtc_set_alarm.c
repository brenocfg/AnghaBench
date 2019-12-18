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
struct xlnx_rtc_dev {scalar_t__ reg_base; } ;
struct rtc_wkalrm {int /*<<< orphan*/  enabled; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RTC_ALRM ; 
 struct xlnx_rtc_dev* dev_get_drvdata (struct device*) ; 
 unsigned long rtc_tm_to_time64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xlnx_rtc_alarm_irq_enable (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xlnx_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct xlnx_rtc_dev *xrtcdev = dev_get_drvdata(dev);
	unsigned long alarm_time;

	alarm_time = rtc_tm_to_time64(&alrm->time);

	writel((u32)alarm_time, (xrtcdev->reg_base + RTC_ALRM));

	xlnx_rtc_alarm_irq_enable(dev, alrm->enabled);

	return 0;
}