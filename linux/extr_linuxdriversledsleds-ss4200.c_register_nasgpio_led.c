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
struct nasgpio_led {int /*<<< orphan*/  name; } ;
struct led_classdev {int /*<<< orphan*/  groups; int /*<<< orphan*/  blink_set; int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  brightness; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GP_LVL ; 
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 struct led_classdev* get_classdev_for_led_nr (int) ; 
 int led_classdev_register (int /*<<< orphan*/ *,struct led_classdev*) ; 
 TYPE_1__* nas_gpio_pci_dev ; 
 scalar_t__ nasgpio_led_get_attr (struct led_classdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nasgpio_led_groups ; 
 int /*<<< orphan*/  nasgpio_led_set_blink ; 
 int /*<<< orphan*/  nasgpio_led_set_brightness ; 
 struct nasgpio_led* nasgpio_leds ; 

__attribute__((used)) static int register_nasgpio_led(int led_nr)
{
	int ret;
	struct nasgpio_led *nas_led = &nasgpio_leds[led_nr];
	struct led_classdev *led = get_classdev_for_led_nr(led_nr);

	led->name = nas_led->name;
	led->brightness = LED_OFF;
	if (nasgpio_led_get_attr(led, GP_LVL))
		led->brightness = LED_FULL;
	led->brightness_set = nasgpio_led_set_brightness;
	led->blink_set = nasgpio_led_set_blink;
	led->groups = nasgpio_led_groups;
	ret = led_classdev_register(&nas_gpio_pci_dev->dev, led);
	if (ret)
		return ret;

	return 0;
}