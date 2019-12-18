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
struct max8997_haptic {int enabled; scalar_t__ mode; int /*<<< orphan*/  mutex; int /*<<< orphan*/  regulator; int /*<<< orphan*/  pwm; } ;

/* Variables and functions */
 scalar_t__ MAX8997_EXTERNAL_MODE ; 
 int /*<<< orphan*/  max8997_haptic_configure (struct max8997_haptic*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwm_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max8997_haptic_disable(struct max8997_haptic *chip)
{
	mutex_lock(&chip->mutex);

	if (chip->enabled) {
		chip->enabled = false;
		max8997_haptic_configure(chip);
		if (chip->mode == MAX8997_EXTERNAL_MODE)
			pwm_disable(chip->pwm);
		regulator_disable(chip->regulator);
	}

	mutex_unlock(&chip->mutex);
}