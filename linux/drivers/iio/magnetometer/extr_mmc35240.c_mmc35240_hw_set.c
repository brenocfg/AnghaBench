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
typedef  int /*<<< orphan*/  u8 ;
struct mmc35240_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC35240_CTRL0_REFILL_BIT ; 
 int /*<<< orphan*/  MMC35240_CTRL0_RESET_BIT ; 
 int /*<<< orphan*/  MMC35240_CTRL0_SET_BIT ; 
 int /*<<< orphan*/  MMC35240_REG_CTRL0 ; 
 scalar_t__ MMC35240_WAIT_CHARGE_PUMP ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int mmc35240_hw_set(struct mmc35240_data *data, bool set)
{
	int ret;
	u8 coil_bit;

	/*
	 * Recharge the capacitor at VCAP pin, requested to be issued
	 * before a SET/RESET command.
	 */
	ret = regmap_update_bits(data->regmap, MMC35240_REG_CTRL0,
				 MMC35240_CTRL0_REFILL_BIT,
				 MMC35240_CTRL0_REFILL_BIT);
	if (ret < 0)
		return ret;
	usleep_range(MMC35240_WAIT_CHARGE_PUMP, MMC35240_WAIT_CHARGE_PUMP + 1);

	if (set)
		coil_bit = MMC35240_CTRL0_SET_BIT;
	else
		coil_bit = MMC35240_CTRL0_RESET_BIT;

	return regmap_update_bits(data->regmap, MMC35240_REG_CTRL0,
				  coil_bit, coil_bit);

}