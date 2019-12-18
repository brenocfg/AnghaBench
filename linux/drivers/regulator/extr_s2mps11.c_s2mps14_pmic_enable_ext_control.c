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
struct s2mps11_info {int dummy; } ;
struct regulator_dev {TYPE_1__* desc; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_mask; int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  S2MPS14_ENABLE_EXT_CONTROL ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s2mps14_pmic_enable_ext_control(struct s2mps11_info *s2mps11,
		struct regulator_dev *rdev)
{
	return regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
			rdev->desc->enable_mask, S2MPS14_ENABLE_EXT_CONTROL);
}