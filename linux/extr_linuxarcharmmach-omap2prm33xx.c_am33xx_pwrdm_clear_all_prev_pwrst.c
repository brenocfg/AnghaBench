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
struct powerdomain {int /*<<< orphan*/  pwrstst_offs; int /*<<< orphan*/  prcm_offs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM33XX_LASTPOWERSTATEENTERED_MASK ; 
 int /*<<< orphan*/  am33xx_prm_rmw_reg_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int am33xx_pwrdm_clear_all_prev_pwrst(struct powerdomain *pwrdm)
{
	am33xx_prm_rmw_reg_bits(AM33XX_LASTPOWERSTATEENTERED_MASK,
				AM33XX_LASTPOWERSTATEENTERED_MASK,
				pwrdm->prcm_offs, pwrdm->pwrstst_offs);
	return 0;
}