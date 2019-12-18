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
struct venc_device {int dummy; } ;
struct seq_file {struct venc_device* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMPREG (struct venc_device*,int /*<<< orphan*/ ) ; 
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
 scalar_t__ venc_runtime_get (struct venc_device*) ; 
 int /*<<< orphan*/  venc_runtime_put (struct venc_device*) ; 

__attribute__((used)) static int venc_dump_regs(struct seq_file *s, void *p)
{
	struct venc_device *venc = s->private;

#define DUMPREG(venc, r) \
	seq_printf(s, "%-35s %08x\n", #r, venc_read_reg(venc, r))

	if (venc_runtime_get(venc))
		return 0;

	DUMPREG(venc, VENC_F_CONTROL);
	DUMPREG(venc, VENC_VIDOUT_CTRL);
	DUMPREG(venc, VENC_SYNC_CTRL);
	DUMPREG(venc, VENC_LLEN);
	DUMPREG(venc, VENC_FLENS);
	DUMPREG(venc, VENC_HFLTR_CTRL);
	DUMPREG(venc, VENC_CC_CARR_WSS_CARR);
	DUMPREG(venc, VENC_C_PHASE);
	DUMPREG(venc, VENC_GAIN_U);
	DUMPREG(venc, VENC_GAIN_V);
	DUMPREG(venc, VENC_GAIN_Y);
	DUMPREG(venc, VENC_BLACK_LEVEL);
	DUMPREG(venc, VENC_BLANK_LEVEL);
	DUMPREG(venc, VENC_X_COLOR);
	DUMPREG(venc, VENC_M_CONTROL);
	DUMPREG(venc, VENC_BSTAMP_WSS_DATA);
	DUMPREG(venc, VENC_S_CARR);
	DUMPREG(venc, VENC_LINE21);
	DUMPREG(venc, VENC_LN_SEL);
	DUMPREG(venc, VENC_L21__WC_CTL);
	DUMPREG(venc, VENC_HTRIGGER_VTRIGGER);
	DUMPREG(venc, VENC_SAVID__EAVID);
	DUMPREG(venc, VENC_FLEN__FAL);
	DUMPREG(venc, VENC_LAL__PHASE_RESET);
	DUMPREG(venc, VENC_HS_INT_START_STOP_X);
	DUMPREG(venc, VENC_HS_EXT_START_STOP_X);
	DUMPREG(venc, VENC_VS_INT_START_X);
	DUMPREG(venc, VENC_VS_INT_STOP_X__VS_INT_START_Y);
	DUMPREG(venc, VENC_VS_INT_STOP_Y__VS_EXT_START_X);
	DUMPREG(venc, VENC_VS_EXT_STOP_X__VS_EXT_START_Y);
	DUMPREG(venc, VENC_VS_EXT_STOP_Y);
	DUMPREG(venc, VENC_AVID_START_STOP_X);
	DUMPREG(venc, VENC_AVID_START_STOP_Y);
	DUMPREG(venc, VENC_FID_INT_START_X__FID_INT_START_Y);
	DUMPREG(venc, VENC_FID_INT_OFFSET_Y__FID_EXT_START_X);
	DUMPREG(venc, VENC_FID_EXT_START_Y__FID_EXT_OFFSET_Y);
	DUMPREG(venc, VENC_TVDETGP_INT_START_STOP_X);
	DUMPREG(venc, VENC_TVDETGP_INT_START_STOP_Y);
	DUMPREG(venc, VENC_GEN_CTRL);
	DUMPREG(venc, VENC_OUTPUT_CONTROL);
	DUMPREG(venc, VENC_OUTPUT_TEST);

	venc_runtime_put(venc);

#undef DUMPREG
	return 0;
}