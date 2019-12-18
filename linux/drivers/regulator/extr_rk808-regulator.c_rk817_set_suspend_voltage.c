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
struct regulator_dev {TYPE_1__* desc; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {unsigned int vsel_reg; int /*<<< orphan*/  vsel_mask; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int RK808_SLP_REG_OFFSET ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int) ; 
 int regulator_map_voltage_linear (struct regulator_dev*,int,int) ; 

__attribute__((used)) static int rk817_set_suspend_voltage(struct regulator_dev *rdev, int uv)
{
	unsigned int reg;
	int sel = regulator_map_voltage_linear(rdev, uv, uv);
	/* only ldo1~ldo9 */
	if (sel < 0)
		return -EINVAL;

	reg = rdev->desc->vsel_reg + RK808_SLP_REG_OFFSET;

	return regmap_update_bits(rdev->regmap, reg,
				  rdev->desc->vsel_mask,
				  sel);
}