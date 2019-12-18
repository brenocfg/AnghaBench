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
struct regulator_dev {TYPE_1__* desc; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {int n_voltages; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_LDO1_CONTROL_2 ; 
 unsigned int ARIZONA_LDO1_HI_PWR ; 
 struct regmap* rdev_get_regmap (struct regulator_dev*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int regulator_set_voltage_sel_regmap (struct regulator_dev*,unsigned int) ; 

__attribute__((used)) static int arizona_ldo1_hc_set_voltage_sel(struct regulator_dev *rdev,
					   unsigned sel)
{
	struct regmap *regmap = rdev_get_regmap(rdev);
	unsigned int val;
	int ret;

	if (sel == rdev->desc->n_voltages - 1)
		val = ARIZONA_LDO1_HI_PWR;
	else
		val = 0;

	ret = regmap_update_bits(regmap, ARIZONA_LDO1_CONTROL_2,
				 ARIZONA_LDO1_HI_PWR, val);
	if (ret != 0)
		return ret;

	if (val)
		return 0;

	return regulator_set_voltage_sel_regmap(rdev, sel);
}