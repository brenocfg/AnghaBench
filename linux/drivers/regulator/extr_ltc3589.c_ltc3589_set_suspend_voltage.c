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
struct ltc3589 {int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  vsel_mask; scalar_t__ vsel_reg; } ;

/* Variables and functions */
 struct ltc3589* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int regulator_map_voltage_linear (struct regulator_dev*,int,int) ; 

__attribute__((used)) static int ltc3589_set_suspend_voltage(struct regulator_dev *rdev, int uV)
{
	struct ltc3589 *ltc3589 = rdev_get_drvdata(rdev);
	int sel;

	sel = regulator_map_voltage_linear(rdev, uV, uV);
	if (sel < 0)
		return sel;

	/* DTV2 register follows right after the corresponding DTV1 register */
	return regmap_update_bits(ltc3589->regmap, rdev->desc->vsel_reg + 1,
				  rdev->desc->vsel_mask, sel);
}