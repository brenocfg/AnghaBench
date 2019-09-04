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
struct lm3646_flash {int mode_reg; int /*<<< orphan*/  regmap; } ;
typedef  enum v4l2_flash_led_mode { ____Placeholder_v4l2_flash_led_mode } v4l2_flash_led_mode ;

/* Variables and functions */
 int EINVAL ; 
 int MODE_FLASH ; 
 int MODE_SHDN ; 
 int MODE_TORCH ; 
 int /*<<< orphan*/  REG_ENABLE ; 
#define  V4L2_FLASH_LED_MODE_FLASH 130 
#define  V4L2_FLASH_LED_MODE_NONE 129 
#define  V4L2_FLASH_LED_MODE_TORCH 128 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lm3646_mode_ctrl(struct lm3646_flash *flash,
			    enum v4l2_flash_led_mode led_mode)
{
	switch (led_mode) {
	case V4L2_FLASH_LED_MODE_NONE:
		return regmap_write(flash->regmap,
				    REG_ENABLE, flash->mode_reg | MODE_SHDN);
	case V4L2_FLASH_LED_MODE_TORCH:
		return regmap_write(flash->regmap,
				    REG_ENABLE, flash->mode_reg | MODE_TORCH);
	case V4L2_FLASH_LED_MODE_FLASH:
		return regmap_write(flash->regmap,
				    REG_ENABLE, flash->mode_reg | MODE_FLASH);
	}
	return -EINVAL;
}