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
struct sh_pfc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int RCAR_GP_PIN (int,int) ; 

__attribute__((used)) static int r8a77470_pin_to_pocctrl(struct sh_pfc *pfc, unsigned int pin,
				   u32 *pocctrl)
{
	int bit = -EINVAL;

	*pocctrl = 0xe60600b0;

	if (pin >= RCAR_GP_PIN(0, 5) && pin <= RCAR_GP_PIN(0, 10))
		bit = 0;

	if (pin >= RCAR_GP_PIN(0, 13) && pin <= RCAR_GP_PIN(0, 22))
		bit = 2;

	if (pin >= RCAR_GP_PIN(4, 14) && pin <= RCAR_GP_PIN(4, 19))
		bit = 1;

	return bit;
}