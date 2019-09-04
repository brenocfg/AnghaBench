#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct bh1770_chip {int lux_thres_hi_onchip; int lux_thres_lo_onchip; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  BH1770_ALS_TH_UP_0 ; 
 int BH1770_LUX_RANGE ; 
 int bh1770_lux_adjusted_to_raw (struct bh1770_chip*,int) ; 
 int i2c_smbus_write_i2c_block_data (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pm_runtime_suspended (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bh1770_lux_update_thresholds(struct bh1770_chip *chip,
					u16 threshold_hi, u16 threshold_lo)
{
	u8 data[4];
	int ret;

	/* sysfs may call this when the chip is powered off */
	if (pm_runtime_suspended(&chip->client->dev))
		return 0;

	/*
	 * Compensate threshold values with the correction factors if not
	 * set to minimum or maximum.
	 * Min & max values disables interrupts.
	 */
	if (threshold_hi != BH1770_LUX_RANGE && threshold_hi != 0)
		threshold_hi = bh1770_lux_adjusted_to_raw(chip, threshold_hi);

	if (threshold_lo != BH1770_LUX_RANGE && threshold_lo != 0)
		threshold_lo = bh1770_lux_adjusted_to_raw(chip, threshold_lo);

	if (chip->lux_thres_hi_onchip == threshold_hi &&
	    chip->lux_thres_lo_onchip == threshold_lo)
		return 0;

	chip->lux_thres_hi_onchip = threshold_hi;
	chip->lux_thres_lo_onchip = threshold_lo;

	data[0] = threshold_hi;
	data[1] = threshold_hi >> 8;
	data[2] = threshold_lo;
	data[3] = threshold_lo >> 8;

	ret = i2c_smbus_write_i2c_block_data(chip->client,
					BH1770_ALS_TH_UP_0,
					ARRAY_SIZE(data),
					data);
	return ret;
}