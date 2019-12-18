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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SC_IRQ_GROUP_RTC ; 
 int /*<<< orphan*/  SC_IRQ_RTC ; 
 int imx_scu_irq_group_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int imx_sc_rtc_alarm_irq_enable(struct device *dev, unsigned int enable)
{
	return imx_scu_irq_group_enable(SC_IRQ_GROUP_RTC, SC_IRQ_RTC, enable);
}