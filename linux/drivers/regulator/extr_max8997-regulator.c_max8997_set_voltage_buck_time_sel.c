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
struct voltage_map_desc {unsigned int step; } ;
struct regulator_dev {int dummy; } ;
struct max8997_data {int ramp_delay; int /*<<< orphan*/  buck5_gpiodvs; int /*<<< orphan*/  buck2_gpiodvs; int /*<<< orphan*/  buck1_gpiodvs; } ;

/* Variables and functions */
 int DIV_ROUND_UP (unsigned int,int) ; 
#define  MAX8997_BUCK1 131 
#define  MAX8997_BUCK2 130 
#define  MAX8997_BUCK4 129 
#define  MAX8997_BUCK5 128 
 struct max8997_data* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 struct voltage_map_desc** reg_voltage_map ; 

__attribute__((used)) static int max8997_set_voltage_buck_time_sel(struct regulator_dev *rdev,
						unsigned int old_selector,
						unsigned int new_selector)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	int rid = rdev_get_id(rdev);
	const struct voltage_map_desc *desc = reg_voltage_map[rid];

	/* Delay is required only if the voltage is increasing */
	if (old_selector >= new_selector)
		return 0;

	/* No need to delay if gpio_dvs_mode */
	switch (rid) {
	case MAX8997_BUCK1:
		if (max8997->buck1_gpiodvs)
			return 0;
		break;
	case MAX8997_BUCK2:
		if (max8997->buck2_gpiodvs)
			return 0;
		break;
	case MAX8997_BUCK5:
		if (max8997->buck5_gpiodvs)
			return 0;
		break;
	}

	switch (rid) {
	case MAX8997_BUCK1:
	case MAX8997_BUCK2:
	case MAX8997_BUCK4:
	case MAX8997_BUCK5:
		return DIV_ROUND_UP(desc->step * (new_selector - old_selector),
				    max8997->ramp_delay * 1000);
	}

	return 0;
}