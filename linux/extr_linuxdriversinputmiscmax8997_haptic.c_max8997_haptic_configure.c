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
struct max8997_haptic {int type; int enabled; int mode; int pwm_divisor; int internal_mode_pattern; int pattern_cycle; int pattern_signal_period; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int MAX8997_CYCLE_SHIFT ; 
 int MAX8997_ENABLE_SHIFT ; 
 int /*<<< orphan*/  MAX8997_HAPTIC_REG_CONF2 ; 
 int /*<<< orphan*/  MAX8997_HAPTIC_REG_CYCLECONF1 ; 
 int /*<<< orphan*/  MAX8997_HAPTIC_REG_CYCLECONF2 ; 
 int /*<<< orphan*/  MAX8997_HAPTIC_REG_DRVCONF ; 
 int /*<<< orphan*/  MAX8997_HAPTIC_REG_SIGCONF1 ; 
 int /*<<< orphan*/  MAX8997_HAPTIC_REG_SIGCONF2 ; 
 int /*<<< orphan*/  MAX8997_HAPTIC_REG_SIGCONF3 ; 
 int /*<<< orphan*/  MAX8997_HAPTIC_REG_SIGCONF4 ; 
 int MAX8997_INTERNAL_MODE ; 
 int MAX8997_MODE_SHIFT ; 
 int MAX8997_MOTOR_TYPE_SHIFT ; 
 int MAX8997_PWM_DUTY_SHIFT ; 
 int MAX8997_SIG_DUTY_SHIFT ; 
 int MAX8997_SIG_PERIOD_SHIFT ; 
 int /*<<< orphan*/  max8997_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void max8997_haptic_configure(struct max8997_haptic *chip)
{
	u8 value;

	value = chip->type << MAX8997_MOTOR_TYPE_SHIFT |
		chip->enabled << MAX8997_ENABLE_SHIFT |
		chip->mode << MAX8997_MODE_SHIFT | chip->pwm_divisor;
	max8997_write_reg(chip->client, MAX8997_HAPTIC_REG_CONF2, value);

	if (chip->mode == MAX8997_INTERNAL_MODE && chip->enabled) {
		value = chip->internal_mode_pattern << MAX8997_CYCLE_SHIFT |
			chip->internal_mode_pattern << MAX8997_SIG_PERIOD_SHIFT |
			chip->internal_mode_pattern << MAX8997_SIG_DUTY_SHIFT |
			chip->internal_mode_pattern << MAX8997_PWM_DUTY_SHIFT;
		max8997_write_reg(chip->client,
			MAX8997_HAPTIC_REG_DRVCONF, value);

		switch (chip->internal_mode_pattern) {
		case 0:
			value = chip->pattern_cycle << 4;
			max8997_write_reg(chip->client,
				MAX8997_HAPTIC_REG_CYCLECONF1, value);
			value = chip->pattern_signal_period;
			max8997_write_reg(chip->client,
				MAX8997_HAPTIC_REG_SIGCONF1, value);
			break;

		case 1:
			value = chip->pattern_cycle;
			max8997_write_reg(chip->client,
				MAX8997_HAPTIC_REG_CYCLECONF1, value);
			value = chip->pattern_signal_period;
			max8997_write_reg(chip->client,
				MAX8997_HAPTIC_REG_SIGCONF2, value);
			break;

		case 2:
			value = chip->pattern_cycle << 4;
			max8997_write_reg(chip->client,
				MAX8997_HAPTIC_REG_CYCLECONF2, value);
			value = chip->pattern_signal_period;
			max8997_write_reg(chip->client,
				MAX8997_HAPTIC_REG_SIGCONF3, value);
			break;

		case 3:
			value = chip->pattern_cycle;
			max8997_write_reg(chip->client,
				MAX8997_HAPTIC_REG_CYCLECONF2, value);
			value = chip->pattern_signal_period;
			max8997_write_reg(chip->client,
				MAX8997_HAPTIC_REG_SIGCONF4, value);
			break;

		default:
			break;
		}
	}
}