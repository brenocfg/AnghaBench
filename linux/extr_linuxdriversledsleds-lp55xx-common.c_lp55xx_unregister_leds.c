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
struct lp55xx_led {int /*<<< orphan*/  cdev; } ;
struct lp55xx_chip {int num_leds; } ;

/* Variables and functions */
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 

void lp55xx_unregister_leds(struct lp55xx_led *led, struct lp55xx_chip *chip)
{
	int i;
	struct lp55xx_led *each;

	for (i = 0; i < chip->num_leds; i++) {
		each = led + i;
		led_classdev_unregister(&each->cdev);
	}
}