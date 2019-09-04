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
struct lm3601x_led {int flash_timeout; int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;
struct led_classdev_flash {int dummy; } ;

/* Variables and functions */
 int LED_OFF ; 
 int /*<<< orphan*/  LM3601X_CFG_REG ; 
 int /*<<< orphan*/  LM3601X_ENABLE_REG ; 
 int LM3601X_LOWER_STEP_US ; 
 int LM3601X_MODE_IR_DRV ; 
 int LM3601X_MODE_STROBE ; 
 int LM3601X_MODE_TORCH ; 
 int LM3601X_TIMEOUT_MASK ; 
 int LM3601X_TIMEOUT_XOVER_US ; 
 int LM3601X_UPPER_STEP_US ; 
 struct lm3601x_led* fled_cdev_to_led (struct led_classdev_flash*) ; 
 int lm3601x_read_faults (struct lm3601x_led*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int lm3601x_strobe_set(struct led_classdev_flash *fled_cdev,
				bool state)
{
	struct lm3601x_led *led = fled_cdev_to_led(fled_cdev);
	int timeout_reg_val;
	int current_timeout;
	int ret;

	mutex_lock(&led->lock);

	ret = regmap_read(led->regmap, LM3601X_CFG_REG, &current_timeout);
	if (ret < 0)
		goto out;

	if (led->flash_timeout >= LM3601X_TIMEOUT_XOVER_US)
		timeout_reg_val = led->flash_timeout / LM3601X_UPPER_STEP_US + 0x07;
	else
		timeout_reg_val = led->flash_timeout / LM3601X_LOWER_STEP_US - 0x01;

	if (led->flash_timeout != current_timeout)
		ret = regmap_update_bits(led->regmap, LM3601X_CFG_REG,
					LM3601X_TIMEOUT_MASK, timeout_reg_val);

	if (state)
		ret = regmap_update_bits(led->regmap, LM3601X_ENABLE_REG,
					LM3601X_MODE_TORCH | LM3601X_MODE_IR_DRV,
					LM3601X_MODE_STROBE);
	else
		ret = regmap_update_bits(led->regmap, LM3601X_ENABLE_REG,
					LM3601X_MODE_STROBE, LED_OFF);

	ret = lm3601x_read_faults(led);
out:
	mutex_unlock(&led->lock);
	return ret;
}