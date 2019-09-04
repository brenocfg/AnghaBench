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
typedef  int /*<<< orphan*/  u32 ;
struct led_classdev_flash {int dummy; } ;
struct as3645a {int /*<<< orphan*/  flash_current; } ;

/* Variables and functions */
 int /*<<< orphan*/  as3645a_current_to_reg (struct as3645a*,int,int /*<<< orphan*/ ) ; 
 int as3645a_set_current (struct as3645a*) ; 
 struct as3645a* fled_to_as3645a (struct led_classdev_flash*) ; 

__attribute__((used)) static int as3645a_set_flash_brightness(struct led_classdev_flash *fled,
					u32 brightness_ua)
{
	struct as3645a *flash = fled_to_as3645a(fled);

	flash->flash_current = as3645a_current_to_reg(flash, true,
						      brightness_ua);

	return as3645a_set_current(flash);
}