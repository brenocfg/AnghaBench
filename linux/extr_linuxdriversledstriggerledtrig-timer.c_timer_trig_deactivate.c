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

/* Variables and functions */
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  led_set_brightness (struct led_classdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timer_trig_deactivate(struct led_classdev *led_cdev)
{
	/* Stop blinking */
	led_set_brightness(led_cdev, LED_OFF);
}