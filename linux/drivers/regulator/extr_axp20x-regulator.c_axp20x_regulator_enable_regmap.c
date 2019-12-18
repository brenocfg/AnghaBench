#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {TYPE_1__* constraints; } ;
struct axp20x_dev {int variant; } ;
struct TYPE_2__ {int /*<<< orphan*/  soft_start; } ;

/* Variables and functions */
#define  AXP209_ID 128 
 int AXP20X_LDO3 ; 
 struct axp20x_dev* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regulator_enable_regmap (struct regulator_dev*) ; 
 int regulator_get_voltage_sel_regmap (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_is_enabled_regmap (struct regulator_dev*) ; 
 int regulator_set_voltage_sel_regmap (struct regulator_dev*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int axp20x_regulator_enable_regmap(struct regulator_dev *rdev)
{
	struct axp20x_dev *axp20x = rdev_get_drvdata(rdev);
	int id = rdev_get_id(rdev);

	switch (axp20x->variant) {
	case AXP209_ID:
		if ((id == AXP20X_LDO3) &&
		    rdev->constraints && rdev->constraints->soft_start) {
			int v_out;
			int ret;

			/*
			 * On some boards, the LDO3 can be overloaded when
			 * turning on, causing the entire PMIC to shutdown
			 * without warning. Turning it on at the minimal voltage
			 * and then setting the voltage to the requested value
			 * works reliably.
			 */
			if (regulator_is_enabled_regmap(rdev))
				break;

			v_out = regulator_get_voltage_sel_regmap(rdev);
			if (v_out < 0)
				return v_out;

			if (v_out == 0)
				break;

			ret = regulator_set_voltage_sel_regmap(rdev, 0x00);
			/*
			 * A small pause is needed between
			 * setting the voltage and enabling the LDO to give the
			 * internal state machine time to process the request.
			 */
			usleep_range(1000, 5000);
			ret |= regulator_enable_regmap(rdev);
			ret |= regulator_set_voltage_sel_regmap(rdev, v_out);

			return ret;
		}
		break;
	default:
		/* No quirks */
		break;
	}

	return regulator_enable_regmap(rdev);
}