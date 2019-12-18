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
 int /*<<< orphan*/  AB8500_RTC ; 
 int /*<<< orphan*/  AB8500_RTC_STAT_REG ; 
 int /*<<< orphan*/  RTC_ALARM_ENA ; 
 int abx500_mask_and_set_register_interruptible (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ab8500_rtc_irq_enable(struct device *dev, unsigned int enabled)
{
	return abx500_mask_and_set_register_interruptible(dev, AB8500_RTC,
		AB8500_RTC_STAT_REG, RTC_ALARM_ENA,
		enabled ? RTC_ALARM_ENA : 0);
}