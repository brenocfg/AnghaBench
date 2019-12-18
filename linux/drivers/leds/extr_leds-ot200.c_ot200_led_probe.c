#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_2__ cdev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ BIT (int) ; 
 int devm_led_classdev_register (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_1__* leds ; 
 scalar_t__ leds_back ; 
 scalar_t__ leds_front ; 
 int /*<<< orphan*/  ot200_led_brightness_set ; 
 int /*<<< orphan*/  outb (scalar_t__,int) ; 

__attribute__((used)) static int ot200_led_probe(struct platform_device *pdev)
{
	int i;
	int ret;

	for (i = 0; i < ARRAY_SIZE(leds); i++) {

		leds[i].cdev.name = leds[i].name;
		leds[i].cdev.brightness_set = ot200_led_brightness_set;

		ret = devm_led_classdev_register(&pdev->dev, &leds[i].cdev);
		if (ret < 0)
			return ret;
	}

	leds_front = 0;		/* turn off all front leds */
	leds_back = BIT(1);	/* turn on init led */
	outb(leds_front, 0x49);
	outb(leds_back, 0x5a);

	return 0;
}