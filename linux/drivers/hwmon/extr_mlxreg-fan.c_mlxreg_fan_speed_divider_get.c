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
typedef  int u32 ;
struct mlxreg_fan {int divider; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct mlxreg_core_data {int /*<<< orphan*/  capability; } ;

/* Variables and functions */
 int MLXREG_FAN_TACHO_DIV_MIN ; 
 int MLXREG_FAN_TACHO_DIV_SCALE_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int mlxreg_fan_speed_divider_get(struct mlxreg_fan *fan,
					struct mlxreg_core_data *data)
{
	u32 regval;
	int err;

	err = regmap_read(fan->regmap, data->capability, &regval);
	if (err) {
		dev_err(fan->dev, "Failed to query capability register 0x%08x\n",
			data->capability);
		return err;
	}

	/*
	 * Set divider value according to the capability register, in case it
	 * contains valid value. Otherwise use default value. The purpose of
	 * this validation is to protect against the old hardware, in which
	 * this register can return zero.
	 */
	if (regval > 0 && regval <= MLXREG_FAN_TACHO_DIV_SCALE_MAX)
		fan->divider = regval * MLXREG_FAN_TACHO_DIV_MIN;

	return 0;
}