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

/* Variables and functions */
 int regulator_count_voltages (struct regulator*) ; 
 int regulator_list_voltage (struct regulator*,int /*<<< orphan*/ ) ; 
 int regulator_set_voltage (struct regulator*,int,int) ; 

__attribute__((used)) static inline int led_regulator_get_max_brightness(struct regulator *supply)
{
	int ret;
	int voltage = regulator_list_voltage(supply, 0);

	if (voltage <= 0)
		return 1;

	/* even if regulator can't change voltages,
	 * we still assume it can change status
	 * and the LED can be turned on and off.
	 */
	ret = regulator_set_voltage(supply, voltage, voltage);
	if (ret < 0)
		return 1;

	return regulator_count_voltages(supply);
}