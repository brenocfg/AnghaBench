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
struct rc5t583 {int /*<<< orphan*/  regmap; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  RC5T583_RTC_CTL1 ; 
 int /*<<< orphan*/  SET_YAL ; 
 struct rc5t583* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rc5t583_rtc_alarm_irq_enable(struct device *dev, unsigned enabled)
{
	struct rc5t583 *rc5t583 = dev_get_drvdata(dev->parent);
	u8 val;

	/* Set Y-Alarm, based on 'enabled' */
	val = enabled ? SET_YAL : 0;

	return regmap_update_bits(rc5t583->regmap, RC5T583_RTC_CTL1, SET_YAL,
		val);
}