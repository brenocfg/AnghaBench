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
typedef  int u32 ;
struct led_classdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPO_BLINK ; 
 int /*<<< orphan*/  nasgpio_led_set_attr (struct led_classdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nasgpio_led_set_blink(struct led_classdev *led_cdev,
				 unsigned long *delay_on,
				 unsigned long *delay_off)
{
	u32 setting = 1;
	if (!(*delay_on == 0 && *delay_off == 0) &&
	    !(*delay_on == 500 && *delay_off == 500))
		return -EINVAL;
	/*
	 * These are very approximate.
	 */
	*delay_on = 500;
	*delay_off = 500;

	nasgpio_led_set_attr(led_cdev, GPO_BLINK, setting);

	return 0;
}