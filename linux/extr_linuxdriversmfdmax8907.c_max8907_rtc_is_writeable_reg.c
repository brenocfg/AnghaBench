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
#define  MAX8907_REG_RTC_IRQ 129 
#define  MAX8907_REG_RTC_STATUS 128 

__attribute__((used)) static bool max8907_rtc_is_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case MAX8907_REG_RTC_STATUS:
	case MAX8907_REG_RTC_IRQ:
		return false;
	default:
		return true;
	}
}