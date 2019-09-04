#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st_lsm6dsx_hw {TYPE_1__* settings; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct TYPE_3__ {int* id; int wai; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENODEV ; 
 int ST_LSM6DSX_MAX_ID ; 
 int /*<<< orphan*/  ST_LSM6DSX_REG_WHOAMI_ADDR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* st_lsm6dsx_sensor_settings ; 

__attribute__((used)) static int st_lsm6dsx_check_whoami(struct st_lsm6dsx_hw *hw, int id)
{
	int err, i, j, data;

	for (i = 0; i < ARRAY_SIZE(st_lsm6dsx_sensor_settings); i++) {
		for (j = 0; j < ST_LSM6DSX_MAX_ID; j++) {
			if (id == st_lsm6dsx_sensor_settings[i].id[j])
				break;
		}
		if (j < ST_LSM6DSX_MAX_ID)
			break;
	}

	if (i == ARRAY_SIZE(st_lsm6dsx_sensor_settings)) {
		dev_err(hw->dev, "unsupported hw id [%02x]\n", id);
		return -ENODEV;
	}

	err = regmap_read(hw->regmap, ST_LSM6DSX_REG_WHOAMI_ADDR, &data);
	if (err < 0) {
		dev_err(hw->dev, "failed to read whoami register\n");
		return err;
	}

	if (data != st_lsm6dsx_sensor_settings[i].wai) {
		dev_err(hw->dev, "unsupported whoami [%02x]\n", data);
		return -ENODEV;
	}

	hw->settings = &st_lsm6dsx_sensor_settings[i];

	return 0;
}