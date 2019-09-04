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
struct smscore_config_gpio {int /*<<< orphan*/  pullupdown; int /*<<< orphan*/  outputslewrate; int /*<<< orphan*/  outputdriving; int /*<<< orphan*/  inputcharacteristics; int /*<<< orphan*/  direction; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMS_GPIO_DIRECTION_OUTPUT ; 
 int /*<<< orphan*/  SMS_GPIO_INPUTCHARACTERISTICS_NORMAL ; 
 int /*<<< orphan*/  SMS_GPIO_OUTPUTDRIVING_4mA ; 
 int /*<<< orphan*/  SMS_GPIO_OUTPUT_SLEW_RATE_0_45_V_NS ; 
 int /*<<< orphan*/  SMS_GPIO_PULLUPDOWN_NONE ; 

__attribute__((used)) static inline void sms_gpio_assign_11xx_default_led_config(
		struct smscore_config_gpio *p_gpio_config) {
	p_gpio_config->direction = SMS_GPIO_DIRECTION_OUTPUT;
	p_gpio_config->inputcharacteristics =
		SMS_GPIO_INPUTCHARACTERISTICS_NORMAL;
	p_gpio_config->outputdriving = SMS_GPIO_OUTPUTDRIVING_4mA;
	p_gpio_config->outputslewrate = SMS_GPIO_OUTPUT_SLEW_RATE_0_45_V_NS;
	p_gpio_config->pullupdown = SMS_GPIO_PULLUPDOWN_NONE;
}