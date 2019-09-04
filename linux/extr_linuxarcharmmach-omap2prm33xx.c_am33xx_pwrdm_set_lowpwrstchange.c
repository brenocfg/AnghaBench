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
struct powerdomain {int /*<<< orphan*/  pwrstctrl_offs; int /*<<< orphan*/  prcm_offs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM33XX_LOWPOWERSTATECHANGE_MASK ; 
 int AM33XX_LOWPOWERSTATECHANGE_SHIFT ; 
 int /*<<< orphan*/  am33xx_prm_rmw_reg_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int am33xx_pwrdm_set_lowpwrstchange(struct powerdomain *pwrdm)
{
	am33xx_prm_rmw_reg_bits(AM33XX_LOWPOWERSTATECHANGE_MASK,
				(1 << AM33XX_LOWPOWERSTATECHANGE_SHIFT),
				pwrdm->prcm_offs, pwrdm->pwrstctrl_offs);
	return 0;
}