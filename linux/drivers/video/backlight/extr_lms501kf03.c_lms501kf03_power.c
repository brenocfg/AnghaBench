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
struct lms501kf03 {int power; } ;

/* Variables and functions */
 scalar_t__ lms501kf03_power_is_on (int) ; 
 int lms501kf03_power_off (struct lms501kf03*) ; 
 int lms501kf03_power_on (struct lms501kf03*) ; 

__attribute__((used)) static int lms501kf03_power(struct lms501kf03 *lcd, int power)
{
	int ret = 0;

	if (lms501kf03_power_is_on(power) &&
		!lms501kf03_power_is_on(lcd->power))
		ret = lms501kf03_power_on(lcd);
	else if (!lms501kf03_power_is_on(power) &&
		lms501kf03_power_is_on(lcd->power))
		ret = lms501kf03_power_off(lcd);

	if (!ret)
		lcd->power = power;

	return ret;
}