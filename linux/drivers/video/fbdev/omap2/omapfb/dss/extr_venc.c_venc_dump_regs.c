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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMPREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VENC_AVID_START_STOP_X ; 
 int /*<<< orphan*/  VENC_AVID_START_STOP_Y ; 
 int /*<<< orphan*/  VENC_BLACK_LEVEL ; 
 int /*<<< orphan*/  VENC_BLANK_LEVEL ; 
 int /*<<< orphan*/  VENC_BSTAMP_WSS_DATA ; 
 int /*<<< orphan*/  VENC_CC_CARR_WSS_CARR ; 
 int /*<<< orphan*/  VENC_C_PHASE ; 
 int /*<<< orphan*/  VENC_FID_EXT_START_Y__FID_EXT_OFFSET_Y ; 
 int /*<<< orphan*/  VENC_FID_INT_OFFSET_Y__FID_EXT_START_X ; 
 int /*<<< orphan*/  VENC_FID_INT_START_X__FID_INT_START_Y ; 
 int /*<<< orphan*/  VENC_FLENS ; 
 int /*<<< orphan*/  VENC_FLEN__FAL ; 
 int /*<<< orphan*/  VENC_F_CONTROL ; 
 int /*<<< orphan*/  VENC_GAIN_U ; 
 int /*<<< orphan*/  VENC_GAIN_V ; 
 int /*<<< orphan*/  VENC_GAIN_Y ; 
 int /*<<< orphan*/  VENC_GEN_CTRL ; 
 int /*<<< orphan*/  VENC_HFLTR_CTRL ; 
 int /*<<< orphan*/  VENC_HS_EXT_START_STOP_X ; 
 int /*<<< orphan*/  VENC_HS_INT_START_STOP_X ; 
 int /*<<< orphan*/  VENC_HTRIGGER_VTRIGGER ; 
 int /*<<< orphan*/  VENC_L21__WC_CTL ; 
 int /*<<< orphan*/  VENC_LAL__PHASE_RESET ; 
 int /*<<< orphan*/  VENC_LINE21 ; 
 int /*<<< orphan*/  VENC_LLEN ; 
 int /*<<< orphan*/  VENC_LN_SEL ; 
 int /*<<< orphan*/  VENC_M_CONTROL ; 
 int /*<<< orphan*/  VENC_OUTPUT_CONTROL ; 
 int /*<<< orphan*/  VENC_OUTPUT_TEST ; 
 int /*<<< orphan*/  VENC_SAVID__EAVID ; 
 int /*<<< orphan*/  VENC_SYNC_CTRL ; 
 int /*<<< orphan*/  VENC_S_CARR ; 
 int /*<<< orphan*/  VENC_TVDETGP_INT_START_STOP_X ; 
 int /*<<< orphan*/  VENC_TVDETGP_INT_START_STOP_Y ; 
 int /*<<< orphan*/  VENC_VIDOUT_CTRL ; 
 int /*<<< orphan*/  VENC_VS_EXT_STOP_X__VS_EXT_START_Y ; 
 int /*<<< orphan*/  VENC_VS_EXT_STOP_Y ; 
 int /*<<< orphan*/  VENC_VS_INT_START_X ; 
 int /*<<< orphan*/  VENC_VS_INT_STOP_X__VS_INT_START_Y ; 
 int /*<<< orphan*/  VENC_VS_INT_STOP_Y__VS_EXT_START_X ; 
 int /*<<< orphan*/  VENC_X_COLOR ; 
 scalar_t__ venc_runtime_get () ; 
 int /*<<< orphan*/  venc_runtime_put () ; 

__attribute__((used)) static void venc_dump_regs(struct seq_file *s)
{
#define DUMPREG(r) seq_printf(s, "%-35s %08x\n", #r, venc_read_reg(r))

	if (venc_runtime_get())
		return;

	DUMPREG(VENC_F_CONTROL);
	DUMPREG(VENC_VIDOUT_CTRL);
	DUMPREG(VENC_SYNC_CTRL);
	DUMPREG(VENC_LLEN);
	DUMPREG(VENC_FLENS);
	DUMPREG(VENC_HFLTR_CTRL);
	DUMPREG(VENC_CC_CARR_WSS_CARR);
	DUMPREG(VENC_C_PHASE);
	DUMPREG(VENC_GAIN_U);
	DUMPREG(VENC_GAIN_V);
	DUMPREG(VENC_GAIN_Y);
	DUMPREG(VENC_BLACK_LEVEL);
	DUMPREG(VENC_BLANK_LEVEL);
	DUMPREG(VENC_X_COLOR);
	DUMPREG(VENC_M_CONTROL);
	DUMPREG(VENC_BSTAMP_WSS_DATA);
	DUMPREG(VENC_S_CARR);
	DUMPREG(VENC_LINE21);
	DUMPREG(VENC_LN_SEL);
	DUMPREG(VENC_L21__WC_CTL);
	DUMPREG(VENC_HTRIGGER_VTRIGGER);
	DUMPREG(VENC_SAVID__EAVID);
	DUMPREG(VENC_FLEN__FAL);
	DUMPREG(VENC_LAL__PHASE_RESET);
	DUMPREG(VENC_HS_INT_START_STOP_X);
	DUMPREG(VENC_HS_EXT_START_STOP_X);
	DUMPREG(VENC_VS_INT_START_X);
	DUMPREG(VENC_VS_INT_STOP_X__VS_INT_START_Y);
	DUMPREG(VENC_VS_INT_STOP_Y__VS_EXT_START_X);
	DUMPREG(VENC_VS_EXT_STOP_X__VS_EXT_START_Y);
	DUMPREG(VENC_VS_EXT_STOP_Y);
	DUMPREG(VENC_AVID_START_STOP_X);
	DUMPREG(VENC_AVID_START_STOP_Y);
	DUMPREG(VENC_FID_INT_START_X__FID_INT_START_Y);
	DUMPREG(VENC_FID_INT_OFFSET_Y__FID_EXT_START_X);
	DUMPREG(VENC_FID_EXT_START_Y__FID_EXT_OFFSET_Y);
	DUMPREG(VENC_TVDETGP_INT_START_STOP_X);
	DUMPREG(VENC_TVDETGP_INT_START_STOP_Y);
	DUMPREG(VENC_GEN_CTRL);
	DUMPREG(VENC_OUTPUT_CONTROL);
	DUMPREG(VENC_OUTPUT_TEST);

	venc_runtime_put();

#undef DUMPREG
}