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
struct da9052_battery {int /*<<< orphan*/  da9052; } ;

/* Variables and functions */
 int DA9052_BAT_TSH ; 
 int da9052_adc_read_temp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9052_bat_check_presence(struct da9052_battery *bat, int *illegal)
{
	int bat_temp;

	bat_temp = da9052_adc_read_temp(bat->da9052);
	if (bat_temp < 0)
		return bat_temp;

	if (bat_temp > DA9052_BAT_TSH)
		*illegal = 1;
	else
		*illegal = 0;

	return 0;
}