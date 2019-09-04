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
struct max77693_haptic {int enabled; int /*<<< orphan*/  pwm_dev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int max77693_haptic_configure (struct max77693_haptic*,int) ; 
 int max77693_haptic_lowsys (struct max77693_haptic*,int) ; 
 int /*<<< orphan*/  pwm_disable (int /*<<< orphan*/ ) ; 
 int pwm_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max77693_haptic_enable(struct max77693_haptic *haptic)
{
	int error;

	if (haptic->enabled)
		return;

	error = pwm_enable(haptic->pwm_dev);
	if (error) {
		dev_err(haptic->dev,
			"failed to enable haptic pwm device: %d\n", error);
		return;
	}

	error = max77693_haptic_lowsys(haptic, true);
	if (error)
		goto err_enable_lowsys;

	error = max77693_haptic_configure(haptic, true);
	if (error)
		goto err_enable_config;

	haptic->enabled = true;

	return;

err_enable_config:
	max77693_haptic_lowsys(haptic, false);
err_enable_lowsys:
	pwm_disable(haptic->pwm_dev);
}