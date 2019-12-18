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
struct lm3601x_led {int last_flag; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EIO ; 
 int LED_FAULT_INPUT_VOLTAGE ; 
 int LED_FAULT_LED_OVER_TEMPERATURE ; 
 int LED_FAULT_OVER_CURRENT ; 
 int LED_FAULT_OVER_TEMPERATURE ; 
 int LED_FAULT_OVER_VOLTAGE ; 
 int LED_FAULT_SHORT_CIRCUIT ; 
 int LED_FAULT_UNDER_VOLTAGE ; 
 int LM36010_CURR_LIMIT ; 
 int LM36010_OVP_FAULT ; 
 int /*<<< orphan*/  LM3601X_FLAGS_REG ; 
 int LM3601X_IVFM_TRIP ; 
 int LM3601X_SHORT_FAULT ; 
 int LM3601X_THERM_CURR ; 
 int LM3601X_THERM_SHUTDOWN ; 
 int LM3601X_UVLO_FAULT ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int lm3601x_read_faults(struct lm3601x_led *led)
{
	int flags_val;
	int ret;

	ret = regmap_read(led->regmap, LM3601X_FLAGS_REG, &flags_val);
	if (ret < 0)
		return -EIO;

	led->last_flag = 0;

	if (flags_val & LM36010_OVP_FAULT)
		led->last_flag |= LED_FAULT_OVER_VOLTAGE;

	if (flags_val & (LM3601X_THERM_SHUTDOWN | LM3601X_THERM_CURR))
		led->last_flag |= LED_FAULT_OVER_TEMPERATURE;

	if (flags_val & LM3601X_SHORT_FAULT)
		led->last_flag |= LED_FAULT_SHORT_CIRCUIT;

	if (flags_val & LM36010_CURR_LIMIT)
		led->last_flag |= LED_FAULT_OVER_CURRENT;

	if (flags_val & LM3601X_UVLO_FAULT)
		led->last_flag |= LED_FAULT_UNDER_VOLTAGE;

	if (flags_val & LM3601X_IVFM_TRIP)
		led->last_flag |= LED_FAULT_INPUT_VOLTAGE;

	if (flags_val & LM3601X_THERM_SHUTDOWN)
		led->last_flag |= LED_FAULT_LED_OVER_TEMPERATURE;

	return led->last_flag;
}