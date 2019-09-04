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
struct input_leds {int num_leds; struct input_led* leds; } ;
struct TYPE_2__ {struct input_leds* name; } ;
struct input_led {TYPE_1__ cdev; } ;
struct input_handle {struct input_leds* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_close_device (struct input_handle*) ; 
 int /*<<< orphan*/  input_unregister_handle (struct input_handle*) ; 
 int /*<<< orphan*/  kfree (struct input_leds*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 

__attribute__((used)) static void input_leds_disconnect(struct input_handle *handle)
{
	struct input_leds *leds = handle->private;
	int i;

	for (i = 0; i < leds->num_leds; i++) {
		struct input_led *led = &leds->leds[i];

		led_classdev_unregister(&led->cdev);
		kfree(led->cdev.name);
	}

	input_close_device(handle);
	input_unregister_handle(handle);

	kfree(leds);
}