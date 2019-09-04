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
struct clockdomain {int flags; int /*<<< orphan*/  clkdm_offs; int /*<<< orphan*/  cm_inst; int /*<<< orphan*/  prcm_partition; } ;

/* Variables and functions */
 int CLKDM_CAN_FORCE_SLEEP ; 
 int CLKDM_CAN_HWSUP ; 
 int EINVAL ; 
 int /*<<< orphan*/  omap4_cminst_clkdm_enable_hwsup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4_cminst_clkdm_force_sleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap4_clkdm_sleep(struct clockdomain *clkdm)
{
	if (clkdm->flags & CLKDM_CAN_HWSUP)
		omap4_cminst_clkdm_enable_hwsup(clkdm->prcm_partition,
						clkdm->cm_inst,
						clkdm->clkdm_offs);
	else if (clkdm->flags & CLKDM_CAN_FORCE_SLEEP)
		omap4_cminst_clkdm_force_sleep(clkdm->prcm_partition,
					       clkdm->cm_inst,
					       clkdm->clkdm_offs);
	else
		return -EINVAL;

	return 0;
}