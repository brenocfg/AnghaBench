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
struct TYPE_2__ {int /*<<< orphan*/  sel_mask; int /*<<< orphan*/  reg; } ;
struct da9055_regulator_info {TYPE_1__ conf; } ;
struct da9055_regulator {scalar_t__ reg_rselect; int /*<<< orphan*/  da9055; struct da9055_regulator_info* info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9055_SEL_REG_A ; 
 scalar_t__ NO_GPIO ; 
 int da9055_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct da9055_regulator* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int da9055_suspend_disable(struct regulator_dev *rdev)
{
	struct da9055_regulator *regulator = rdev_get_drvdata(rdev);
	struct da9055_regulator_info *info = regulator->info;

	/* Diselect register set B. */
	if (regulator->reg_rselect == NO_GPIO)
		return da9055_reg_update(regulator->da9055, info->conf.reg,
					info->conf.sel_mask, DA9055_SEL_REG_A);
	else
		return 0;
}