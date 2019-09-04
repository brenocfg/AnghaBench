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

/* Variables and functions */
 int /*<<< orphan*/  CM_CLKEN ; 
 int EN_APLL_LOCKED ; 
 int /*<<< orphan*/  PLL_MOD ; 
 int omap2_cm_read_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap2_cm_write_mod_reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap2xxx_cm_wait_module_ready (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int _omap2xxx_apll_enable(u8 enable_bit, u8 status_bit)
{
	u32 v, m;

	m = EN_APLL_LOCKED << enable_bit;

	v = omap2_cm_read_mod_reg(PLL_MOD, CM_CLKEN);
	if (v & m)
		return 0;   /* apll already enabled */

	v |= m;
	omap2_cm_write_mod_reg(v, PLL_MOD, CM_CLKEN);

	omap2xxx_cm_wait_module_ready(0, PLL_MOD, 1, status_bit);

	/*
	 * REVISIT: Should we return an error code if
	 * omap2xxx_cm_wait_module_ready() fails?
	 */
	return 0;
}