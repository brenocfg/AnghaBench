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
struct regulator {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int EINVAL ; 
 int regulator_list_voltage (struct regulator*,int) ; 

__attribute__((used)) static int led_regulator_get_voltage(struct regulator *supply,
		enum led_brightness brightness)
{
	if (brightness == 0)
		return -EINVAL;

	return regulator_list_voltage(supply, brightness - 1);
}