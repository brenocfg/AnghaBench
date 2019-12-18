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
struct picolcd_data {struct led_classdev** led; } ;
struct led_classdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct led_classdev*) ; 
 int /*<<< orphan*/  led_classdev_unregister (struct led_classdev*) ; 

void picolcd_exit_leds(struct picolcd_data *data)
{
	struct led_classdev *led;
	int i;

	for (i = 0; i < 8; i++) {
		led = data->led[i];
		data->led[i] = NULL;
		if (!led)
			continue;
		led_classdev_unregister(led);
		kfree(led);
	}
}