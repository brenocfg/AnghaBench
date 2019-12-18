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

/* Variables and functions */
#define  HUB_LED_AMBER 131 
#define  HUB_LED_AUTO 130 
#define  HUB_LED_GREEN 129 
#define  HUB_LED_OFF 128 

__attribute__((used)) static char *to_led_name(int selector)
{
	switch (selector) {
	case HUB_LED_AMBER:
		return "amber";
	case HUB_LED_GREEN:
		return "green";
	case HUB_LED_OFF:
		return "off";
	case HUB_LED_AUTO:
		return "auto";
	default:
		return "??";
	}
}