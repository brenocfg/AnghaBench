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
typedef  int /*<<< orphan*/  u32 ;
struct powerdomain {int /*<<< orphan*/  prcm_offs; int /*<<< orphan*/  prcm_partition; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP4_PM_PWSTCTRL ; 
 int __ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap2_pwrdm_get_mem_bank_retst_mask (int) ; 
 int /*<<< orphan*/  omap4_prminst_rmw_inst_reg_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap4_pwrdm_set_mem_retst(struct powerdomain *pwrdm, u8 bank,
				     u8 pwrst)
{
	u32 m;

	m = omap2_pwrdm_get_mem_bank_retst_mask(bank);

	omap4_prminst_rmw_inst_reg_bits(m, (pwrst << __ffs(m)),
					pwrdm->prcm_partition, pwrdm->prcm_offs,
					OMAP4_PM_PWSTCTRL);

	return 0;
}