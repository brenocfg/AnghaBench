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
struct led_classdev_flash {int dummy; } ;
struct led_classdev {int dummy; } ;
struct as3645a {int assist_current; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int /*<<< orphan*/  AS_MODE_ASSIST ; 
 int as3645a_set_control (struct as3645a*,int /*<<< orphan*/ ,int) ; 
 int as3645a_set_current (struct as3645a*) ; 
 struct as3645a* fled_to_as3645a (struct led_classdev_flash*) ; 
 struct led_classdev_flash* lcdev_to_flcdev (struct led_classdev*) ; 

__attribute__((used)) static int as3645a_set_assist_brightness(struct led_classdev *fled_cdev,
					 enum led_brightness brightness)
{
	struct led_classdev_flash *fled = lcdev_to_flcdev(fled_cdev);
	struct as3645a *flash = fled_to_as3645a(fled);
	int rval;

	if (brightness) {
		/* Register value 0 is 20 mA. */
		flash->assist_current = brightness - 1;

		rval = as3645a_set_current(flash);
		if (rval)
			return rval;
	}

	return as3645a_set_control(flash, AS_MODE_ASSIST, brightness);
}