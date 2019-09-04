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
struct sc27xx_led {TYPE_1__* priv; } ;
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int LED_OFF ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sc27xx_led_disable (struct sc27xx_led*) ; 
 int sc27xx_led_enable (struct sc27xx_led*,int) ; 
 struct sc27xx_led* to_sc27xx_led (struct led_classdev*) ; 

__attribute__((used)) static int sc27xx_led_set(struct led_classdev *ldev, enum led_brightness value)
{
	struct sc27xx_led *leds = to_sc27xx_led(ldev);
	int err;

	mutex_lock(&leds->priv->lock);

	if (value == LED_OFF)
		err = sc27xx_led_disable(leds);
	else
		err = sc27xx_led_enable(leds, value);

	mutex_unlock(&leds->priv->lock);

	return err;
}