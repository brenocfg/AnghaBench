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
struct led_classdev {int dummy; } ;
struct nasgpio_led {struct led_classdev led_cdev; } ;

/* Variables and functions */
 struct nasgpio_led* nasgpio_leds ; 

__attribute__((used)) static struct led_classdev *get_classdev_for_led_nr(int nr)
{
	struct nasgpio_led *nas_led = &nasgpio_leds[nr];
	struct led_classdev *led = &nas_led->led_cdev;
	return led;
}