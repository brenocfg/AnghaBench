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
struct regulator_dev {int dummy; } ;
struct da9052_regulator_info {unsigned int step_uV; unsigned int min_uV; int max_uV; } ;
struct da9052_regulator {TYPE_1__* da9052; struct da9052_regulator_info* info; } ;
struct TYPE_2__ {scalar_t__ chip_id; } ;

/* Variables and functions */
 scalar_t__ DA9052 ; 
 unsigned int DA9052_BUCK_PERI_3uV_STEP ; 
 unsigned int DA9052_BUCK_PERI_REG_MAP_UPTO_3uV ; 
 int DA9052_ID_BUCK4 ; 
 int EINVAL ; 
 struct da9052_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int da9052_list_voltage(struct regulator_dev *rdev,
				unsigned int selector)
{
	struct da9052_regulator *regulator = rdev_get_drvdata(rdev);
	struct da9052_regulator_info *info = regulator->info;
	int id = rdev_get_id(rdev);
	int volt_uV;

	if ((id == DA9052_ID_BUCK4) && (regulator->da9052->chip_id == DA9052)
		&& (selector >= DA9052_BUCK_PERI_REG_MAP_UPTO_3uV)) {
		volt_uV = ((DA9052_BUCK_PERI_REG_MAP_UPTO_3uV * info->step_uV)
			  + info->min_uV);
		volt_uV += (selector - DA9052_BUCK_PERI_REG_MAP_UPTO_3uV)
				    * (DA9052_BUCK_PERI_3uV_STEP);
	} else {
		volt_uV = (selector * info->step_uV) + info->min_uV;
	}

	if (volt_uV > info->max_uV)
		return -EINVAL;

	return volt_uV;
}