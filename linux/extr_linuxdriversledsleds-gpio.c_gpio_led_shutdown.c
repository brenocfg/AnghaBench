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
struct platform_device {int dummy; } ;
struct gpio_leds_priv {int num_leds; struct gpio_led_data* leds; } ;
struct TYPE_2__ {int flags; } ;
struct gpio_led_data {TYPE_1__ cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_OFF ; 
 int LED_RETAIN_AT_SHUTDOWN ; 
 int /*<<< orphan*/  gpio_led_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct gpio_leds_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void gpio_led_shutdown(struct platform_device *pdev)
{
	struct gpio_leds_priv *priv = platform_get_drvdata(pdev);
	int i;

	for (i = 0; i < priv->num_leds; i++) {
		struct gpio_led_data *led = &priv->leds[i];

		if (!(led->cdev.flags & LED_RETAIN_AT_SHUTDOWN))
			gpio_led_set(&led->cdev, LED_OFF);
	}
}