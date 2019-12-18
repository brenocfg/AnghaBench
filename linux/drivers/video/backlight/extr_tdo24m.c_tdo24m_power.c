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
struct tdo24m {int power; } ;

/* Variables and functions */
 scalar_t__ POWER_IS_ON (int) ; 
 int tdo24m_power_off (struct tdo24m*) ; 
 int tdo24m_power_on (struct tdo24m*) ; 

__attribute__((used)) static int tdo24m_power(struct tdo24m *lcd, int power)
{
	int ret = 0;

	if (POWER_IS_ON(power) && !POWER_IS_ON(lcd->power))
		ret = tdo24m_power_on(lcd);
	else if (!POWER_IS_ON(power) && POWER_IS_ON(lcd->power))
		ret = tdo24m_power_off(lcd);

	if (!ret)
		lcd->power = power;

	return ret;
}