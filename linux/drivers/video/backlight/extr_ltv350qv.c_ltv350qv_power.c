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
struct ltv350qv {int power; } ;

/* Variables and functions */
 scalar_t__ POWER_IS_ON (int) ; 
 int ltv350qv_power_off (struct ltv350qv*) ; 
 int ltv350qv_power_on (struct ltv350qv*) ; 

__attribute__((used)) static int ltv350qv_power(struct ltv350qv *lcd, int power)
{
	int ret = 0;

	if (POWER_IS_ON(power) && !POWER_IS_ON(lcd->power))
		ret = ltv350qv_power_on(lcd);
	else if (!POWER_IS_ON(power) && POWER_IS_ON(lcd->power))
		ret = ltv350qv_power_off(lcd);

	if (!ret)
		lcd->power = power;

	return ret;
}