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
struct mlxreg_fan {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct mlxreg_core_data {int bit; int /*<<< orphan*/  capability; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int mlxreg_fan_connect_verify(struct mlxreg_fan *fan,
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

	return !!(regval & data->bit);
}