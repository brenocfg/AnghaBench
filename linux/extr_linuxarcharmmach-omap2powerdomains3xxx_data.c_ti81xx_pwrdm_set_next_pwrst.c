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
struct powerdomain {int /*<<< orphan*/  prcm_offs; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_POWERSTATE_MASK ; 
 int OMAP_POWERSTATE_SHIFT ; 
 int /*<<< orphan*/  TI81XX_PM_PWSTCTRL ; 
 int /*<<< orphan*/  omap2_prm_rmw_mod_reg_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti81xx_pwrdm_set_next_pwrst(struct powerdomain *pwrdm, u8 pwrst)
{
	omap2_prm_rmw_mod_reg_bits(OMAP_POWERSTATE_MASK,
				   (pwrst << OMAP_POWERSTATE_SHIFT),
				   pwrdm->prcm_offs, TI81XX_PM_PWSTCTRL);
	return 0;
}