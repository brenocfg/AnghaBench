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
typedef  int /*<<< orphan*/  u8 ;
struct palmas {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  PALMAS_RTC_BASE ; 
 int /*<<< orphan*/  PALMAS_RTC_INTERRUPTS_REG ; 
 int /*<<< orphan*/  PALMAS_RTC_INTERRUPTS_REG_IT_ALARM ; 
 struct palmas* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int palmas_write (struct palmas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int palmas_rtc_alarm_irq_enable(struct device *dev, unsigned enabled)
{
	struct palmas *palmas = dev_get_drvdata(dev->parent);
	u8 val;

	val = enabled ? PALMAS_RTC_INTERRUPTS_REG_IT_ALARM : 0;
	return palmas_write(palmas, PALMAS_RTC_BASE,
		PALMAS_RTC_INTERRUPTS_REG, val);
}