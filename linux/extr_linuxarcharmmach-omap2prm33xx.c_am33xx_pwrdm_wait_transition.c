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
typedef  scalar_t__ u32 ;
struct powerdomain {int /*<<< orphan*/  name; int /*<<< orphan*/  pwrstst_offs; int /*<<< orphan*/  prcm_offs; } ;

/* Variables and functions */
 int EAGAIN ; 
 int OMAP_INTRANSITION_MASK ; 
 scalar_t__ PWRDM_TRANSITION_BAILOUT ; 
 int am33xx_prm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int am33xx_pwrdm_wait_transition(struct powerdomain *pwrdm)
{
	u32 c = 0;

	/*
	 * REVISIT: pwrdm_wait_transition() may be better implemented
	 * via a callback and a periodic timer check -- how long do we expect
	 * powerdomain transitions to take?
	 */

	/* XXX Is this udelay() value meaningful? */
	while ((am33xx_prm_read_reg(pwrdm->prcm_offs, pwrdm->pwrstst_offs)
			& OMAP_INTRANSITION_MASK) &&
			(c++ < PWRDM_TRANSITION_BAILOUT))
		udelay(1);

	if (c > PWRDM_TRANSITION_BAILOUT) {
		pr_err("powerdomain: %s: waited too long to complete transition\n",
		       pwrdm->name);
		return -EAGAIN;
	}

	pr_debug("powerdomain: completed transition in %d loops\n", c);

	return 0;
}