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
typedef  int /*<<< orphan*/  u8 ;
struct regulator_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct ab8500_ext_regulator_info {int /*<<< orphan*/  update_val; int /*<<< orphan*/  update_mask; int /*<<< orphan*/  update_reg; int /*<<< orphan*/  update_bank; TYPE_2__ desc; int /*<<< orphan*/  dev; TYPE_1__* cfg; int /*<<< orphan*/  update_val_lp; int /*<<< orphan*/  update_val_hp; } ;
struct TYPE_3__ {scalar_t__ hwreq; } ;

/* Variables and functions */
 int EINVAL ; 
#define  REGULATOR_MODE_IDLE 129 
#define  REGULATOR_MODE_NORMAL 128 
 scalar_t__ ab8500_ext_regulator_is_enabled (struct regulator_dev*) ; 
 int abx500_mask_and_set_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rdev_get_dev (struct regulator_dev*) ; 
 struct ab8500_ext_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int ab8500_ext_regulator_set_mode(struct regulator_dev *rdev,
					 unsigned int mode)
{
	int ret = 0;
	struct ab8500_ext_regulator_info *info = rdev_get_drvdata(rdev);
	u8 regval;

	if (info == NULL) {
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		return -EINVAL;
	}

	switch (mode) {
	case REGULATOR_MODE_NORMAL:
		regval = info->update_val_hp;
		break;
	case REGULATOR_MODE_IDLE:
		regval = info->update_val_lp;
		break;

	default:
		return -EINVAL;
	}

	/* If regulator is enabled and info->cfg->hwreq is set, the regulator
	   must be on in high power, so we don't need to write the register with
	   the same value.
	 */
	if (ab8500_ext_regulator_is_enabled(rdev) &&
	    !(info->cfg && info->cfg->hwreq)) {
		ret = abx500_mask_and_set_register_interruptible(info->dev,
					info->update_bank, info->update_reg,
					info->update_mask, regval);
		if (ret < 0) {
			dev_err(rdev_get_dev(rdev),
				"Could not set regulator mode.\n");
			return ret;
		}

		dev_dbg(rdev_get_dev(rdev),
			"%s-set_mode (bank, reg, mask, value): "
			"0x%x, 0x%x, 0x%x, 0x%x\n",
			info->desc.name, info->update_bank, info->update_reg,
			info->update_mask, regval);
	}

	info->update_val = regval;

	return 0;
}