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
struct clockdomain {int flags; int /*<<< orphan*/  clkdm_offs; int /*<<< orphan*/  cm_inst; } ;

/* Variables and functions */
 int CLKDM_CAN_FORCE_SLEEP ; 
 int /*<<< orphan*/  am33xx_clkdm_sleep (struct clockdomain*) ; 
 int am33xx_cm_is_clkdm_in_hwsup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int am33xx_clkdm_clk_disable(struct clockdomain *clkdm)
{
	bool hwsup = false;

	hwsup = am33xx_cm_is_clkdm_in_hwsup(clkdm->cm_inst, clkdm->clkdm_offs);

	if (!hwsup && (clkdm->flags & CLKDM_CAN_FORCE_SLEEP))
		am33xx_clkdm_sleep(clkdm);

	return 0;
}