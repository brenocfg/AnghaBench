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
 unsigned int MAX77802_RTC_DATE ; 
 unsigned int MAX77802_RTC_HOUR ; 
 unsigned int MAX77802_RTC_MIN ; 
 unsigned int MAX77802_RTC_MONTH ; 
 unsigned int MAX77802_RTC_SEC ; 
 unsigned int MAX77802_RTC_WEEKDAY ; 
 unsigned int MAX77802_RTC_YEAR ; 
 scalar_t__ max77802_rtc_is_precious_reg (struct device*,unsigned int) ; 

__attribute__((used)) static bool max77802_rtc_is_volatile_reg(struct device *dev, unsigned int reg)
{
	return (max77802_rtc_is_precious_reg(dev, reg) ||
		reg == MAX77802_RTC_SEC ||
		reg == MAX77802_RTC_MIN ||
		reg == MAX77802_RTC_HOUR ||
		reg == MAX77802_RTC_WEEKDAY ||
		reg == MAX77802_RTC_MONTH ||
		reg == MAX77802_RTC_YEAR ||
		reg == MAX77802_RTC_DATE);
}