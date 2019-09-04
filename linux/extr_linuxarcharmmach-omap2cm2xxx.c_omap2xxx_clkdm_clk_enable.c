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
struct clockdomain {int flags; int /*<<< orphan*/  clktrctrl_mask; TYPE_2__ pwrdm; } ;
struct TYPE_3__ {int /*<<< orphan*/  prcm_offs; } ;

/* Variables and functions */
 int CLKDM_CAN_FORCE_WAKEUP ; 
 int /*<<< orphan*/  omap2xxx_clkdm_wakeup (struct clockdomain*) ; 
 int omap2xxx_cm_is_clkdm_in_hwsup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap2xxx_clkdm_clk_enable(struct clockdomain *clkdm)
{
	bool hwsup = false;

	if (!clkdm->clktrctrl_mask)
		return 0;

	hwsup = omap2xxx_cm_is_clkdm_in_hwsup(clkdm->pwrdm.ptr->prcm_offs,
					      clkdm->clktrctrl_mask);
	if (!hwsup && clkdm->flags & CLKDM_CAN_FORCE_WAKEUP)
		omap2xxx_clkdm_wakeup(clkdm);

	return 0;
}