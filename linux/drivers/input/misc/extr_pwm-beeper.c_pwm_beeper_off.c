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
struct pwm_beeper {int amplifier_on; int /*<<< orphan*/  pwm; int /*<<< orphan*/  amplifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  pwm_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pwm_beeper_off(struct pwm_beeper *beeper)
{
	if (beeper->amplifier_on) {
		regulator_disable(beeper->amplifier);
		beeper->amplifier_on = false;
	}

	pwm_disable(beeper->pwm);
}