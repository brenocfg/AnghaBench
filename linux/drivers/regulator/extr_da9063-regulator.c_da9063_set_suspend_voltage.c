#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {TYPE_2__* desc; } ;
struct da9063_regulator_info {int /*<<< orphan*/  suspend_vsel_reg; } ;
struct da9063_regulator {TYPE_1__* hw; struct da9063_regulator_info* info; } ;
struct TYPE_4__ {int /*<<< orphan*/  vsel_mask; } ;
struct TYPE_3__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ffs (int /*<<< orphan*/ ) ; 
 struct da9063_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int regulator_map_voltage_linear (struct regulator_dev*,int,int) ; 

__attribute__((used)) static int da9063_set_suspend_voltage(struct regulator_dev *rdev, int uV)
{
	struct da9063_regulator *regl = rdev_get_drvdata(rdev);
	const struct da9063_regulator_info *rinfo = regl->info;
	int ret, sel;

	sel = regulator_map_voltage_linear(rdev, uV, uV);
	if (sel < 0)
		return sel;

	sel <<= ffs(rdev->desc->vsel_mask) - 1;

	ret = regmap_update_bits(regl->hw->regmap, rinfo->suspend_vsel_reg,
				 rdev->desc->vsel_mask, sel);

	return ret;
}