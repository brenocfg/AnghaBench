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
struct radeonfb_info {int dummy; } ;
struct radeon_regs {int crtc_gen_cntl; int crtc_ext_cntl; int crtc_more_cntl; int dac_cntl; int crtc_h_total_disp; int crtc_h_sync_strt_wid; int crtc_v_total_disp; int crtc_v_sync_strt_wid; int crtc_pitch; int surface_cntl; int fp_crtc_h_total_disp; int fp_crtc_v_total_disp; int fp_gen_cntl; int fp_h_sync_strt_wid; int fp_horz_stretch; int fp_v_sync_strt_wid; int fp_vert_stretch; int lvds_gen_cntl; int lvds_pll_cntl; int tmds_crc; int tmds_transmitter_cntl; int clk_cntl_index; void* ppll_ref_div; void* ppll_div_3; void* vclk_ecp_cntl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_CNTL_INDEX ; 
 int /*<<< orphan*/  CRTC_EXT_CNTL ; 
 int /*<<< orphan*/  CRTC_GEN_CNTL ; 
 int /*<<< orphan*/  CRTC_H_SYNC_STRT_WID ; 
 int /*<<< orphan*/  CRTC_H_TOTAL_DISP ; 
 int /*<<< orphan*/  CRTC_MORE_CNTL ; 
 int /*<<< orphan*/  CRTC_PITCH ; 
 int /*<<< orphan*/  CRTC_V_SYNC_STRT_WID ; 
 int /*<<< orphan*/  CRTC_V_TOTAL_DISP ; 
 int /*<<< orphan*/  DAC_CNTL ; 
 int /*<<< orphan*/  FP_CRTC_H_TOTAL_DISP ; 
 int /*<<< orphan*/  FP_CRTC_V_TOTAL_DISP ; 
 int /*<<< orphan*/  FP_GEN_CNTL ; 
 int /*<<< orphan*/  FP_HORZ_STRETCH ; 
 int /*<<< orphan*/  FP_H_SYNC_STRT_WID ; 
 int /*<<< orphan*/  FP_VERT_STRETCH ; 
 int /*<<< orphan*/  FP_V_SYNC_STRT_WID ; 
 void* INPLL (int /*<<< orphan*/ ) ; 
 int INREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LVDS_GEN_CNTL ; 
 int /*<<< orphan*/  LVDS_PLL_CNTL ; 
 int /*<<< orphan*/  PPLL_DIV_3 ; 
 int /*<<< orphan*/  PPLL_REF_DIV ; 
 int /*<<< orphan*/  SURFACE_CNTL ; 
 int /*<<< orphan*/  TMDS_CRC ; 
 int /*<<< orphan*/  TMDS_TRANSMITTER_CNTL ; 
 int /*<<< orphan*/  VCLK_ECP_CNTL ; 
 int /*<<< orphan*/  radeon_pll_errata_after_index (struct radeonfb_info*) ; 

__attribute__((used)) static void radeon_save_state (struct radeonfb_info *rinfo,
			       struct radeon_regs *save)
{
	/* CRTC regs */
	save->crtc_gen_cntl = INREG(CRTC_GEN_CNTL);
	save->crtc_ext_cntl = INREG(CRTC_EXT_CNTL);
	save->crtc_more_cntl = INREG(CRTC_MORE_CNTL);
	save->dac_cntl = INREG(DAC_CNTL);
        save->crtc_h_total_disp = INREG(CRTC_H_TOTAL_DISP);
        save->crtc_h_sync_strt_wid = INREG(CRTC_H_SYNC_STRT_WID);
        save->crtc_v_total_disp = INREG(CRTC_V_TOTAL_DISP);
        save->crtc_v_sync_strt_wid = INREG(CRTC_V_SYNC_STRT_WID);
	save->crtc_pitch = INREG(CRTC_PITCH);
	save->surface_cntl = INREG(SURFACE_CNTL);

	/* FP regs */
	save->fp_crtc_h_total_disp = INREG(FP_CRTC_H_TOTAL_DISP);
	save->fp_crtc_v_total_disp = INREG(FP_CRTC_V_TOTAL_DISP);
	save->fp_gen_cntl = INREG(FP_GEN_CNTL);
	save->fp_h_sync_strt_wid = INREG(FP_H_SYNC_STRT_WID);
	save->fp_horz_stretch = INREG(FP_HORZ_STRETCH);
	save->fp_v_sync_strt_wid = INREG(FP_V_SYNC_STRT_WID);
	save->fp_vert_stretch = INREG(FP_VERT_STRETCH);
	save->lvds_gen_cntl = INREG(LVDS_GEN_CNTL);
	save->lvds_pll_cntl = INREG(LVDS_PLL_CNTL);
	save->tmds_crc = INREG(TMDS_CRC);
	save->tmds_transmitter_cntl = INREG(TMDS_TRANSMITTER_CNTL);
	save->vclk_ecp_cntl = INPLL(VCLK_ECP_CNTL);

	/* PLL regs */
	save->clk_cntl_index = INREG(CLOCK_CNTL_INDEX) & ~0x3f;
	radeon_pll_errata_after_index(rinfo);
	save->ppll_div_3 = INPLL(PPLL_DIV_3);
	save->ppll_ref_div = INPLL(PPLL_REF_DIV);
}