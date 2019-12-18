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
struct wacom_led {int hlv; int llv; struct wacom* wacom; } ;
struct TYPE_2__ {int max_hlv; int max_llv; } ;
struct wacom {TYPE_1__ led; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int LED_FULL ; 

enum led_brightness wacom_leds_brightness_get(struct wacom_led *led)
{
	struct wacom *wacom = led->wacom;

	if (wacom->led.max_hlv)
		return led->hlv * LED_FULL / wacom->led.max_hlv;

	if (wacom->led.max_llv)
		return led->llv * LED_FULL / wacom->led.max_llv;

	/* device doesn't support brightness tuning */
	return LED_FULL;
}