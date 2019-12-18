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
struct TYPE_2__ {int brightness; } ;
struct an30259a_led {int default_state; TYPE_1__ cdev; int /*<<< orphan*/  num; struct an30259a* chip; } ;
struct an30259a {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int AN30259A_LED_EN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AN30259A_REG_LEDCC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AN30259A_REG_LED_ON ; 
 int LED_FULL ; 
 void* LED_OFF ; 
#define  STATE_KEEP 129 
#define  STATE_ON 128 
 int /*<<< orphan*/  an30259a_brightness_set (TYPE_1__*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void an30259a_init_default_state(struct an30259a_led *led)
{
	struct an30259a *chip = led->chip;
	int led_on, err;

	switch (led->default_state) {
	case STATE_ON:
		led->cdev.brightness = LED_FULL;
		break;
	case STATE_KEEP:
		err = regmap_read(chip->regmap, AN30259A_REG_LED_ON, &led_on);
		if (err)
			break;

		if (!(led_on & AN30259A_LED_EN(led->num))) {
			led->cdev.brightness = LED_OFF;
			break;
		}
		regmap_read(chip->regmap, AN30259A_REG_LEDCC(led->num),
			    &led->cdev.brightness);
		break;
	default:
		led->cdev.brightness = LED_OFF;
	}

	an30259a_brightness_set(&led->cdev, led->cdev.brightness);
}