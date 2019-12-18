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
struct lm3646_flash {unsigned int mode_reg; int /*<<< orphan*/  regmap; TYPE_1__* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  led1_torch_brt; int /*<<< orphan*/  led1_flash_brt; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM3646_LED1_FLASH_BRT_uA_TO_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LM3646_LED1_TORCH_BRT_uA_TO_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_ENABLE ; 
 int /*<<< orphan*/  REG_FLAG ; 
 int /*<<< orphan*/  REG_LED1_FLASH_BR ; 
 int /*<<< orphan*/  REG_LED1_TORCH_BR ; 
 int /*<<< orphan*/  V4L2_FLASH_LED_MODE_NONE ; 
 int lm3646_mode_ctrl (struct lm3646_flash*,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm3646_init_device(struct lm3646_flash *flash)
{
	unsigned int reg_val;
	int rval;

	/* read the value of mode register to reduce redundant i2c accesses */
	rval = regmap_read(flash->regmap, REG_ENABLE, &reg_val);
	if (rval < 0)
		return rval;
	flash->mode_reg = reg_val & 0xfc;

	/* output disable */
	rval = lm3646_mode_ctrl(flash, V4L2_FLASH_LED_MODE_NONE);
	if (rval < 0)
		return rval;

	/*
	 * LED1 flash current setting
	 * LED2 flash current = Total(Max) flash current - LED1 flash current
	 */
	rval = regmap_update_bits(flash->regmap,
				  REG_LED1_FLASH_BR, 0x7F,
				  LM3646_LED1_FLASH_BRT_uA_TO_REG
				  (flash->pdata->led1_flash_brt));

	if (rval < 0)
		return rval;

	/*
	 * LED1 torch current setting
	 * LED2 torch current = Total(Max) torch current - LED1 torch current
	 */
	rval = regmap_update_bits(flash->regmap,
				  REG_LED1_TORCH_BR, 0x7F,
				  LM3646_LED1_TORCH_BRT_uA_TO_REG
				  (flash->pdata->led1_torch_brt));
	if (rval < 0)
		return rval;

	/* Reset flag register */
	return regmap_read(flash->regmap, REG_FLAG, &reg_val);
}