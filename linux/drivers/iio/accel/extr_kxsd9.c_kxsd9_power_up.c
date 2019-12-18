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
struct kxsd9_state {int scale; int /*<<< orphan*/  map; int /*<<< orphan*/  dev; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int KXSD9_CTRL_B_ENABLE ; 
 int KXSD9_CTRL_C_LP_1000HZ ; 
 int KXSD9_CTRL_C_MOT_LAT ; 
 int KXSD9_CTRL_C_MOT_LEV ; 
 int /*<<< orphan*/  KXSD9_REG_CTRL_B ; 
 int /*<<< orphan*/  KXSD9_REG_CTRL_C ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kxsd9_power_up(struct kxsd9_state *st)
{
	int ret;

	/* Enable the regulators */
	ret = regulator_bulk_enable(ARRAY_SIZE(st->regs), st->regs);
	if (ret) {
		dev_err(st->dev, "Cannot enable regulators\n");
		return ret;
	}

	/* Power up */
	ret = regmap_write(st->map,
			   KXSD9_REG_CTRL_B,
			   KXSD9_CTRL_B_ENABLE);
	if (ret)
		return ret;

	/*
	 * Set 1000Hz LPF, 2g fullscale, motion wakeup threshold 1g,
	 * latched wakeup
	 */
	ret = regmap_write(st->map,
			   KXSD9_REG_CTRL_C,
			   KXSD9_CTRL_C_LP_1000HZ |
			   KXSD9_CTRL_C_MOT_LEV	|
			   KXSD9_CTRL_C_MOT_LAT |
			   st->scale);
	if (ret)
		return ret;

	/*
	 * Power-up time depends on the LPF setting, but typ 15.9 ms, let's
	 * set 20 ms to allow for some slack.
	 */
	msleep(20);

	return 0;
}