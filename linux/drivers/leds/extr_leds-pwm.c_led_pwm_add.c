#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pwm_args {scalar_t__ period; } ;
struct led_pwm_priv {size_t num_leds; struct led_pwm_data* leds; } ;
struct TYPE_3__ {int /*<<< orphan*/  brightness; int /*<<< orphan*/  (* brightness_set_blocking ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  flags; int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  name; } ;
struct led_pwm_data {scalar_t__ period; TYPE_1__ cdev; int /*<<< orphan*/  pwm; int /*<<< orphan*/  active_low; } ;
struct led_pwm {scalar_t__ pwm_period_ns; int /*<<< orphan*/  name; int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  active_low; } ;
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_CORE_SUSPENDRESUME ; 
 int /*<<< orphan*/  LED_OFF ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  devm_fwnode_pwm_get (struct device*,struct fwnode_handle*,int /*<<< orphan*/ *) ; 
 int devm_led_classdev_register (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  devm_pwm_get (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_pwm_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_apply_args (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_get_args (int /*<<< orphan*/ ,struct pwm_args*) ; 

__attribute__((used)) static int led_pwm_add(struct device *dev, struct led_pwm_priv *priv,
		       struct led_pwm *led, struct fwnode_handle *fwnode)
{
	struct led_pwm_data *led_data = &priv->leds[priv->num_leds];
	struct pwm_args pargs;
	int ret;

	led_data->active_low = led->active_low;
	led_data->cdev.name = led->name;
	led_data->cdev.default_trigger = led->default_trigger;
	led_data->cdev.brightness = LED_OFF;
	led_data->cdev.max_brightness = led->max_brightness;
	led_data->cdev.flags = LED_CORE_SUSPENDRESUME;

	if (fwnode)
		led_data->pwm = devm_fwnode_pwm_get(dev, fwnode, NULL);
	else
		led_data->pwm = devm_pwm_get(dev, led->name);
	if (IS_ERR(led_data->pwm)) {
		ret = PTR_ERR(led_data->pwm);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "unable to request PWM for %s: %d\n",
				led->name, ret);
		return ret;
	}

	led_data->cdev.brightness_set_blocking = led_pwm_set;

	/*
	 * FIXME: pwm_apply_args() should be removed when switching to the
	 * atomic PWM API.
	 */
	pwm_apply_args(led_data->pwm);

	pwm_get_args(led_data->pwm, &pargs);

	led_data->period = pargs.period;
	if (!led_data->period && (led->pwm_period_ns > 0))
		led_data->period = led->pwm_period_ns;

	ret = devm_led_classdev_register(dev, &led_data->cdev);
	if (ret == 0) {
		priv->num_leds++;
		led_pwm_set(&led_data->cdev, led_data->cdev.brightness);
	} else {
		dev_err(dev, "failed to register PWM led for %s: %d\n",
			led->name, ret);
	}

	return ret;
}