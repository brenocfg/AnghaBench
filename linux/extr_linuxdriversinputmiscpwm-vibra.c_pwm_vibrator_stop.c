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
struct pwm_vibrator {int vcc_on; int /*<<< orphan*/  vcc; scalar_t__ pwm; scalar_t__ pwm_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  pwm_disable (scalar_t__) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pwm_vibrator_stop(struct pwm_vibrator *vibrator)
{
	if (vibrator->pwm_dir)
		pwm_disable(vibrator->pwm_dir);
	pwm_disable(vibrator->pwm);

	if (vibrator->vcc_on) {
		regulator_disable(vibrator->vcc);
		vibrator->vcc_on = false;
	}
}