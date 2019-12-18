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
struct da9052_regulator_info {unsigned int activate_bit; } ;
struct da9052_regulator {int /*<<< orphan*/  da9052; struct da9052_regulator_info* info; } ;
struct TYPE_2__ {unsigned int vsel_mask; int /*<<< orphan*/  vsel_reg; } ;

/* Variables and functions */
#define  DA9052_ID_BUCK1 132 
#define  DA9052_ID_BUCK2 131 
#define  DA9052_ID_BUCK3 130 
#define  DA9052_ID_LDO2 129 
#define  DA9052_ID_LDO3 128 
 int /*<<< orphan*/  DA9052_SUPPLY_REG ; 
 int da9052_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct da9052_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int da9052_regulator_set_voltage_sel(struct regulator_dev *rdev,
					    unsigned int selector)
{
	struct da9052_regulator *regulator = rdev_get_drvdata(rdev);
	struct da9052_regulator_info *info = regulator->info;
	int id = rdev_get_id(rdev);
	int ret;

	ret = da9052_reg_update(regulator->da9052, rdev->desc->vsel_reg,
				rdev->desc->vsel_mask, selector);
	if (ret < 0)
		return ret;

	/* Some LDOs and DCDCs are DVC controlled which requires enabling of
	 * the activate bit to implment the changes on the output.
	 */
	switch (id) {
	case DA9052_ID_BUCK1:
	case DA9052_ID_BUCK2:
	case DA9052_ID_BUCK3:
	case DA9052_ID_LDO2:
	case DA9052_ID_LDO3:
		ret = da9052_reg_update(regulator->da9052, DA9052_SUPPLY_REG,
					info->activate_bit, info->activate_bit);
		break;
	}

	return ret;
}