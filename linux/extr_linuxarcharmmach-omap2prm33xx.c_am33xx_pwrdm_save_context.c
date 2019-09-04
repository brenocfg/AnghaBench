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
struct powerdomain {int /*<<< orphan*/  context; int /*<<< orphan*/  pwrstctrl_offs; int /*<<< orphan*/  prcm_offs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM33XX_LOWPOWERSTATECHANGE_MASK ; 
 int /*<<< orphan*/  am33xx_prm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void am33xx_pwrdm_save_context(struct powerdomain *pwrdm)
{
	pwrdm->context = am33xx_prm_read_reg(pwrdm->prcm_offs,
						pwrdm->pwrstctrl_offs);
	/*
	 * Do not save LOWPOWERSTATECHANGE, writing a 1 indicates a request,
	 * reading back a 1 indicates a request in progress.
	 */
	pwrdm->context &= ~AM33XX_LOWPOWERSTATECHANGE_MASK;
}