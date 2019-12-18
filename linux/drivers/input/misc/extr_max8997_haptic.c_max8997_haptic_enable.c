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
struct max8997_haptic {int enabled; scalar_t__ mode; int /*<<< orphan*/  mutex; int /*<<< orphan*/  regulator; int /*<<< orphan*/  dev; int /*<<< orphan*/  pwm; } ;

/* Variables and functions */
 scalar_t__ MAX8997_EXTERNAL_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  max8997_haptic_configure (struct max8997_haptic*) ; 
 int max8997_haptic_set_duty_cycle (struct max8997_haptic*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pwm_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max8997_haptic_enable(struct max8997_haptic *chip)
{
	int error;

	mutex_lock(&chip->mutex);

	error = max8997_haptic_set_duty_cycle(chip);
	if (error) {
		dev_err(chip->dev, "set_pwm_cycle failed, error: %d\n", error);
		goto out;
	}

	if (!chip->enabled) {
		error = regulator_enable(chip->regulator);
		if (error) {
			dev_err(chip->dev, "Failed to enable regulator\n");
			goto out;
		}
		max8997_haptic_configure(chip);
		if (chip->mode == MAX8997_EXTERNAL_MODE) {
			error = pwm_enable(chip->pwm);
			if (error) {
				dev_err(chip->dev, "Failed to enable PWM\n");
				regulator_disable(chip->regulator);
				goto out;
			}
		}
		chip->enabled = true;
	}

out:
	mutex_unlock(&chip->mutex);
}