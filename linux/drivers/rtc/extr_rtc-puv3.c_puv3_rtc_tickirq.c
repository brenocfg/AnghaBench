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
struct rtc_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RTC_IRQF ; 
 int RTC_PF ; 
 int /*<<< orphan*/  RTC_RTSR ; 
 int RTC_RTSR_HZ ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_update_irq (struct rtc_device*,int,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t puv3_rtc_tickirq(int irq, void *id)
{
	struct rtc_device *rdev = id;

	writel(readl(RTC_RTSR) | RTC_RTSR_HZ, RTC_RTSR);
	rtc_update_irq(rdev, 1, RTC_PF | RTC_IRQF);
	return IRQ_HANDLED;
}