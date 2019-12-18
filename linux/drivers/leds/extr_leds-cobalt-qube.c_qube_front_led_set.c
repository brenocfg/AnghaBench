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
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int LED_FRONT_LEFT ; 
 int LED_FRONT_RIGHT ; 
 int /*<<< orphan*/  led_port ; 
 int led_value ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qube_front_led_set(struct led_classdev *led_cdev,
			       enum led_brightness brightness)
{
	if (brightness)
		led_value = LED_FRONT_LEFT | LED_FRONT_RIGHT;
	else
		led_value = ~(LED_FRONT_LEFT | LED_FRONT_RIGHT);
	writeb(led_value, led_port);
}