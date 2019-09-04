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
typedef  scalar_t__ u32 ;
struct regmap {int dummy; } ;
struct max77693_led_device {scalar_t__ iout_joint; struct regmap* regmap; } ;
struct max77693_led_config_data {scalar_t__ low_vsys; int boost_mode; int /*<<< orphan*/  boost_vout; scalar_t__* iout_flash_max; } ;

/* Variables and functions */
 int FLASH_BOOST_FIXED ; 
 int FLASH_BOOST_LEDNUM_2 ; 
 size_t FLED1 ; 
 size_t FLED2 ; 
 int MAX77693_LED_BOOST_FIXED ; 
 int /*<<< orphan*/  MAX77693_LED_REG_ITORCHTIMER ; 
 int /*<<< orphan*/  MAX77693_LED_REG_MAX_FLASH1 ; 
 int /*<<< orphan*/  MAX77693_LED_REG_MAX_FLASH2 ; 
 int /*<<< orphan*/  MAX77693_LED_REG_VOUT_CNTL ; 
 int /*<<< orphan*/  MAX77693_LED_REG_VOUT_FLASH1 ; 
 int MAX77693_LED_TRIG_TYPE_LEVEL ; 
 int MAX_FLASH1_MAX_FL_EN ; 
 int /*<<< orphan*/  MODE_OFF ; 
 int TORCH_TMR_NO_TIMER ; 
 scalar_t__ max77693_fled_used (struct max77693_led_device*,size_t) ; 
 int max77693_led_vout_to_reg (int /*<<< orphan*/ ) ; 
 int max77693_led_vsys_to_reg (scalar_t__) ; 
 int max77693_set_flash_current (struct max77693_led_device*,int,scalar_t__) ; 
 int max77693_set_mode_reg (struct max77693_led_device*,int /*<<< orphan*/ ) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max77693_setup(struct max77693_led_device *led,
			 struct max77693_led_config_data *led_cfg)
{
	struct regmap *rmap = led->regmap;
	int i, first_led, last_led, ret;
	u32 max_flash_curr[2];
	u8 v;

	/*
	 * Initialize only flash current. Torch current doesn't
	 * require initialization as ITORCH register is written with
	 * new value each time brightness_set op is called.
	 */
	if (led->iout_joint) {
		first_led = FLED1;
		last_led = FLED1;
		max_flash_curr[FLED1] = led_cfg->iout_flash_max[FLED1] +
					led_cfg->iout_flash_max[FLED2];
	} else {
		first_led = max77693_fled_used(led, FLED1) ? FLED1 : FLED2;
		last_led = max77693_fled_used(led, FLED2) ? FLED2 : FLED1;
		max_flash_curr[FLED1] = led_cfg->iout_flash_max[FLED1];
		max_flash_curr[FLED2] = led_cfg->iout_flash_max[FLED2];
	}

	for (i = first_led; i <= last_led; ++i) {
		ret = max77693_set_flash_current(led, i,
					max_flash_curr[i]);
		if (ret < 0)
			return ret;
	}

	v = TORCH_TMR_NO_TIMER | MAX77693_LED_TRIG_TYPE_LEVEL;
	ret = regmap_write(rmap, MAX77693_LED_REG_ITORCHTIMER, v);
	if (ret < 0)
		return ret;

	if (led_cfg->low_vsys > 0)
		v = max77693_led_vsys_to_reg(led_cfg->low_vsys) |
						MAX_FLASH1_MAX_FL_EN;
	else
		v = 0;

	ret = regmap_write(rmap, MAX77693_LED_REG_MAX_FLASH1, v);
	if (ret < 0)
		return ret;
	ret = regmap_write(rmap, MAX77693_LED_REG_MAX_FLASH2, 0);
	if (ret < 0)
		return ret;

	if (led_cfg->boost_mode == MAX77693_LED_BOOST_FIXED)
		v = FLASH_BOOST_FIXED;
	else
		v = led_cfg->boost_mode | led_cfg->boost_mode << 1;

	if (max77693_fled_used(led, FLED1) && max77693_fled_used(led, FLED2))
		v |= FLASH_BOOST_LEDNUM_2;

	ret = regmap_write(rmap, MAX77693_LED_REG_VOUT_CNTL, v);
	if (ret < 0)
		return ret;

	v = max77693_led_vout_to_reg(led_cfg->boost_vout);
	ret = regmap_write(rmap, MAX77693_LED_REG_VOUT_FLASH1, v);
	if (ret < 0)
		return ret;

	return max77693_set_mode_reg(led, MODE_OFF);
}