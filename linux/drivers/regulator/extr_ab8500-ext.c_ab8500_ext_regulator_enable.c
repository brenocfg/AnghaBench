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
struct ab8500_ext_regulator_info {int /*<<< orphan*/  update_mask; int /*<<< orphan*/  update_reg; int /*<<< orphan*/  update_bank; TYPE_2__ desc; int /*<<< orphan*/  dev; int /*<<< orphan*/  update_val; int /*<<< orphan*/  update_val_hp; TYPE_1__* cfg; } ;
struct TYPE_3__ {scalar_t__ hwreq; } ;

/* Variables and functions */
 int EINVAL ; 
 int abx500_mask_and_set_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rdev_get_dev (struct regulator_dev*) ; 
 struct ab8500_ext_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int ab8500_ext_regulator_enable(struct regulator_dev *rdev)
{
	int ret;
	struct ab8500_ext_regulator_info *info = rdev_get_drvdata(rdev);
	u8 regval;

	if (info == NULL) {
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		return -EINVAL;
	}

	/*
	 * To satisfy both HW high power request and SW request, the regulator
	 * must be on in high power.
	 */
	if (info->cfg && info->cfg->hwreq)
		regval = info->update_val_hp;
	else
		regval = info->update_val;

	ret = abx500_mask_and_set_register_interruptible(info->dev,
		info->update_bank, info->update_reg,
		info->update_mask, regval);
	if (ret < 0) {
		dev_err(rdev_get_dev(rdev),
			"couldn't set enable bits for regulator\n");
		return ret;
	}

	dev_dbg(rdev_get_dev(rdev),
		"%s-enable (bank, reg, mask, value): 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
		info->desc.name, info->update_bank, info->update_reg,
		info->update_mask, regval);

	return 0;
}