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
struct spmi_regulator {int /*<<< orphan*/  slew_rate; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int abs (scalar_t__) ; 
 struct spmi_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 scalar_t__ spmi_regulator_common_list_voltage (struct regulator_dev*,unsigned int) ; 

__attribute__((used)) static int spmi_regulator_set_voltage_time_sel(struct regulator_dev *rdev,
		unsigned int old_selector, unsigned int new_selector)
{
	struct spmi_regulator *vreg = rdev_get_drvdata(rdev);
	int diff_uV;

	diff_uV = abs(spmi_regulator_common_list_voltage(rdev, new_selector) -
		      spmi_regulator_common_list_voltage(rdev, old_selector));

	return DIV_ROUND_UP(diff_uV, vreg->slew_rate);
}