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
struct led_classdev {int /*<<< orphan*/  brightness; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int /*<<< orphan*/  LED_OFF ; 
 int u2fzero_blink (struct led_classdev*) ; 

__attribute__((used)) static int u2fzero_brightness_set(struct led_classdev *ldev,
				  enum led_brightness brightness)
{
	ldev->brightness = LED_OFF;
	if (brightness)
		return u2fzero_blink(ldev);
	else
		return 0;
}