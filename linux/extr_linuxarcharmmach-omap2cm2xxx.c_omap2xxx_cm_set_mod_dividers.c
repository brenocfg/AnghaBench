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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CM_CLKSEL ; 
 int /*<<< orphan*/  CM_CLKSEL1 ; 
 int /*<<< orphan*/  CORE_MOD ; 
 int /*<<< orphan*/  GFX_MOD ; 
 int /*<<< orphan*/  MPU_MOD ; 
 int /*<<< orphan*/  OMAP2430_MDM_MOD ; 
 int OMAP24XX_CLKSEL_DSS2_MASK ; 
 int /*<<< orphan*/  OMAP24XX_DSP_MOD ; 
 int omap2_cm_read_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap2_cm_write_mod_reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void omap2xxx_cm_set_mod_dividers(u32 mpu, u32 dsp, u32 gfx, u32 core, u32 mdm)
{
	u32 tmp;

	omap2_cm_write_mod_reg(mpu, MPU_MOD, CM_CLKSEL);
	omap2_cm_write_mod_reg(dsp, OMAP24XX_DSP_MOD, CM_CLKSEL);
	omap2_cm_write_mod_reg(gfx, GFX_MOD, CM_CLKSEL);
	tmp = omap2_cm_read_mod_reg(CORE_MOD, CM_CLKSEL1) &
		OMAP24XX_CLKSEL_DSS2_MASK;
	omap2_cm_write_mod_reg(core | tmp, CORE_MOD, CM_CLKSEL1);
	if (mdm)
		omap2_cm_write_mod_reg(mdm, OMAP2430_MDM_MOD, CM_CLKSEL);
}