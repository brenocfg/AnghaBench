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
struct lm3532_led {int control_bank; unsigned int ctrl_brt_pointer; unsigned int mode; int full_scale_current; int num_leds; int* led_strings; struct lm3532_data* priv; } ;
struct lm3532_data {unsigned int runtime_ramp_up; unsigned int runtime_ramp_down; int /*<<< orphan*/  regmap; scalar_t__ enable_gpio; } ;

/* Variables and functions */
 int LM3532_FS_CURR_MIN ; 
 int LM3532_FS_CURR_STEP ; 
 unsigned int LM3532_OUTPUT_CFG_MASK ; 
 unsigned int LM3532_RAMP_DOWN_SHIFT ; 
 int LM3532_REG_CTRL_A_FS_CURR ; 
 int /*<<< orphan*/  LM3532_REG_OUTPUT_CFG ; 
 int LM3532_REG_RT_RAMP ; 
 int LM3532_REG_ZONE_CFG_A ; 
 unsigned int LM3532_ZONE_MASK ; 
 int /*<<< orphan*/  gpiod_direction_output (scalar_t__,int) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int regmap_write (int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int lm3532_init_registers(struct lm3532_led *led)
{
	struct lm3532_data *drvdata = led->priv;
	unsigned int runtime_ramp_val;
	unsigned int output_cfg_val = 0;
	unsigned int output_cfg_shift = 0;
	unsigned int output_cfg_mask = 0;
	unsigned int brightness_config_reg;
	unsigned int brightness_config_val;
	int fs_current_reg;
	int fs_current_val;
	int ret, i;

	if (drvdata->enable_gpio)
		gpiod_direction_output(drvdata->enable_gpio, 1);

	brightness_config_reg = LM3532_REG_ZONE_CFG_A + led->control_bank * 2;
	/*
	 * This could be hard coded to the default value but the control
	 * brightness register may have changed during boot.
	 */
	ret = regmap_read(drvdata->regmap, brightness_config_reg,
			  &led->ctrl_brt_pointer);
	if (ret)
		return ret;

	led->ctrl_brt_pointer &= LM3532_ZONE_MASK;
	brightness_config_val = led->ctrl_brt_pointer | led->mode;
	ret = regmap_write(drvdata->regmap, brightness_config_reg,
			   brightness_config_val);
	if (ret)
		return ret;

	if (led->full_scale_current) {
		fs_current_reg = LM3532_REG_CTRL_A_FS_CURR + led->control_bank * 2;
		fs_current_val = (led->full_scale_current - LM3532_FS_CURR_MIN) /
				 LM3532_FS_CURR_STEP;

		ret = regmap_write(drvdata->regmap, fs_current_reg,
				   fs_current_val);
		if (ret)
			return ret;
	}

	for (i = 0; i < led->num_leds; i++) {
		output_cfg_shift = led->led_strings[i] * 2;
		output_cfg_val |= (led->control_bank << output_cfg_shift);
		output_cfg_mask |= LM3532_OUTPUT_CFG_MASK << output_cfg_shift;
	}

	ret = regmap_update_bits(drvdata->regmap, LM3532_REG_OUTPUT_CFG,
				 output_cfg_mask, output_cfg_val);
	if (ret)
		return ret;

	runtime_ramp_val = drvdata->runtime_ramp_up |
			 (drvdata->runtime_ramp_down << LM3532_RAMP_DOWN_SHIFT);

	return regmap_write(drvdata->regmap, LM3532_REG_RT_RAMP,
			    runtime_ramp_val);
}