#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vibra_info {int enabled; struct twl6040* twl6040; int /*<<< orphan*/  dev; int /*<<< orphan*/  supplies; } ;
struct twl6040 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TWL6040_REG_VIBCTLL ; 
 int /*<<< orphan*/  TWL6040_REG_VIBCTLR ; 
 scalar_t__ TWL6040_REV_ES1_1 ; 
 int TWL6040_VIBCTRL ; 
 int TWL6040_VIBENA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ twl6040_get_revid (struct twl6040*) ; 
 int /*<<< orphan*/  twl6040_power (struct twl6040*,int) ; 
 int /*<<< orphan*/  twl6040_reg_write (struct twl6040*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void twl6040_vibra_enable(struct vibra_info *info)
{
	struct twl6040 *twl6040 = info->twl6040;
	int ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(info->supplies), info->supplies);
	if (ret) {
		dev_err(info->dev, "failed to enable regulators %d\n", ret);
		return;
	}

	twl6040_power(info->twl6040, 1);
	if (twl6040_get_revid(twl6040) <= TWL6040_REV_ES1_1) {
		/*
		 * ERRATA: Disable overcurrent protection for at least
		 * 3ms when enabling vibrator drivers to avoid false
		 * overcurrent detection
		 */
		twl6040_reg_write(twl6040, TWL6040_REG_VIBCTLL,
				  TWL6040_VIBENA | TWL6040_VIBCTRL);
		twl6040_reg_write(twl6040, TWL6040_REG_VIBCTLR,
				  TWL6040_VIBENA | TWL6040_VIBCTRL);
		usleep_range(3000, 3500);
	}

	twl6040_reg_write(twl6040, TWL6040_REG_VIBCTLL,
			  TWL6040_VIBENA);
	twl6040_reg_write(twl6040, TWL6040_REG_VIBCTLR,
			  TWL6040_VIBENA);

	info->enabled = true;
}