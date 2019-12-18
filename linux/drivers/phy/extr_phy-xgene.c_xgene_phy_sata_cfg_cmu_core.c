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
struct xgene_phy_ctx {int dummy; } ;
typedef  enum cmu_type_t { ____Placeholder_cmu_type_t } cmu_type_t ;
typedef  enum clk_type_t { ____Placeholder_clk_type_t } clk_type_t ;

/* Variables and functions */
 int CLK_EXT_DIFF ; 
 int /*<<< orphan*/  CMU_REG0 ; 
 int CMU_REG0_CAL_COUNT_RESOL_SET (int,int) ; 
 int /*<<< orphan*/  CMU_REG1 ; 
 int /*<<< orphan*/  CMU_REG10 ; 
 int CMU_REG10_VREG_REFSEL_SET (int,int) ; 
 int /*<<< orphan*/  CMU_REG16 ; 
 int CMU_REG16_BYPASS_PLL_LOCK_SET (int,int) ; 
 int CMU_REG16_CALIBRATION_DONE_OVERRIDE_SET (int,int) ; 
 int CMU_REG16_VCOCAL_WAIT_BTW_CODE_SET (int,int) ; 
 int CMU_REG1_PLL_CP_SEL_SET (int,int) ; 
 int CMU_REG1_PLL_CP_SET (int,int) ; 
 int CMU_REG1_PLL_MANUALCAL_SET (int,int) ; 
 int /*<<< orphan*/  CMU_REG2 ; 
 int /*<<< orphan*/  CMU_REG26 ; 
 int CMU_REG26_FORCE_PLL_LOCK_SET (int,int) ; 
 int CMU_REG2_PLL_FBDIV_SET (int,int /*<<< orphan*/ ) ; 
 int CMU_REG2_PLL_LFRES_SET (int,int) ; 
 int CMU_REG2_PLL_REFDIV_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMU_REG3 ; 
 int /*<<< orphan*/  CMU_REG30 ; 
 int CMU_REG30_LOCK_COUNT_SET (int,int) ; 
 int CMU_REG30_PCIE_MODE_SET (int,int) ; 
 int /*<<< orphan*/  CMU_REG31 ; 
 int /*<<< orphan*/  CMU_REG32 ; 
 int CMU_REG32_IREF_ADJ_SET (int,int) ; 
 int CMU_REG32_PVT_CAL_WAIT_SEL_SET (int,int) ; 
 int /*<<< orphan*/  CMU_REG34 ; 
 int CMU_REG34_VCO_CAL_VTH_HI_MAX_SET (int,int) ; 
 int CMU_REG34_VCO_CAL_VTH_HI_MIN_SET (int,int) ; 
 int CMU_REG34_VCO_CAL_VTH_LO_MAX_SET (int,int) ; 
 int CMU_REG34_VCO_CAL_VTH_LO_MIN_SET (int,int) ; 
 int /*<<< orphan*/  CMU_REG37 ; 
 int CMU_REG3_VCOVARSEL_SET (int,int) ; 
 int CMU_REG3_VCO_MANMOMSEL_SET (int,int) ; 
 int CMU_REG3_VCO_MOMSEL_INIT_SET (int,int) ; 
 int /*<<< orphan*/  CMU_REG5 ; 
 int CMU_REG5_PLL_LFCAP_SET (int,int) ; 
 int CMU_REG5_PLL_LFSMCAP_SET (int,int) ; 
 int CMU_REG5_PLL_LOCK_RESOLUTION_SET (int,int) ; 
 int /*<<< orphan*/  CMU_REG5_PLL_RESETB_MASK ; 
 int /*<<< orphan*/  CMU_REG6 ; 
 int CMU_REG6_MAN_PVT_CAL_SET (int,int) ; 
 int CMU_REG6_PLL_VREGTRIM_SET (int,int) ; 
 int /*<<< orphan*/  CMU_REG9 ; 
 int CMU_REG9_IGEN_BYPASS_SET (int,int) ; 
 int CMU_REG9_PLL_POST_DIVBY2_SET (int,int) ; 
 int CMU_REG9_TX_WORD_MODE_CH0_SET (int,int /*<<< orphan*/ ) ; 
 int CMU_REG9_TX_WORD_MODE_CH1_SET (int,int /*<<< orphan*/ ) ; 
 int CMU_REG9_VBG_BYPASSB_SET (int,int) ; 
 int /*<<< orphan*/  CMU_REG9_WORD_LEN_20BIT ; 
 int /*<<< orphan*/  FBDIV_VAL_100M ; 
 int /*<<< orphan*/  FBDIV_VAL_50M ; 
 int PHY_CMU ; 
 int /*<<< orphan*/  REFDIV_VAL_100M ; 
 int /*<<< orphan*/  REFDIV_VAL_50M ; 
 int REF_CMU ; 
 int /*<<< orphan*/  cmu_clrbits (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmu_rd (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  cmu_wr (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ preA3Chip ; 

__attribute__((used)) static void xgene_phy_sata_cfg_cmu_core(struct xgene_phy_ctx *ctx,
					enum cmu_type_t cmu_type,
					enum clk_type_t clk_type)
{
	u32 val;
	int ref_100MHz;

	if (cmu_type == REF_CMU) {
		/* Set VCO calibration voltage threshold */
		cmu_rd(ctx, cmu_type, CMU_REG34, &val);
		val = CMU_REG34_VCO_CAL_VTH_LO_MAX_SET(val, 0x7);
		val = CMU_REG34_VCO_CAL_VTH_HI_MAX_SET(val, 0xc);
		val = CMU_REG34_VCO_CAL_VTH_LO_MIN_SET(val, 0x3);
		val = CMU_REG34_VCO_CAL_VTH_HI_MIN_SET(val, 0x8);
		cmu_wr(ctx, cmu_type, CMU_REG34, val);
	}

	/* Set the VCO calibration counter */
	cmu_rd(ctx, cmu_type, CMU_REG0, &val);
	if (cmu_type == REF_CMU || preA3Chip)
		val = CMU_REG0_CAL_COUNT_RESOL_SET(val, 0x4);
	else
		val = CMU_REG0_CAL_COUNT_RESOL_SET(val, 0x7);
	cmu_wr(ctx, cmu_type, CMU_REG0, val);

	/* Configure PLL for calibration */
	cmu_rd(ctx, cmu_type, CMU_REG1, &val);
	val = CMU_REG1_PLL_CP_SET(val, 0x1);
	if (cmu_type == REF_CMU || preA3Chip)
		val = CMU_REG1_PLL_CP_SEL_SET(val, 0x5);
	else
		val = CMU_REG1_PLL_CP_SEL_SET(val, 0x3);
	if (cmu_type == REF_CMU)
		val = CMU_REG1_PLL_MANUALCAL_SET(val, 0x0);
	else
		val = CMU_REG1_PLL_MANUALCAL_SET(val, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG1, val);

	if (cmu_type != REF_CMU)
		cmu_clrbits(ctx, cmu_type, CMU_REG5, CMU_REG5_PLL_RESETB_MASK);

	/* Configure the PLL for either 100MHz or 50MHz */
	cmu_rd(ctx, cmu_type, CMU_REG2, &val);
	if (cmu_type == REF_CMU) {
		val = CMU_REG2_PLL_LFRES_SET(val, 0xa);
		ref_100MHz = 1;
	} else {
		val = CMU_REG2_PLL_LFRES_SET(val, 0x3);
		if (clk_type == CLK_EXT_DIFF)
			ref_100MHz = 0;
		else
			ref_100MHz = 1;
	}
	if (ref_100MHz) {
		val = CMU_REG2_PLL_FBDIV_SET(val, FBDIV_VAL_100M);
		val = CMU_REG2_PLL_REFDIV_SET(val, REFDIV_VAL_100M);
	} else {
		val = CMU_REG2_PLL_FBDIV_SET(val, FBDIV_VAL_50M);
		val = CMU_REG2_PLL_REFDIV_SET(val, REFDIV_VAL_50M);
	}
	cmu_wr(ctx, cmu_type, CMU_REG2, val);

	/* Configure the VCO */
	cmu_rd(ctx, cmu_type, CMU_REG3, &val);
	if (cmu_type == REF_CMU) {
		val = CMU_REG3_VCOVARSEL_SET(val, 0x3);
		val = CMU_REG3_VCO_MOMSEL_INIT_SET(val, 0x10);
	} else {
		val = CMU_REG3_VCOVARSEL_SET(val, 0xF);
		if (preA3Chip)
			val = CMU_REG3_VCO_MOMSEL_INIT_SET(val, 0x15);
		else
			val = CMU_REG3_VCO_MOMSEL_INIT_SET(val, 0x1a);
		val = CMU_REG3_VCO_MANMOMSEL_SET(val, 0x15);
	}
	cmu_wr(ctx, cmu_type, CMU_REG3, val);

	/* Disable force PLL lock */
	cmu_rd(ctx, cmu_type, CMU_REG26, &val);
	val = CMU_REG26_FORCE_PLL_LOCK_SET(val, 0x0);
	cmu_wr(ctx, cmu_type, CMU_REG26, val);

	/* Setup PLL loop filter */
	cmu_rd(ctx, cmu_type, CMU_REG5, &val);
	val = CMU_REG5_PLL_LFSMCAP_SET(val, 0x3);
	val = CMU_REG5_PLL_LFCAP_SET(val, 0x3);
	if (cmu_type == REF_CMU || !preA3Chip)
		val = CMU_REG5_PLL_LOCK_RESOLUTION_SET(val, 0x7);
	else
		val = CMU_REG5_PLL_LOCK_RESOLUTION_SET(val, 0x4);
	cmu_wr(ctx, cmu_type, CMU_REG5, val);

	/* Enable or disable manual calibration */
	cmu_rd(ctx, cmu_type, CMU_REG6, &val);
	val = CMU_REG6_PLL_VREGTRIM_SET(val, preA3Chip ? 0x0 : 0x2);
	val = CMU_REG6_MAN_PVT_CAL_SET(val, preA3Chip ? 0x1 : 0x0);
	cmu_wr(ctx, cmu_type, CMU_REG6, val);

	/* Configure lane for 20-bits */
	if (cmu_type == PHY_CMU) {
		cmu_rd(ctx, cmu_type, CMU_REG9, &val);
		val = CMU_REG9_TX_WORD_MODE_CH1_SET(val,
						    CMU_REG9_WORD_LEN_20BIT);
		val = CMU_REG9_TX_WORD_MODE_CH0_SET(val,
						    CMU_REG9_WORD_LEN_20BIT);
		val = CMU_REG9_PLL_POST_DIVBY2_SET(val, 0x1);
		if (!preA3Chip) {
			val = CMU_REG9_VBG_BYPASSB_SET(val, 0x0);
			val = CMU_REG9_IGEN_BYPASS_SET(val , 0x0);
		}
		cmu_wr(ctx, cmu_type, CMU_REG9, val);

		if (!preA3Chip) {
			cmu_rd(ctx, cmu_type, CMU_REG10, &val);
			val = CMU_REG10_VREG_REFSEL_SET(val, 0x1);
			cmu_wr(ctx, cmu_type, CMU_REG10, val);
		}
	}

	cmu_rd(ctx, cmu_type, CMU_REG16, &val);
	val = CMU_REG16_CALIBRATION_DONE_OVERRIDE_SET(val, 0x1);
	val = CMU_REG16_BYPASS_PLL_LOCK_SET(val, 0x1);
	if (cmu_type == REF_CMU || preA3Chip)
		val = CMU_REG16_VCOCAL_WAIT_BTW_CODE_SET(val, 0x4);
	else
		val = CMU_REG16_VCOCAL_WAIT_BTW_CODE_SET(val, 0x7);
	cmu_wr(ctx, cmu_type, CMU_REG16, val);

	/* Configure for SATA */
	cmu_rd(ctx, cmu_type, CMU_REG30, &val);
	val = CMU_REG30_PCIE_MODE_SET(val, 0x0);
	val = CMU_REG30_LOCK_COUNT_SET(val, 0x3);
	cmu_wr(ctx, cmu_type, CMU_REG30, val);

	/* Disable state machine bypass */
	cmu_wr(ctx, cmu_type, CMU_REG31, 0xF);

	cmu_rd(ctx, cmu_type, CMU_REG32, &val);
	val = CMU_REG32_PVT_CAL_WAIT_SEL_SET(val, 0x3);
	if (cmu_type == REF_CMU || preA3Chip)
		val = CMU_REG32_IREF_ADJ_SET(val, 0x3);
	else
		val = CMU_REG32_IREF_ADJ_SET(val, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG32, val);

	/* Set VCO calibration threshold */
	if (cmu_type != REF_CMU && preA3Chip)
		cmu_wr(ctx, cmu_type, CMU_REG34, 0x8d27);
	else
		cmu_wr(ctx, cmu_type, CMU_REG34, 0x873c);

	/* Set CTLE Override and override waiting from state machine */
	cmu_wr(ctx, cmu_type, CMU_REG37, 0xF00F);
}