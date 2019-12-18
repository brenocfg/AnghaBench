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
struct s5m8767_info {TYPE_1__* iodev; } ;
struct regulator_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap_pmic; } ;

/* Variables and functions */
 int EINVAL ; 
 int S5M8767_BUCK9 ; 
 int /*<<< orphan*/  S5M8767_ENCTRL_MASK ; 
 int S5M8767_ENCTRL_SHIFT ; 
 int S5M8767_ENCTRL_USE_GPIO ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int s5m8767_get_register (struct s5m8767_info*,int,int*,int*) ; 

__attribute__((used)) static int s5m8767_enable_ext_control(struct s5m8767_info *s5m8767,
		struct regulator_dev *rdev)
{
	int id = rdev_get_id(rdev);
	int ret, reg, enable_ctrl;

	if (id != S5M8767_BUCK9)
		return -EINVAL;

	ret = s5m8767_get_register(s5m8767, id, &reg, &enable_ctrl);
	if (ret)
		return ret;

	return regmap_update_bits(s5m8767->iodev->regmap_pmic,
			reg, S5M8767_ENCTRL_MASK,
			S5M8767_ENCTRL_USE_GPIO << S5M8767_ENCTRL_SHIFT);
}