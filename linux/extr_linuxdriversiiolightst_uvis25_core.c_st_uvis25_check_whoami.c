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
struct st_uvis25_hw {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ST_UVIS25_REG_WHOAMI_ADDR ; 
 int ST_UVIS25_REG_WHOAMI_VAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int st_uvis25_check_whoami(struct st_uvis25_hw *hw)
{
	int err, data;

	err = regmap_read(hw->regmap, ST_UVIS25_REG_WHOAMI_ADDR, &data);
	if (err < 0) {
		dev_err(regmap_get_device(hw->regmap),
			"failed to read whoami register\n");
		return err;
	}

	if (data != ST_UVIS25_REG_WHOAMI_VAL) {
		dev_err(regmap_get_device(hw->regmap),
			"wrong whoami {%02x vs %02x}\n",
			data, ST_UVIS25_REG_WHOAMI_VAL);
		return -ENODEV;
	}

	return 0;
}