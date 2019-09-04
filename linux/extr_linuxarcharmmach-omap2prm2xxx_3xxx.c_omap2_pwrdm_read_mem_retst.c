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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct powerdomain {int /*<<< orphan*/  prcm_offs; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP2_PM_PWSTCTRL ; 
 int omap2_prm_read_mod_bits_shift (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap2_pwrdm_get_mem_bank_retst_mask (int /*<<< orphan*/ ) ; 

int omap2_pwrdm_read_mem_retst(struct powerdomain *pwrdm, u8 bank)
{
	u32 m;

	m = omap2_pwrdm_get_mem_bank_retst_mask(bank);

	return omap2_prm_read_mod_bits_shift(pwrdm->prcm_offs,
					     OMAP2_PM_PWSTCTRL, m);
}