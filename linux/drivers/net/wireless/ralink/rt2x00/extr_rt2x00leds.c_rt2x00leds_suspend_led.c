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
struct TYPE_3__ {int /*<<< orphan*/  brightness; int /*<<< orphan*/  (* brightness_set ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct rt2x00_led {TYPE_1__ led_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  led_classdev_suspend (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rt2x00leds_suspend_led(struct rt2x00_led *led)
{
	led_classdev_suspend(&led->led_dev);

	/* This shouldn't be needed, but just to be safe */
	led->led_dev.brightness_set(&led->led_dev, LED_OFF);
	led->led_dev.brightness = LED_OFF;
}