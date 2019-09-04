#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ v4l2_std_id ;
typedef  int u64 ;
typedef  int u32 ;
struct cx88_core {scalar_t__ tvnorm; int /*<<< orphan*/  chroma_agc; TYPE_2__* dvbdev; TYPE_1__* v4ldev; } ;
struct TYPE_4__ {int /*<<< orphan*/  vb2_mpegq; } ;
struct TYPE_3__ {int /*<<< orphan*/  vb2_vbiq; int /*<<< orphan*/  vb2_vidq; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MO_AGC_BURST ; 
 int /*<<< orphan*/  MO_HTOTAL ; 
 int /*<<< orphan*/  MO_INPUT_FORMAT ; 
 int /*<<< orphan*/  MO_OUTPUT_FORMAT ; 
 int /*<<< orphan*/  MO_SCONV_REG ; 
 int /*<<< orphan*/  MO_SUB_STEP ; 
 int /*<<< orphan*/  MO_SUB_STEP_DR ; 
 int /*<<< orphan*/  MO_VBI_PACKET ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_STD_NTSC ; 
 scalar_t__ V4L2_STD_NTSC_443 ; 
 scalar_t__ V4L2_STD_NTSC_M_JP ; 
 scalar_t__ V4L2_STD_PAL_60 ; 
 scalar_t__ V4L2_STD_PAL_M ; 
 scalar_t__ V4L2_STD_PAL_N ; 
 scalar_t__ V4L2_STD_PAL_Nc ; 
 scalar_t__ V4L2_STD_SECAM ; 
 int VideoFormatNTSC ; 
 int VideoFormatNTSC443 ; 
 int VideoFormatNTSCJapan ; 
 int VideoFormatPAL ; 
 int VideoFormatPAL60 ; 
 int VideoFormatPALM ; 
 int VideoFormatPALN ; 
 int VideoFormatPALNC ; 
 int VideoFormatSECAM ; 
 int /*<<< orphan*/  call_all (struct cx88_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cx88_set_scale (struct cx88_core*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_andor (int /*<<< orphan*/ ,int,int) ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,int,int,...) ; 
 int norm_fsc8 (scalar_t__) ; 
 int norm_htotal (scalar_t__) ; 
 int norm_vbipack (scalar_t__) ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  set_pll (struct cx88_core*,int,int) ; 
 int /*<<< orphan*/  set_tvaudio (struct cx88_core*) ; 
 int /*<<< orphan*/  v4l2_ctrl_grab (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_norm_to_name (scalar_t__) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video ; 
 int xtal ; 

int cx88_set_tvnorm(struct cx88_core *core, v4l2_std_id norm)
{
	u32 fsc8;
	u32 adc_clock;
	u32 vdec_clock;
	u32 step_db, step_dr;
	u64 tmp64;
	u32 bdelay, agcdelay, htotal;
	u32 cxiformat, cxoformat;

	if (norm == core->tvnorm)
		return 0;
	if (core->v4ldev && (vb2_is_busy(&core->v4ldev->vb2_vidq) ||
			     vb2_is_busy(&core->v4ldev->vb2_vbiq)))
		return -EBUSY;
	if (core->dvbdev && vb2_is_busy(&core->dvbdev->vb2_mpegq))
		return -EBUSY;
	core->tvnorm = norm;
	fsc8       = norm_fsc8(norm);
	adc_clock  = xtal;
	vdec_clock = fsc8;
	step_db    = fsc8;
	step_dr    = fsc8;

	if (norm & V4L2_STD_NTSC_M_JP) {
		cxiformat = VideoFormatNTSCJapan;
		cxoformat = 0x181f0008;
	} else if (norm & V4L2_STD_NTSC_443) {
		cxiformat = VideoFormatNTSC443;
		cxoformat = 0x181f0008;
	} else if (norm & V4L2_STD_PAL_M) {
		cxiformat = VideoFormatPALM;
		cxoformat = 0x1c1f0008;
	} else if (norm & V4L2_STD_PAL_N) {
		cxiformat = VideoFormatPALN;
		cxoformat = 0x1c1f0008;
	} else if (norm & V4L2_STD_PAL_Nc) {
		cxiformat = VideoFormatPALNC;
		cxoformat = 0x1c1f0008;
	} else if (norm & V4L2_STD_PAL_60) {
		cxiformat = VideoFormatPAL60;
		cxoformat = 0x181f0008;
	} else if (norm & V4L2_STD_NTSC) {
		cxiformat = VideoFormatNTSC;
		cxoformat = 0x181f0008;
	} else if (norm & V4L2_STD_SECAM) {
		step_db = 4250000 * 8;
		step_dr = 4406250 * 8;

		cxiformat = VideoFormatSECAM;
		cxoformat = 0x181f0008;
	} else { /* PAL */
		cxiformat = VideoFormatPAL;
		cxoformat = 0x181f0008;
	}

	dprintk(1, "set_tvnorm: \"%s\" fsc8=%d adc=%d vdec=%d db/dr=%d/%d\n",
		v4l2_norm_to_name(core->tvnorm), fsc8, adc_clock, vdec_clock,
		step_db, step_dr);
	set_pll(core, 2, vdec_clock);

	dprintk(1, "set_tvnorm: MO_INPUT_FORMAT  0x%08x [old=0x%08x]\n",
		cxiformat, cx_read(MO_INPUT_FORMAT) & 0x0f);
	/*
	 * Chroma AGC must be disabled if SECAM is used, we enable it
	 * by default on PAL and NTSC
	 */
	cx_andor(MO_INPUT_FORMAT, 0x40f,
		 norm & V4L2_STD_SECAM ? cxiformat : cxiformat | 0x400);

	// FIXME: as-is from DScaler
	dprintk(1, "set_tvnorm: MO_OUTPUT_FORMAT 0x%08x [old=0x%08x]\n",
		cxoformat, cx_read(MO_OUTPUT_FORMAT));
	cx_write(MO_OUTPUT_FORMAT, cxoformat);

	// MO_SCONV_REG = adc clock / video dec clock * 2^17
	tmp64  = adc_clock * (u64)(1 << 17);
	do_div(tmp64, vdec_clock);
	dprintk(1, "set_tvnorm: MO_SCONV_REG     0x%08x [old=0x%08x]\n",
		(u32)tmp64, cx_read(MO_SCONV_REG));
	cx_write(MO_SCONV_REG, (u32)tmp64);

	// MO_SUB_STEP = 8 * fsc / video dec clock * 2^22
	tmp64  = step_db * (u64)(1 << 22);
	do_div(tmp64, vdec_clock);
	dprintk(1, "set_tvnorm: MO_SUB_STEP      0x%08x [old=0x%08x]\n",
		(u32)tmp64, cx_read(MO_SUB_STEP));
	cx_write(MO_SUB_STEP, (u32)tmp64);

	// MO_SUB_STEP_DR = 8 * 4406250 / video dec clock * 2^22
	tmp64  = step_dr * (u64)(1 << 22);
	do_div(tmp64, vdec_clock);
	dprintk(1, "set_tvnorm: MO_SUB_STEP_DR   0x%08x [old=0x%08x]\n",
		(u32)tmp64, cx_read(MO_SUB_STEP_DR));
	cx_write(MO_SUB_STEP_DR, (u32)tmp64);

	// bdelay + agcdelay
	bdelay   = vdec_clock * 65 / 20000000 + 21;
	agcdelay = vdec_clock * 68 / 20000000 + 15;
	dprintk(1,
		"set_tvnorm: MO_AGC_BURST     0x%08x [old=0x%08x,bdelay=%d,agcdelay=%d]\n",
		(bdelay << 8) | agcdelay, cx_read(MO_AGC_BURST),
		bdelay, agcdelay);
	cx_write(MO_AGC_BURST, (bdelay << 8) | agcdelay);

	// htotal
	tmp64 = norm_htotal(norm) * (u64)vdec_clock;
	do_div(tmp64, fsc8);
	htotal = (u32)tmp64;
	dprintk(1,
		"set_tvnorm: MO_HTOTAL        0x%08x [old=0x%08x,htotal=%d]\n",
		htotal, cx_read(MO_HTOTAL), (u32)tmp64);
	cx_andor(MO_HTOTAL, 0x07ff, htotal);

	// vbi stuff, set vbi offset to 10 (for 20 Clk*2 pixels), this makes
	// the effective vbi offset ~244 samples, the same as the Bt8x8
	cx_write(MO_VBI_PACKET, (10 << 11) | norm_vbipack(norm));

	// this is needed as well to set all tvnorm parameter
	cx88_set_scale(core, 320, 240, V4L2_FIELD_INTERLACED);

	// audio
	set_tvaudio(core);

	// tell i2c chips
	call_all(core, video, s_std, norm);

	/*
	 * The chroma_agc control should be inaccessible
	 * if the video format is SECAM
	 */
	v4l2_ctrl_grab(core->chroma_agc, cxiformat == VideoFormatSECAM);

	// done
	return 0;
}