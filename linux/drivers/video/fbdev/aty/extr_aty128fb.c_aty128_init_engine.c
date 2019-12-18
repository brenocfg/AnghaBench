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
typedef  int u32 ;
struct TYPE_2__ {int pitch; int bpp; int /*<<< orphan*/  depth; } ;
struct aty128fb_par {TYPE_1__ crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_OFFSET ; 
 int /*<<< orphan*/  DEFAULT_PITCH ; 
 int /*<<< orphan*/  DEFAULT_SC_BOTTOM_RIGHT ; 
 int /*<<< orphan*/  DP_BRUSH_BKGD_CLR ; 
 int /*<<< orphan*/  DP_BRUSH_FRGD_CLR ; 
 int /*<<< orphan*/  DP_GUI_MASTER_CNTL ; 
 int /*<<< orphan*/  DP_SRC_BKGD_CLR ; 
 int /*<<< orphan*/  DP_SRC_FRGD_CLR ; 
 int /*<<< orphan*/  DP_WRITE_MASK ; 
 int /*<<< orphan*/  DST_BRES_DEC ; 
 int /*<<< orphan*/  DST_BRES_ERR ; 
 int /*<<< orphan*/  DST_BRES_INC ; 
 int GMC_3D_FCN_EN_CLR ; 
 int GMC_AUX_CLIP_CLEAR ; 
 int GMC_BRUSH_SOLIDCOLOR ; 
 int GMC_BYTE_ORDER_MSB_TO_LSB ; 
 int GMC_DP_CONVERSION_TEMP_6500 ; 
 int GMC_DP_SRC_RECT ; 
 int GMC_DST_CLIP_DEFAULT ; 
 int GMC_DST_CLR_CMP_FCN_CLEAR ; 
 int GMC_DST_PITCH_OFFSET_DEFAULT ; 
 int GMC_SRC_CLIP_DEFAULT ; 
 int GMC_SRC_DSTCOLOR ; 
 int GMC_SRC_PITCH_OFFSET_DEFAULT ; 
 int GMC_WRITE_MASK_SET ; 
 int ROP3_PATCOPY ; 
 int /*<<< orphan*/  SCALE_3D_CNTL ; 
 int /*<<< orphan*/  aty128_reset_engine (struct aty128fb_par*) ; 
 int /*<<< orphan*/  aty_st_le32 (int /*<<< orphan*/ ,int) ; 
 int depth_to_dst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_fifo (int,struct aty128fb_par*) ; 
 int /*<<< orphan*/  wait_for_idle (struct aty128fb_par*) ; 

__attribute__((used)) static void aty128_init_engine(struct aty128fb_par *par)
{
	u32 pitch_value;

	wait_for_idle(par);

	/* 3D scaler not spoken here */
	wait_for_fifo(1, par);
	aty_st_le32(SCALE_3D_CNTL, 0x00000000);

	aty128_reset_engine(par);

	pitch_value = par->crtc.pitch;
	if (par->crtc.bpp == 24) {
		pitch_value = pitch_value * 3;
	}

	wait_for_fifo(4, par);
	/* setup engine offset registers */
	aty_st_le32(DEFAULT_OFFSET, 0x00000000);

	/* setup engine pitch registers */
	aty_st_le32(DEFAULT_PITCH, pitch_value);

	/* set the default scissor register to max dimensions */
	aty_st_le32(DEFAULT_SC_BOTTOM_RIGHT, (0x1FFF << 16) | 0x1FFF);

	/* set the drawing controls registers */
	aty_st_le32(DP_GUI_MASTER_CNTL,
		    GMC_SRC_PITCH_OFFSET_DEFAULT		|
		    GMC_DST_PITCH_OFFSET_DEFAULT		|
		    GMC_SRC_CLIP_DEFAULT			|
		    GMC_DST_CLIP_DEFAULT			|
		    GMC_BRUSH_SOLIDCOLOR			|
		    (depth_to_dst(par->crtc.depth) << 8)	|
		    GMC_SRC_DSTCOLOR			|
		    GMC_BYTE_ORDER_MSB_TO_LSB		|
		    GMC_DP_CONVERSION_TEMP_6500		|
		    ROP3_PATCOPY				|
		    GMC_DP_SRC_RECT				|
		    GMC_3D_FCN_EN_CLR			|
		    GMC_DST_CLR_CMP_FCN_CLEAR		|
		    GMC_AUX_CLIP_CLEAR			|
		    GMC_WRITE_MASK_SET);

	wait_for_fifo(8, par);
	/* clear the line drawing registers */
	aty_st_le32(DST_BRES_ERR, 0);
	aty_st_le32(DST_BRES_INC, 0);
	aty_st_le32(DST_BRES_DEC, 0);

	/* set brush color registers */
	aty_st_le32(DP_BRUSH_FRGD_CLR, 0xFFFFFFFF); /* white */
	aty_st_le32(DP_BRUSH_BKGD_CLR, 0x00000000); /* black */

	/* set source color registers */
	aty_st_le32(DP_SRC_FRGD_CLR, 0xFFFFFFFF);   /* white */
	aty_st_le32(DP_SRC_BKGD_CLR, 0x00000000);   /* black */

	/* default write mask */
	aty_st_le32(DP_WRITE_MASK, 0xFFFFFFFF);

	/* Wait for all the writes to be completed before returning */
	wait_for_idle(par);
}