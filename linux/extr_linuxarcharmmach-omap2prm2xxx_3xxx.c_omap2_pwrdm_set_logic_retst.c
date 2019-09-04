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
typedef  int u8 ;
typedef  int u32 ;
struct powerdomain {int /*<<< orphan*/  prcm_offs; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP2_PM_PWSTCTRL ; 
 int /*<<< orphan*/  OMAP_LOGICRETSTATE_MASK ; 
 int __ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap2_prm_rmw_mod_reg_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int omap2_pwrdm_set_logic_retst(struct powerdomain *pwrdm, u8 pwrst)
{
	u32 v;

	v = pwrst << __ffs(OMAP_LOGICRETSTATE_MASK);
	omap2_prm_rmw_mod_reg_bits(OMAP_LOGICRETSTATE_MASK, v, pwrdm->prcm_offs,
				   OMAP2_PM_PWSTCTRL);

	return 0;
}