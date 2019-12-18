#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ctx_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  CONFIG2 ; 
 int /*<<< orphan*/  CONFIG3 ; 
 int /*<<< orphan*/  CONTROL ; 
 int /*<<< orphan*/  CONTROL2 ; 
 int /*<<< orphan*/  CONTROL3 ; 
 int /*<<< orphan*/  CPR_COEF_B (int) ; 
 int /*<<< orphan*/  CPR_COEF_G (int) ; 
 int /*<<< orphan*/  CPR_COEF_R (int) ; 
 int /*<<< orphan*/  DATA_CYCLE1 (int) ; 
 int /*<<< orphan*/  DATA_CYCLE2 (int) ; 
 int /*<<< orphan*/  DATA_CYCLE3 (int) ; 
 int /*<<< orphan*/  DEFAULT_COLOR (int) ; 
 int /*<<< orphan*/  DIVISOR ; 
 int /*<<< orphan*/  DIVISORo (int) ; 
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  FEAT_ALPHA_FIXED_ZORDER ; 
 int /*<<< orphan*/  FEAT_ALPHA_FREE_ZORDER ; 
 int /*<<< orphan*/  FEAT_ATTR2 ; 
 int /*<<< orphan*/  FEAT_CORE_CLK_DIV ; 
 int /*<<< orphan*/  FEAT_CPR ; 
 int /*<<< orphan*/  FEAT_FIR_COEF_V ; 
 int /*<<< orphan*/  FEAT_HANDLE_UV_SEPARATE ; 
 int /*<<< orphan*/  FEAT_MGR_LCD2 ; 
 int /*<<< orphan*/  FEAT_MGR_LCD3 ; 
 int /*<<< orphan*/  FEAT_PRELOAD ; 
 int /*<<< orphan*/  GLOBAL_ALPHA ; 
 int /*<<< orphan*/  IRQENABLE ; 
 int /*<<< orphan*/  LINE_NUMBER ; 
 int OMAP_DSS_CHANNEL_DIGIT ; 
 int OMAP_DSS_GFX ; 
 int /*<<< orphan*/  OVL_ACCU0 (int) ; 
 int /*<<< orphan*/  OVL_ACCU1 (int) ; 
 int /*<<< orphan*/  OVL_ACCU2_0 (int) ; 
 int /*<<< orphan*/  OVL_ACCU2_1 (int) ; 
 int /*<<< orphan*/  OVL_ATTRIBUTES (int) ; 
 int /*<<< orphan*/  OVL_ATTRIBUTES2 (int) ; 
 int /*<<< orphan*/  OVL_BA0 (int) ; 
 int /*<<< orphan*/  OVL_BA0_UV (int) ; 
 int /*<<< orphan*/  OVL_BA1 (int) ; 
 int /*<<< orphan*/  OVL_BA1_UV (int) ; 
 int /*<<< orphan*/  OVL_CONV_COEF (int,int) ; 
 int /*<<< orphan*/  OVL_FIFO_THRESHOLD (int) ; 
 int /*<<< orphan*/  OVL_FIR (int) ; 
 int /*<<< orphan*/  OVL_FIR2 (int) ; 
 int /*<<< orphan*/  OVL_FIR_COEF_H (int,int) ; 
 int /*<<< orphan*/  OVL_FIR_COEF_H2 (int,int) ; 
 int /*<<< orphan*/  OVL_FIR_COEF_HV (int,int) ; 
 int /*<<< orphan*/  OVL_FIR_COEF_HV2 (int,int) ; 
 int /*<<< orphan*/  OVL_FIR_COEF_V (int,int) ; 
 int /*<<< orphan*/  OVL_FIR_COEF_V2 (int,int) ; 
 int /*<<< orphan*/  OVL_PICTURE_SIZE (int) ; 
 int /*<<< orphan*/  OVL_PIXEL_INC (int) ; 
 int /*<<< orphan*/  OVL_POSITION (int) ; 
 int /*<<< orphan*/  OVL_PRELOAD (int) ; 
 int /*<<< orphan*/  OVL_ROW_INC (int) ; 
 int /*<<< orphan*/  OVL_SIZE (int) ; 
 int /*<<< orphan*/  OVL_TABLE_BA (int) ; 
 int /*<<< orphan*/  OVL_WINDOW_SKIP (int) ; 
 int /*<<< orphan*/  POL_FREQ (int) ; 
 int /*<<< orphan*/  SIZE_MGR (int) ; 
 int /*<<< orphan*/  SR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMING_H (int) ; 
 int /*<<< orphan*/  TIMING_V (int) ; 
 int /*<<< orphan*/  TRANS_COLOR (int) ; 
 TYPE_1__ dispc ; 
 int dss_feat_get_num_mgrs () ; 
 int dss_feat_get_num_ovls () ; 
 scalar_t__ dss_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_save_context(void)
{
	int i, j;

	DSSDBG("dispc_save_context\n");

	SR(IRQENABLE);
	SR(CONTROL);
	SR(CONFIG);
	SR(LINE_NUMBER);
	if (dss_has_feature(FEAT_ALPHA_FIXED_ZORDER) ||
			dss_has_feature(FEAT_ALPHA_FREE_ZORDER))
		SR(GLOBAL_ALPHA);
	if (dss_has_feature(FEAT_MGR_LCD2)) {
		SR(CONTROL2);
		SR(CONFIG2);
	}
	if (dss_has_feature(FEAT_MGR_LCD3)) {
		SR(CONTROL3);
		SR(CONFIG3);
	}

	for (i = 0; i < dss_feat_get_num_mgrs(); i++) {
		SR(DEFAULT_COLOR(i));
		SR(TRANS_COLOR(i));
		SR(SIZE_MGR(i));
		if (i == OMAP_DSS_CHANNEL_DIGIT)
			continue;
		SR(TIMING_H(i));
		SR(TIMING_V(i));
		SR(POL_FREQ(i));
		SR(DIVISORo(i));

		SR(DATA_CYCLE1(i));
		SR(DATA_CYCLE2(i));
		SR(DATA_CYCLE3(i));

		if (dss_has_feature(FEAT_CPR)) {
			SR(CPR_COEF_R(i));
			SR(CPR_COEF_G(i));
			SR(CPR_COEF_B(i));
		}
	}

	for (i = 0; i < dss_feat_get_num_ovls(); i++) {
		SR(OVL_BA0(i));
		SR(OVL_BA1(i));
		SR(OVL_POSITION(i));
		SR(OVL_SIZE(i));
		SR(OVL_ATTRIBUTES(i));
		SR(OVL_FIFO_THRESHOLD(i));
		SR(OVL_ROW_INC(i));
		SR(OVL_PIXEL_INC(i));
		if (dss_has_feature(FEAT_PRELOAD))
			SR(OVL_PRELOAD(i));
		if (i == OMAP_DSS_GFX) {
			SR(OVL_WINDOW_SKIP(i));
			SR(OVL_TABLE_BA(i));
			continue;
		}
		SR(OVL_FIR(i));
		SR(OVL_PICTURE_SIZE(i));
		SR(OVL_ACCU0(i));
		SR(OVL_ACCU1(i));

		for (j = 0; j < 8; j++)
			SR(OVL_FIR_COEF_H(i, j));

		for (j = 0; j < 8; j++)
			SR(OVL_FIR_COEF_HV(i, j));

		for (j = 0; j < 5; j++)
			SR(OVL_CONV_COEF(i, j));

		if (dss_has_feature(FEAT_FIR_COEF_V)) {
			for (j = 0; j < 8; j++)
				SR(OVL_FIR_COEF_V(i, j));
		}

		if (dss_has_feature(FEAT_HANDLE_UV_SEPARATE)) {
			SR(OVL_BA0_UV(i));
			SR(OVL_BA1_UV(i));
			SR(OVL_FIR2(i));
			SR(OVL_ACCU2_0(i));
			SR(OVL_ACCU2_1(i));

			for (j = 0; j < 8; j++)
				SR(OVL_FIR_COEF_H2(i, j));

			for (j = 0; j < 8; j++)
				SR(OVL_FIR_COEF_HV2(i, j));

			for (j = 0; j < 8; j++)
				SR(OVL_FIR_COEF_V2(i, j));
		}
		if (dss_has_feature(FEAT_ATTR2))
			SR(OVL_ATTRIBUTES2(i));
	}

	if (dss_has_feature(FEAT_CORE_CLK_DIV))
		SR(DIVISOR);

	dispc.ctx_valid = true;

	DSSDBG("context saved\n");
}