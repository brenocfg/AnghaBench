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
struct powerdomain {int /*<<< orphan*/  context; int /*<<< orphan*/  pwrstctrl_offs; int /*<<< orphan*/  prcm_offs; int /*<<< orphan*/  prcm_partition; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP4430_LOWPOWERSTATECHANGE_MASK ; 
 int /*<<< orphan*/  omap4_prminst_read_inst_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap4_pwrdm_save_context(struct powerdomain *pwrdm)
{
	pwrdm->context = omap4_prminst_read_inst_reg(pwrdm->prcm_partition,
						     pwrdm->prcm_offs,
						     pwrdm->pwrstctrl_offs);

	/*
	 * Do not save LOWPOWERSTATECHANGE, writing a 1 indicates a request,
	 * reading back a 1 indicates a request in progress.
	 */
	pwrdm->context &= ~OMAP4430_LOWPOWERSTATECHANGE_MASK;
}