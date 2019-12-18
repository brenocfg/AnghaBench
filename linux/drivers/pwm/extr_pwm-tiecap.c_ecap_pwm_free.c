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
struct pwm_device {int dummy; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ pwm_is_enabled (struct pwm_device*) ; 

__attribute__((used)) static void ecap_pwm_free(struct pwm_chip *chip, struct pwm_device *pwm)
{
	if (pwm_is_enabled(pwm)) {
		dev_warn(chip->dev, "Removing PWM device without disabling\n");
		pm_runtime_put_sync(chip->dev);
	}
}