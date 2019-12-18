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
struct max77693_haptic {int enabled; int /*<<< orphan*/  pwm_dev; } ;

/* Variables and functions */
 int max77693_haptic_configure (struct max77693_haptic*,int) ; 
 int max77693_haptic_lowsys (struct max77693_haptic*,int) ; 
 int /*<<< orphan*/  pwm_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max77693_haptic_disable(struct max77693_haptic *haptic)
{
	int error;

	if (!haptic->enabled)
		return;

	error = max77693_haptic_configure(haptic, false);
	if (error)
		return;

	error = max77693_haptic_lowsys(haptic, false);
	if (error)
		goto err_disable_lowsys;

	pwm_disable(haptic->pwm_dev);
	haptic->enabled = false;

	return;

err_disable_lowsys:
	max77693_haptic_configure(haptic, true);
}