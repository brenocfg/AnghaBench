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
typedef  int u8 ;
struct max77693_led_device {int mode_flags; scalar_t__ iout_joint; } ;

/* Variables and functions */
 int max77693_set_mode_reg (struct max77693_led_device*,int) ; 

__attribute__((used)) static int max77693_clear_mode(struct max77693_led_device *led,
				u8 mode)
{
	if (led->iout_joint)
		/* Clear mode also on FLED2 for joint iouts case */
		mode |= (mode << 1);

	led->mode_flags &= ~mode;

	return max77693_set_mode_reg(led, led->mode_flags);
}