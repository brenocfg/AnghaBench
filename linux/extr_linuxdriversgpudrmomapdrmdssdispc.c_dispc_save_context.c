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
struct dispc_device {int ctx_valid; } ;

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
 int /*<<< orphan*/  SR (struct dispc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMING_H (int) ; 
 int /*<<< orphan*/  TIMING_V (int) ; 
 int /*<<< orphan*/  TRANS_COLOR (int) ; 
 int dispc_get_num_mgrs (struct dispc_device*) ; 
 int dispc_get_num_ovls (struct dispc_device*) ; 
 scalar_t__ dispc_has_feature (struct dispc_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_save_context(struct dispc_device *dispc)
{
	int i, j;

	DSSDBG("dispc_save_context\n");

	SR(dispc, IRQENABLE);
	SR(dispc, CONTROL);
	SR(dispc, CONFIG);
	SR(dispc, LINE_NUMBER);
	if (dispc_has_feature(dispc, FEAT_ALPHA_FIXED_ZORDER) ||
			dispc_has_feature(dispc, FEAT_ALPHA_FREE_ZORDER))
		SR(dispc, GLOBAL_ALPHA);
	if (dispc_has_feature(dispc, FEAT_MGR_LCD2)) {
		SR(dispc, CONTROL2);
		SR(dispc, CONFIG2);
	}
	if (dispc_has_feature(dispc, FEAT_MGR_LCD3)) {
		SR(dispc, CONTROL3);
		SR(dispc, CONFIG3);
	}

	for (i = 0; i < dispc_get_num_mgrs(dispc); i++) {
		SR(dispc, DEFAULT_COLOR(i));
		SR(dispc, TRANS_COLOR(i));
		SR(dispc, SIZE_MGR(i));
		if (i == OMAP_DSS_CHANNEL_DIGIT)
			continue;
		SR(dispc, TIMING_H(i));
		SR(dispc, TIMING_V(i));
		SR(dispc, POL_FREQ(i));
		SR(dispc, DIVISORo(i));

		SR(dispc, DATA_CYCLE1(i));
		SR(dispc, DATA_CYCLE2(i));
		SR(dispc, DATA_CYCLE3(i));

		if (dispc_has_feature(dispc, FEAT_CPR)) {
			SR(dispc, CPR_COEF_R(i));
			SR(dispc, CPR_COEF_G(i));
			SR(dispc, CPR_COEF_B(i));
		}
	}

	for (i = 0; i < dispc_get_num_ovls(dispc); i++) {
		SR(dispc, OVL_BA0(i));
		SR(dispc, OVL_BA1(i));
		SR(dispc, OVL_POSITION(i));
		SR(dispc, OVL_SIZE(i));
		SR(dispc, OVL_ATTRIBUTES(i));
		SR(dispc, OVL_FIFO_THRESHOLD(i));
		SR(dispc, OVL_ROW_INC(i));
		SR(dispc, OVL_PIXEL_INC(i));
		if (dispc_has_feature(dispc, FEAT_PRELOAD))
			SR(dispc, OVL_PRELOAD(i));
		if (i == OMAP_DSS_GFX) {
			SR(dispc, OVL_WINDOW_SKIP(i));
			SR(dispc, OVL_TABLE_BA(i));
			continue;
		}
		SR(dispc, OVL_FIR(i));
		SR(dispc, OVL_PICTURE_SIZE(i));
		SR(dispc, OVL_ACCU0(i));
		SR(dispc, OVL_ACCU1(i));

		for (j = 0; j < 8; j++)
			SR(dispc, OVL_FIR_COEF_H(i, j));

		for (j = 0; j < 8; j++)
			SR(dispc, OVL_FIR_COEF_HV(i, j));

		for (j = 0; j < 5; j++)
			SR(dispc, OVL_CONV_COEF(i, j));

		if (dispc_has_feature(dispc, FEAT_FIR_COEF_V)) {
			for (j = 0; j < 8; j++)
				SR(dispc, OVL_FIR_COEF_V(i, j));
		}

		if (dispc_has_feature(dispc, FEAT_HANDLE_UV_SEPARATE)) {
			SR(dispc, OVL_BA0_UV(i));
			SR(dispc, OVL_BA1_UV(i));
			SR(dispc, OVL_FIR2(i));
			SR(dispc, OVL_ACCU2_0(i));
			SR(dispc, OVL_ACCU2_1(i));

			for (j = 0; j < 8; j++)
				SR(dispc, OVL_FIR_COEF_H2(i, j));

			for (j = 0; j < 8; j++)
				SR(dispc, OVL_FIR_COEF_HV2(i, j));

			for (j = 0; j < 8; j++)
				SR(dispc, OVL_FIR_COEF_V2(i, j));
		}
		if (dispc_has_feature(dispc, FEAT_ATTR2))
			SR(dispc, OVL_ATTRIBUTES2(i));
	}

	if (dispc_has_feature(dispc, FEAT_CORE_CLK_DIV))
		SR(dispc, DIVISOR);

	dispc->ctx_valid = true;

	DSSDBG("context saved\n");
}