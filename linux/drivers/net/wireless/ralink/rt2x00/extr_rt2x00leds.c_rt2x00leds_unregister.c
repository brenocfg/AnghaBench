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
struct TYPE_2__ {int flags; } ;
struct rt2x00_dev {TYPE_1__ led_radio; TYPE_1__ led_assoc; TYPE_1__ led_qual; } ;

/* Variables and functions */
 int LED_REGISTERED ; 
 int /*<<< orphan*/  rt2x00leds_unregister_led (TYPE_1__*) ; 

void rt2x00leds_unregister(struct rt2x00_dev *rt2x00dev)
{
	if (rt2x00dev->led_qual.flags & LED_REGISTERED)
		rt2x00leds_unregister_led(&rt2x00dev->led_qual);
	if (rt2x00dev->led_assoc.flags & LED_REGISTERED)
		rt2x00leds_unregister_led(&rt2x00dev->led_assoc);
	if (rt2x00dev->led_radio.flags & LED_REGISTERED)
		rt2x00leds_unregister_led(&rt2x00dev->led_radio);
}