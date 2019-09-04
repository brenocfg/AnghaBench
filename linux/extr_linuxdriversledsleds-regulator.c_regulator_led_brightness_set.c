#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int max_brightness; int /*<<< orphan*/  dev; } ;
struct regulator_led {int /*<<< orphan*/  mutex; TYPE_1__ cdev; int /*<<< orphan*/  vcc; } ;
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int LED_OFF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int led_regulator_get_voltage (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_led_disable (struct regulator_led*) ; 
 int /*<<< orphan*/  regulator_led_enable (struct regulator_led*) ; 
 int regulator_set_voltage (int /*<<< orphan*/ ,int,int) ; 
 struct regulator_led* to_regulator_led (struct led_classdev*) ; 

__attribute__((used)) static int regulator_led_brightness_set(struct led_classdev *led_cdev,
					 enum led_brightness value)
{
	struct regulator_led *led = to_regulator_led(led_cdev);
	int voltage;
	int ret = 0;

	mutex_lock(&led->mutex);

	if (value == LED_OFF) {
		regulator_led_disable(led);
		goto out;
	}

	if (led->cdev.max_brightness > 1) {
		voltage = led_regulator_get_voltage(led->vcc, value);
		dev_dbg(led->cdev.dev, "brightness: %d voltage: %d\n",
				value, voltage);

		ret = regulator_set_voltage(led->vcc, voltage, voltage);
		if (ret != 0)
			dev_err(led->cdev.dev, "Failed to set voltage %d: %d\n",
				voltage, ret);
	}

	regulator_led_enable(led);

out:
	mutex_unlock(&led->mutex);
	return ret;
}