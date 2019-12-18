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
typedef  scalar_t__ u8 ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int RTC_AF ; 
 int RTC_IRQF ; 
 scalar_t__ SC_IRQ_GROUP_RTC ; 
 unsigned long SC_IRQ_RTC ; 
 int /*<<< orphan*/  imx_sc_rtc ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int imx_sc_rtc_alarm_notify(struct notifier_block *nb,
					unsigned long event, void *group)
{
	/* ignore non-rtc irq */
	if (!((event & SC_IRQ_RTC) && (*(u8 *)group == SC_IRQ_GROUP_RTC)))
		return 0;

	rtc_update_irq(imx_sc_rtc, 1, RTC_IRQF | RTC_AF);

	return 0;
}