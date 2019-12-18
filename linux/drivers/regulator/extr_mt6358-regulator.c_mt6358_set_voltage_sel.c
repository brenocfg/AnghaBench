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
typedef  int u32 ;
struct regulator_dev {int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  vsel_mask; int /*<<< orphan*/  vsel_reg; } ;
struct mt6358_regulator_info {int* index_table; int vsel_shift; TYPE_1__ desc; } ;

/* Variables and functions */
 struct mt6358_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt6358_set_voltage_sel(struct regulator_dev *rdev,
				  unsigned int selector)
{
	int idx, ret;
	const u32 *pvol;
	struct mt6358_regulator_info *info = rdev_get_drvdata(rdev);

	pvol = info->index_table;

	idx = pvol[selector];
	ret = regmap_update_bits(rdev->regmap, info->desc.vsel_reg,
				 info->desc.vsel_mask,
				 idx << info->vsel_shift);

	return ret;
}