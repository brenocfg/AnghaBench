#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* ptr; } ;
struct clockdomain {int dep_bit; TYPE_2__ pwrdm; } ;
struct TYPE_3__ {int /*<<< orphan*/  prcm_offs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM_WKDEP ; 
 int omap2_prm_read_mod_bits_shift (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int omap2_clkdm_read_wkdep(struct clockdomain *clkdm1,
			   struct clockdomain *clkdm2)
{
	return omap2_prm_read_mod_bits_shift(clkdm1->pwrdm.ptr->prcm_offs,
					     PM_WKDEP, (1 << clkdm2->dep_bit));
}