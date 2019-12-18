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
struct s2mps11_info {int dev_type; int /*<<< orphan*/  suspend_state; } ;
struct regulator_dev {TYPE_1__* desc; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {unsigned int enable_mask; int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 int EINVAL ; 
#define  S2MPS11X 141 
#define  S2MPS11_LDO2 140 
#define  S2MPS11_LDO36 139 
#define  S2MPS11_LDO37 138 
#define  S2MPS11_LDO38 137 
#define  S2MPS13X 136 
#define  S2MPS14X 135 
 unsigned int S2MPS14_ENABLE_SUSPEND ; 
#define  S2MPS14_LDO3 134 
#define  S2MPU02 133 
#define  S2MPU02_BUCK7 132 
 unsigned int S2MPU02_DISABLE_SUSPEND ; 
 unsigned int S2MPU02_ENABLE_SUSPEND ; 
#define  S2MPU02_LDO13 131 
#define  S2MPU02_LDO14 130 
#define  S2MPU02_LDO15 129 
#define  S2MPU02_LDO17 128 
 struct s2mps11_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s2mps11_regulator_set_suspend_disable(struct regulator_dev *rdev)
{
	int ret;
	unsigned int val, state;
	struct s2mps11_info *s2mps11 = rdev_get_drvdata(rdev);
	int rdev_id = rdev_get_id(rdev);

	/* Below LDO should be always on or does not support suspend mode. */
	switch (s2mps11->dev_type) {
	case S2MPS11X:
		switch (rdev_id) {
		case S2MPS11_LDO2:
		case S2MPS11_LDO36:
		case S2MPS11_LDO37:
		case S2MPS11_LDO38:
			return 0;
		default:
			state = S2MPS14_ENABLE_SUSPEND;
			break;
		}
		break;
	case S2MPS13X:
	case S2MPS14X:
		switch (rdev_id) {
		case S2MPS14_LDO3:
			return 0;
		default:
			state = S2MPS14_ENABLE_SUSPEND;
			break;
		}
		break;
	case S2MPU02:
		switch (rdev_id) {
		case S2MPU02_LDO13:
		case S2MPU02_LDO14:
		case S2MPU02_LDO15:
		case S2MPU02_LDO17:
		case S2MPU02_BUCK7:
			state = S2MPU02_DISABLE_SUSPEND;
			break;
		default:
			state = S2MPU02_ENABLE_SUSPEND;
			break;
		}
		break;
	default:
		return -EINVAL;
	}

	ret = regmap_read(rdev->regmap, rdev->desc->enable_reg, &val);
	if (ret < 0)
		return ret;

	set_bit(rdev_id, s2mps11->suspend_state);
	/*
	 * Don't enable suspend mode if regulator is already disabled because
	 * this would effectively for a short time turn on the regulator after
	 * resuming.
	 * However we still want to toggle the suspend_state bit for regulator
	 * in case if it got enabled before suspending the system.
	 */
	if (!(val & rdev->desc->enable_mask))
		return 0;

	return regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				  rdev->desc->enable_mask, state);
}