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
struct hid_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {char* name; int /*<<< orphan*/  flags; int /*<<< orphan*/  (* brightness_set_blocking ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  max_brightness; } ;
struct hammer_kbd_leds {TYPE_1__ cdev; struct hid_device* hdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LED_HW_PLUGGABLE ; 
 int /*<<< orphan*/  MAX_BRIGHTNESS ; 
 struct hammer_kbd_leds* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_led_classdev_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  hammer_kbd_brightness_set_blocking (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hammer_register_leds(struct hid_device *hdev)
{
	struct hammer_kbd_leds *kbd_backlight;

	kbd_backlight = devm_kzalloc(&hdev->dev,
				     sizeof(*kbd_backlight),
				     GFP_KERNEL);
	if (!kbd_backlight)
		return -ENOMEM;

	kbd_backlight->hdev = hdev;
	kbd_backlight->cdev.name = "hammer::kbd_backlight";
	kbd_backlight->cdev.max_brightness = MAX_BRIGHTNESS;
	kbd_backlight->cdev.brightness_set_blocking =
		hammer_kbd_brightness_set_blocking;
	kbd_backlight->cdev.flags = LED_HW_PLUGGABLE;

	/* Set backlight to 0% initially. */
	hammer_kbd_brightness_set_blocking(&kbd_backlight->cdev, 0);

	return devm_led_classdev_register(&hdev->dev, &kbd_backlight->cdev);
}