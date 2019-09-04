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
struct bh1770_chip {scalar_t__ lux_thres_lo_onchip; int /*<<< orphan*/  lux_thres_hi_onchip; int /*<<< orphan*/  client; scalar_t__ prox_data; scalar_t__ lux_data_raw; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BH1770_ALS_CONTROL ; 
 int /*<<< orphan*/  BH1770_LUX_RANGE ; 
 int BH1770_RESET_TIME ; 
 int /*<<< orphan*/  BH1770_STANDALONE ; 
 int BH1770_STARTUP_DELAY ; 
 int /*<<< orphan*/  BH1770_SWRESET ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int bh1770_chip_on(struct bh1770_chip *chip)
{
	int ret = regulator_bulk_enable(ARRAY_SIZE(chip->regs),
					chip->regs);
	if (ret < 0)
		return ret;

	usleep_range(BH1770_STARTUP_DELAY, BH1770_STARTUP_DELAY * 2);

	/* Reset the chip */
	i2c_smbus_write_byte_data(chip->client, BH1770_ALS_CONTROL,
				BH1770_SWRESET);
	usleep_range(BH1770_RESET_TIME, BH1770_RESET_TIME * 2);

	/*
	 * ALS is started always since proximity needs als results
	 * for realibility estimation.
	 * Let's assume dark until the first ALS measurement is ready.
	 */
	chip->lux_data_raw = 0;
	chip->prox_data = 0;
	ret = i2c_smbus_write_byte_data(chip->client,
					BH1770_ALS_CONTROL, BH1770_STANDALONE);

	/* Assume reset defaults */
	chip->lux_thres_hi_onchip = BH1770_LUX_RANGE;
	chip->lux_thres_lo_onchip = 0;

	return ret;
}