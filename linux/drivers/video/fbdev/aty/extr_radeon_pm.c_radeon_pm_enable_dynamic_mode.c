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
struct radeonfb_info {scalar_t__ family; int vram_width; scalar_t__ is_mobility; int /*<<< orphan*/  has_CRTC2; } ;

/* Variables and functions */
 int CFG_ATI_REV_A13 ; 
 int CFG_ATI_REV_ID_MASK ; 
 scalar_t__ CHIP_FAMILY_R300 ; 
 scalar_t__ CHIP_FAMILY_R350 ; 
 scalar_t__ CHIP_FAMILY_RV100 ; 
 scalar_t__ CHIP_FAMILY_RV200 ; 
 scalar_t__ CHIP_FAMILY_RV250 ; 
 scalar_t__ CHIP_FAMILY_RV280 ; 
 scalar_t__ CHIP_FAMILY_RV350 ; 
 int CLK_PIN_CNTL__SCLK_DYN_START_CNTL ; 
 int CLK_PWRMGT_CNTL__ACTIVE_HILO_LAT_MASK ; 
 int CLK_PWRMGT_CNTL__ACTIVE_HILO_LAT__SHIFT ; 
 int CLK_PWRMGT_CNTL__DISP_DYN_STOP_LAT_MASK ; 
 int CLK_PWRMGT_CNTL__DYN_STOP_MODE_MASK ; 
 int CLK_PWRMGT_CNTL__ENGINE_DYNCLK_MODE_MASK ; 
 int /*<<< orphan*/  CNFG_CNTL ; 
 int INPLL (int /*<<< orphan*/ ) ; 
 int INREG (int /*<<< orphan*/ ) ; 
 int MCLK_CNTL__FORCE_MC ; 
 int MCLK_CNTL__FORCE_MCLKA ; 
 int MCLK_CNTL__FORCE_MCLKB ; 
 int MCLK_CNTL__FORCE_YCLKA ; 
 int MCLK_CNTL__FORCE_YCLKB ; 
 int MCLK_CNTL__R300_DISABLE_MC_MCLKA ; 
 int MCLK_CNTL__R300_DISABLE_MC_MCLKB ; 
 int MCLK_MISC__IO_MCLK_DYN_ENABLE ; 
 int MCLK_MISC__IO_MCLK_MAX_DYN_STOP_LAT ; 
 int MCLK_MISC__MC_MCLK_DYN_ENABLE ; 
 int MCLK_MISC__MC_MCLK_MAX_DYN_STOP_LAT ; 
 int /*<<< orphan*/  MEM_CNTL ; 
 int /*<<< orphan*/  OUTPLL (int /*<<< orphan*/ ,int) ; 
 int PIXCLKS_CNTL__DISP_TVOUT_PIXCLK_TV_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__PIX2CLK_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__PIX2CLK_DAC_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__PIXCLK_BLEND_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__PIXCLK_DIG_TMDS_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__PIXCLK_GV_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__PIXCLK_LVDS_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__PIXCLK_TMDS_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__R300_DVOCLK_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__R300_P2G2CLK_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__R300_P2G2CLK_DAC_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__R300_PIXCLK_DVO_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__R300_PIXCLK_TRANS_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__R300_PIXCLK_TVO_ALWAYS_ONb ; 
 int PLL_PWRMGT_CNTL__TCL_BYPASS_DISABLE ; 
 int R300_MEM_USE_CD_CH_ONLY ; 
 int SCLK_CNTL2__R300_CBA_MAX_DYN_STOP_LAT ; 
 int SCLK_CNTL2__R300_FORCE_CBA ; 
 int SCLK_CNTL2__R300_FORCE_GA ; 
 int SCLK_CNTL2__R300_FORCE_TCL ; 
 int SCLK_CNTL2__R300_GA_MAX_DYN_STOP_LAT ; 
 int SCLK_CNTL2__R300_TCL_MAX_DYN_STOP_LAT ; 
 int SCLK_CNTL__DYN_STOP_LAT_MASK ; 
 int SCLK_CNTL__FORCEON_MASK ; 
 int SCLK_CNTL__FORCE_CP ; 
 int SCLK_CNTL__FORCE_DISP1 ; 
 int SCLK_CNTL__FORCE_DISP2 ; 
 int SCLK_CNTL__FORCE_E2 ; 
 int SCLK_CNTL__FORCE_HDP ; 
 int SCLK_CNTL__FORCE_IDCT ; 
 int SCLK_CNTL__FORCE_OV0 ; 
 int SCLK_CNTL__FORCE_PB ; 
 int SCLK_CNTL__FORCE_RB ; 
 int SCLK_CNTL__FORCE_RE ; 
 int SCLK_CNTL__FORCE_SE ; 
 int SCLK_CNTL__FORCE_TAM ; 
 int SCLK_CNTL__FORCE_TDM ; 
 int SCLK_CNTL__FORCE_TOP ; 
 int SCLK_CNTL__FORCE_TV_SCLK ; 
 int SCLK_CNTL__FORCE_VIP ; 
 int SCLK_CNTL__R300_FORCE_PX ; 
 int SCLK_CNTL__R300_FORCE_SR ; 
 int SCLK_CNTL__R300_FORCE_SU ; 
 int SCLK_CNTL__R300_FORCE_TX ; 
 int SCLK_CNTL__R300_FORCE_US ; 
 int SCLK_CNTL__R300_FORCE_VAP ; 
 int SCLK_MORE_CNTL__DISPREGS_MAX_DYN_STOP_LAT ; 
 int SCLK_MORE_CNTL__FORCEON ; 
 int SCLK_MORE_CNTL__MC_GUI_MAX_DYN_STOP_LAT ; 
 int SCLK_MORE_CNTL__MC_HOST_MAX_DYN_STOP_LAT ; 
 int VCLK_ECP_CNTL__PIXCLK_ALWAYS_ONb ; 
 int VCLK_ECP_CNTL__PIXCLK_DAC_ALWAYS_ONb ; 
 int /*<<< orphan*/  pllCLK_PIN_CNTL ; 
 int /*<<< orphan*/  pllCLK_PWRMGT_CNTL ; 
 int /*<<< orphan*/  pllMCLK_CNTL ; 
 int /*<<< orphan*/  pllMCLK_MISC ; 
 int /*<<< orphan*/  pllPIXCLKS_CNTL ; 
 int /*<<< orphan*/  pllPLL_PWRMGT_CNTL ; 
 int /*<<< orphan*/  pllSCLK_CNTL ; 
 int /*<<< orphan*/  pllSCLK_CNTL2 ; 
 int /*<<< orphan*/  pllSCLK_MORE_CNTL ; 
 int /*<<< orphan*/  pllVCLK_ECP_CNTL ; 
 int /*<<< orphan*/  radeon_msleep (int) ; 

__attribute__((used)) static void radeon_pm_enable_dynamic_mode(struct radeonfb_info *rinfo)
{
	u32 tmp;

	/* R100 */
	if (!rinfo->has_CRTC2) {
                tmp = INPLL(pllSCLK_CNTL);

		if ((INREG(CNFG_CNTL) & CFG_ATI_REV_ID_MASK) > CFG_ATI_REV_A13)
                    tmp &= ~(SCLK_CNTL__FORCE_CP	| SCLK_CNTL__FORCE_RB);
                tmp &= ~(SCLK_CNTL__FORCE_HDP		| SCLK_CNTL__FORCE_DISP1 |
			 SCLK_CNTL__FORCE_TOP		| SCLK_CNTL__FORCE_SE   |
			 SCLK_CNTL__FORCE_IDCT		| SCLK_CNTL__FORCE_RE   |
			 SCLK_CNTL__FORCE_PB		| SCLK_CNTL__FORCE_TAM  |
			 SCLK_CNTL__FORCE_TDM);
                OUTPLL(pllSCLK_CNTL, tmp);
		return;
	}

	/* M10/M11 */
	if (rinfo->family == CHIP_FAMILY_RV350) {
		tmp = INPLL(pllSCLK_CNTL2);
		tmp &= ~(SCLK_CNTL2__R300_FORCE_TCL |
			 SCLK_CNTL2__R300_FORCE_GA  |
			 SCLK_CNTL2__R300_FORCE_CBA);
		tmp |=  (SCLK_CNTL2__R300_TCL_MAX_DYN_STOP_LAT |
			 SCLK_CNTL2__R300_GA_MAX_DYN_STOP_LAT  |
			 SCLK_CNTL2__R300_CBA_MAX_DYN_STOP_LAT);
		OUTPLL(pllSCLK_CNTL2, tmp);

		tmp = INPLL(pllSCLK_CNTL);
		tmp &= ~(SCLK_CNTL__FORCE_DISP2 | SCLK_CNTL__FORCE_CP      |
			 SCLK_CNTL__FORCE_HDP   | SCLK_CNTL__FORCE_DISP1   |
			 SCLK_CNTL__FORCE_TOP   | SCLK_CNTL__FORCE_E2      |
			 SCLK_CNTL__R300_FORCE_VAP | SCLK_CNTL__FORCE_IDCT |
			 SCLK_CNTL__FORCE_VIP   | SCLK_CNTL__R300_FORCE_SR |
			 SCLK_CNTL__R300_FORCE_PX | SCLK_CNTL__R300_FORCE_TX |
			 SCLK_CNTL__R300_FORCE_US | SCLK_CNTL__FORCE_TV_SCLK |
			 SCLK_CNTL__R300_FORCE_SU | SCLK_CNTL__FORCE_OV0);
		tmp |= SCLK_CNTL__DYN_STOP_LAT_MASK;
		OUTPLL(pllSCLK_CNTL, tmp);

		tmp = INPLL(pllSCLK_MORE_CNTL);
		tmp &= ~SCLK_MORE_CNTL__FORCEON;
		tmp |=  SCLK_MORE_CNTL__DISPREGS_MAX_DYN_STOP_LAT |
			SCLK_MORE_CNTL__MC_GUI_MAX_DYN_STOP_LAT |
			SCLK_MORE_CNTL__MC_HOST_MAX_DYN_STOP_LAT;
		OUTPLL(pllSCLK_MORE_CNTL, tmp);

		tmp = INPLL(pllVCLK_ECP_CNTL);
		tmp |= (VCLK_ECP_CNTL__PIXCLK_ALWAYS_ONb |
			VCLK_ECP_CNTL__PIXCLK_DAC_ALWAYS_ONb);
		OUTPLL(pllVCLK_ECP_CNTL, tmp);

		tmp = INPLL(pllPIXCLKS_CNTL);
		tmp |= (PIXCLKS_CNTL__PIX2CLK_ALWAYS_ONb         |
			PIXCLKS_CNTL__PIX2CLK_DAC_ALWAYS_ONb     |
			PIXCLKS_CNTL__DISP_TVOUT_PIXCLK_TV_ALWAYS_ONb |
			PIXCLKS_CNTL__R300_DVOCLK_ALWAYS_ONb            |
			PIXCLKS_CNTL__PIXCLK_BLEND_ALWAYS_ONb    |
			PIXCLKS_CNTL__PIXCLK_GV_ALWAYS_ONb       |
			PIXCLKS_CNTL__R300_PIXCLK_DVO_ALWAYS_ONb        |
			PIXCLKS_CNTL__PIXCLK_LVDS_ALWAYS_ONb     |
			PIXCLKS_CNTL__PIXCLK_TMDS_ALWAYS_ONb     |
			PIXCLKS_CNTL__R300_PIXCLK_TRANS_ALWAYS_ONb      |
			PIXCLKS_CNTL__R300_PIXCLK_TVO_ALWAYS_ONb        |
			PIXCLKS_CNTL__R300_P2G2CLK_ALWAYS_ONb           |
			PIXCLKS_CNTL__R300_P2G2CLK_DAC_ALWAYS_ONb);
		OUTPLL(pllPIXCLKS_CNTL, tmp);

		tmp = INPLL(pllMCLK_MISC);
		tmp |= (MCLK_MISC__MC_MCLK_DYN_ENABLE |
			MCLK_MISC__IO_MCLK_DYN_ENABLE);
		OUTPLL(pllMCLK_MISC, tmp);

		tmp = INPLL(pllMCLK_CNTL);
		tmp |= (MCLK_CNTL__FORCE_MCLKA | MCLK_CNTL__FORCE_MCLKB);
		tmp &= ~(MCLK_CNTL__FORCE_YCLKA  |
			 MCLK_CNTL__FORCE_YCLKB  |
			 MCLK_CNTL__FORCE_MC);

		/* Some releases of vbios have set DISABLE_MC_MCLKA
		 * and DISABLE_MC_MCLKB bits in the vbios table.  Setting these
		 * bits will cause H/W hang when reading video memory with dynamic
		 * clocking enabled.
		 */
		if ((tmp & MCLK_CNTL__R300_DISABLE_MC_MCLKA) &&
		    (tmp & MCLK_CNTL__R300_DISABLE_MC_MCLKB)) {
			/* If both bits are set, then check the active channels */
			tmp = INPLL(pllMCLK_CNTL);
			if (rinfo->vram_width == 64) {
			    if (INREG(MEM_CNTL) & R300_MEM_USE_CD_CH_ONLY)
				tmp &= ~MCLK_CNTL__R300_DISABLE_MC_MCLKB;
			    else
				tmp &= ~MCLK_CNTL__R300_DISABLE_MC_MCLKA;
			} else {
			    tmp &= ~(MCLK_CNTL__R300_DISABLE_MC_MCLKA |
				     MCLK_CNTL__R300_DISABLE_MC_MCLKB);
			}
		}
		OUTPLL(pllMCLK_CNTL, tmp);
		return;
	}

	/* R300 */
	if (rinfo->family == CHIP_FAMILY_R300 || rinfo->family == CHIP_FAMILY_R350) {
		tmp = INPLL(pllSCLK_CNTL);
		tmp &= ~(SCLK_CNTL__R300_FORCE_VAP);
		tmp |= SCLK_CNTL__FORCE_CP;
		OUTPLL(pllSCLK_CNTL, tmp);
		radeon_msleep(15);

		tmp = INPLL(pllSCLK_CNTL2);
		tmp &= ~(SCLK_CNTL2__R300_FORCE_TCL |
			 SCLK_CNTL2__R300_FORCE_GA  |
			 SCLK_CNTL2__R300_FORCE_CBA);
		OUTPLL(pllSCLK_CNTL2, tmp);
	}

	/* Others */

	tmp = INPLL( pllCLK_PWRMGT_CNTL);
	tmp &= ~(CLK_PWRMGT_CNTL__ACTIVE_HILO_LAT_MASK|
		 CLK_PWRMGT_CNTL__DISP_DYN_STOP_LAT_MASK|
		 CLK_PWRMGT_CNTL__DYN_STOP_MODE_MASK);
	tmp |= CLK_PWRMGT_CNTL__ENGINE_DYNCLK_MODE_MASK |
	       (0x01 << CLK_PWRMGT_CNTL__ACTIVE_HILO_LAT__SHIFT);
	OUTPLL( pllCLK_PWRMGT_CNTL, tmp);
	radeon_msleep(15);

	tmp = INPLL(pllCLK_PIN_CNTL);
	tmp |= CLK_PIN_CNTL__SCLK_DYN_START_CNTL;
	OUTPLL(pllCLK_PIN_CNTL, tmp);
	radeon_msleep(15);

	/* When DRI is enabled, setting DYN_STOP_LAT to zero can cause some R200
	 * to lockup randomly, leave them as set by BIOS.
	 */
	tmp = INPLL(pllSCLK_CNTL);
	tmp &= ~SCLK_CNTL__FORCEON_MASK;

	/*RAGE_6::A11 A12 A12N1 A13, RV250::A11 A12, R300*/
	if ((rinfo->family == CHIP_FAMILY_RV250 &&
	     ((INREG(CNFG_CNTL) & CFG_ATI_REV_ID_MASK) < CFG_ATI_REV_A13)) ||
	    ((rinfo->family == CHIP_FAMILY_RV100) &&
	     ((INREG(CNFG_CNTL) & CFG_ATI_REV_ID_MASK) <= CFG_ATI_REV_A13))) {
		tmp |= SCLK_CNTL__FORCE_CP;
		tmp |= SCLK_CNTL__FORCE_VIP;
	}
	OUTPLL(pllSCLK_CNTL, tmp);
	radeon_msleep(15);

	if ((rinfo->family == CHIP_FAMILY_RV200) ||
	    (rinfo->family == CHIP_FAMILY_RV250) ||
	    (rinfo->family == CHIP_FAMILY_RV280)) {
		tmp = INPLL(pllSCLK_MORE_CNTL);
		tmp &= ~SCLK_MORE_CNTL__FORCEON;

		/* RV200::A11 A12 RV250::A11 A12 */
		if (((rinfo->family == CHIP_FAMILY_RV200) ||
		     (rinfo->family == CHIP_FAMILY_RV250)) &&
		    ((INREG(CNFG_CNTL) & CFG_ATI_REV_ID_MASK) < CFG_ATI_REV_A13))
			tmp |= SCLK_MORE_CNTL__FORCEON;

		OUTPLL(pllSCLK_MORE_CNTL, tmp);
		radeon_msleep(15);
	}
	

	/* RV200::A11 A12, RV250::A11 A12 */
	if (((rinfo->family == CHIP_FAMILY_RV200) ||
	     (rinfo->family == CHIP_FAMILY_RV250)) &&
	    ((INREG(CNFG_CNTL) & CFG_ATI_REV_ID_MASK) < CFG_ATI_REV_A13)) {
		tmp = INPLL(pllPLL_PWRMGT_CNTL);
		tmp |= PLL_PWRMGT_CNTL__TCL_BYPASS_DISABLE;
		OUTPLL(pllPLL_PWRMGT_CNTL, tmp);
		radeon_msleep(15);
	}

	tmp = INPLL(pllPIXCLKS_CNTL);
	tmp |=  PIXCLKS_CNTL__PIX2CLK_ALWAYS_ONb |
		PIXCLKS_CNTL__PIX2CLK_DAC_ALWAYS_ONb|
		PIXCLKS_CNTL__PIXCLK_BLEND_ALWAYS_ONb|
		PIXCLKS_CNTL__PIXCLK_GV_ALWAYS_ONb|
		PIXCLKS_CNTL__PIXCLK_DIG_TMDS_ALWAYS_ONb|
		PIXCLKS_CNTL__PIXCLK_LVDS_ALWAYS_ONb|
		PIXCLKS_CNTL__PIXCLK_TMDS_ALWAYS_ONb;
	OUTPLL(pllPIXCLKS_CNTL, tmp);
	radeon_msleep(15);
		
	tmp = INPLL(pllVCLK_ECP_CNTL);
	tmp |=  VCLK_ECP_CNTL__PIXCLK_ALWAYS_ONb |
		VCLK_ECP_CNTL__PIXCLK_DAC_ALWAYS_ONb;
	OUTPLL(pllVCLK_ECP_CNTL, tmp);

	/* X doesn't do that ... hrm, we do on mobility && Macs */
#ifdef CONFIG_PPC
	if (rinfo->is_mobility) {
		tmp  = INPLL(pllMCLK_CNTL);
		tmp &= ~(MCLK_CNTL__FORCE_MCLKA |
			 MCLK_CNTL__FORCE_MCLKB |
			 MCLK_CNTL__FORCE_YCLKA |
			 MCLK_CNTL__FORCE_YCLKB);
		OUTPLL(pllMCLK_CNTL, tmp);
		radeon_msleep(15);

		tmp = INPLL(pllMCLK_MISC);
		tmp |= 	MCLK_MISC__MC_MCLK_MAX_DYN_STOP_LAT|
			MCLK_MISC__IO_MCLK_MAX_DYN_STOP_LAT|
			MCLK_MISC__MC_MCLK_DYN_ENABLE|
			MCLK_MISC__IO_MCLK_DYN_ENABLE;
		OUTPLL(pllMCLK_MISC, tmp);
		radeon_msleep(15);
	}
#endif /* CONFIG_PPC */
}