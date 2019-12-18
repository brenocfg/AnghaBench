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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct wm8350_led {int value; int max_uA_index; TYPE_1__ cdev; int /*<<< orphan*/  isink; int /*<<< orphan*/  value_lock; } ;
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int LED_FULL ; 
 int LED_OFF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * isink_cur ; 
 int regulator_set_current_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct wm8350_led* to_wm8350_led (struct led_classdev*) ; 
 int wm8350_led_disable (struct wm8350_led*) ; 
 int wm8350_led_enable (struct wm8350_led*) ; 

__attribute__((used)) static int wm8350_led_set(struct led_classdev *led_cdev,
			   enum led_brightness value)
{
	struct wm8350_led *led = to_wm8350_led(led_cdev);
	unsigned long flags;
	int ret;
	int uA;

	led->value = value;

	spin_lock_irqsave(&led->value_lock, flags);

	if (led->value == LED_OFF) {
		spin_unlock_irqrestore(&led->value_lock, flags);
		return wm8350_led_disable(led);
	}

	/* This scales linearly into the index of valid current
	 * settings which results in a linear scaling of perceived
	 * brightness due to the non-linear current settings provided
	 * by the hardware.
	 */
	uA = (led->max_uA_index * led->value) / LED_FULL;
	spin_unlock_irqrestore(&led->value_lock, flags);
	BUG_ON(uA >= ARRAY_SIZE(isink_cur));

	ret = regulator_set_current_limit(led->isink, isink_cur[uA],
					  isink_cur[uA]);
	if (ret != 0) {
		dev_err(led->cdev.dev, "Failed to set %duA: %d\n",
			isink_cur[uA], ret);
		return ret;
	}

	return wm8350_led_enable(led);
}