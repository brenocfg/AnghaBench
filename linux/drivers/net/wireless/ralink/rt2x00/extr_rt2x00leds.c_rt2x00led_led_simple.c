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
struct TYPE_2__ {unsigned int brightness; int /*<<< orphan*/  (* brightness_set ) (TYPE_1__*,unsigned int) ;} ;
struct rt2x00_led {int flags; TYPE_1__ led_dev; } ;

/* Variables and functions */
 unsigned int LED_FULL ; 
 unsigned int LED_OFF ; 
 int LED_REGISTERED ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static void rt2x00led_led_simple(struct rt2x00_led *led, bool enabled)
{
	unsigned int brightness = enabled ? LED_FULL : LED_OFF;

	if (!(led->flags & LED_REGISTERED))
		return;

	led->led_dev.brightness_set(&led->led_dev, brightness);
	led->led_dev.brightness = brightness;
}