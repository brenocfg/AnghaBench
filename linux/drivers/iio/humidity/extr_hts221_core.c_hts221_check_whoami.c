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
struct hts221_hw {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HTS221_REG_WHOAMI_ADDR ; 
 int HTS221_REG_WHOAMI_VAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int hts221_check_whoami(struct hts221_hw *hw)
{
	int err, data;

	err = regmap_read(hw->regmap, HTS221_REG_WHOAMI_ADDR, &data);
	if (err < 0) {
		dev_err(hw->dev, "failed to read whoami register\n");
		return err;
	}

	if (data != HTS221_REG_WHOAMI_VAL) {
		dev_err(hw->dev, "wrong whoami {%02x vs %02x}\n",
			data, HTS221_REG_WHOAMI_VAL);
		return -ENODEV;
	}

	return 0;
}