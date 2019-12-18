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
typedef  int u8 ;
struct ti_lmu_bank {scalar_t__ max_brightness; int lsb_brightness_reg; int msb_brightness_reg; struct regmap* regmap; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LMU_11BIT_LSB_MASK ; 
 int LMU_11BIT_MSB_SHIFT ; 
 scalar_t__ MAX_BRIGHTNESS_11BIT ; 
 int regmap_update_bits (struct regmap*,int,int /*<<< orphan*/ ,int) ; 
 int regmap_write (struct regmap*,int,int) ; 

__attribute__((used)) static int ti_lmu_common_update_brightness(struct ti_lmu_bank *lmu_bank,
					   int brightness)
{
	struct regmap *regmap = lmu_bank->regmap;
	u8 reg, val;
	int ret;

	/*
	 * Brightness register update
	 *
	 * 11 bit dimming: update LSB bits and write MSB byte.
	 *		   MSB brightness should be shifted.
	 *  8 bit dimming: write MSB byte.
	 */
	if (lmu_bank->max_brightness == MAX_BRIGHTNESS_11BIT) {
		reg = lmu_bank->lsb_brightness_reg;
		ret = regmap_update_bits(regmap, reg,
					 LMU_11BIT_LSB_MASK,
					 brightness);
		if (ret)
			return ret;

		val = brightness >> LMU_11BIT_MSB_SHIFT;
	} else {
		val = brightness;
	}

	reg = lmu_bank->msb_brightness_reg;

	return regmap_write(regmap, reg, val);
}