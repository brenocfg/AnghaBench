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
struct ili9320 {int power; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ POWER_IS_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int ili9320_power_off (struct ili9320*) ; 
 int ili9320_power_on (struct ili9320*) ; 

__attribute__((used)) static int ili9320_power(struct ili9320 *lcd, int power)
{
	int ret = 0;

	dev_dbg(lcd->dev, "power %d => %d\n", lcd->power, power);

	if (POWER_IS_ON(power) && !POWER_IS_ON(lcd->power))
		ret = ili9320_power_on(lcd);
	else if (!POWER_IS_ON(power) && POWER_IS_ON(lcd->power))
		ret = ili9320_power_off(lcd);

	if (ret == 0)
		lcd->power = power;
	else
		dev_warn(lcd->dev, "failed to set power mode %d\n", power);

	return ret;
}