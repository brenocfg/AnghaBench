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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct cx18_av_state {int /*<<< orphan*/  hdl; TYPE_2__* volume; } ;
struct cx18 {int dummy; } ;
struct TYPE_3__ {int val; } ;
struct TYPE_4__ {int default_value; TYPE_1__ cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXADEC_AFE_CTRL ; 
 int /*<<< orphan*/  CXADEC_AFE_DIAG_CTRL1 ; 
 int /*<<< orphan*/  CXADEC_AFE_DIAG_CTRL3 ; 
 int /*<<< orphan*/  CXADEC_CHIP_CTRL ; 
 int /*<<< orphan*/  CXADEC_CRUSH_CTRL ; 
 int /*<<< orphan*/  CXADEC_DFE_CTRL2 ; 
 int /*<<< orphan*/  CXADEC_DLL1_DIAG_CTRL ; 
 int /*<<< orphan*/  CXADEC_DLL2_DIAG_CTRL ; 
 int /*<<< orphan*/  CXADEC_DL_CTL ; 
 int /*<<< orphan*/  CXADEC_HOST_REG1 ; 
 int /*<<< orphan*/  CXADEC_MODE_CTRL ; 
 int /*<<< orphan*/  CXADEC_OUT_CTRL1 ; 
 int /*<<< orphan*/  CXADEC_PIN_CTRL1 ; 
 int /*<<< orphan*/  CXADEC_PIN_CTRL2 ; 
 int /*<<< orphan*/  CXADEC_SOFT_RST_CTRL ; 
 int /*<<< orphan*/  CXADEC_SRC_COMB_CFG ; 
 int /*<<< orphan*/  cx18_av_and_or4 (struct cx18*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cx18_av_init (struct cx18*) ; 
 int /*<<< orphan*/  cx18_av_loadfw (struct cx18*) ; 
 int cx18_av_read (struct cx18*,int) ; 
 int cx18_av_read4 (struct cx18*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_av_write (struct cx18*,int,int) ; 
 int /*<<< orphan*/  cx18_av_write4 (struct cx18*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx18_av_write4_expect (struct cx18*,int /*<<< orphan*/ ,int,int,int) ; 
 struct cx18_av_state* to_cx18_av_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 struct cx18* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static void cx18_av_initialize(struct v4l2_subdev *sd)
{
	struct cx18_av_state *state = to_cx18_av_state(sd);
	struct cx18 *cx = v4l2_get_subdevdata(sd);
	int default_volume;
	u32 v;

	cx18_av_loadfw(cx);
	/* Stop 8051 code execution */
	cx18_av_write4_expect(cx, CXADEC_DL_CTL, 0x03000000,
						 0x03000000, 0x13000000);

	/* initallize the PLL by toggling sleep bit */
	v = cx18_av_read4(cx, CXADEC_HOST_REG1);
	/* enable sleep mode - register appears to be read only... */
	cx18_av_write4_expect(cx, CXADEC_HOST_REG1, v | 1, v, 0xfffe);
	/* disable sleep mode */
	cx18_av_write4_expect(cx, CXADEC_HOST_REG1, v & 0xfffe,
						    v & 0xfffe, 0xffff);

	/* initialize DLLs */
	v = cx18_av_read4(cx, CXADEC_DLL1_DIAG_CTRL) & 0xE1FFFEFF;
	/* disable FLD */
	cx18_av_write4(cx, CXADEC_DLL1_DIAG_CTRL, v);
	/* enable FLD */
	cx18_av_write4(cx, CXADEC_DLL1_DIAG_CTRL, v | 0x10000100);

	v = cx18_av_read4(cx, CXADEC_DLL2_DIAG_CTRL) & 0xE1FFFEFF;
	/* disable FLD */
	cx18_av_write4(cx, CXADEC_DLL2_DIAG_CTRL, v);
	/* enable FLD */
	cx18_av_write4(cx, CXADEC_DLL2_DIAG_CTRL, v | 0x06000100);

	/* set analog bias currents. Set Vreg to 1.20V. */
	cx18_av_write4(cx, CXADEC_AFE_DIAG_CTRL1, 0x000A1802);

	v = cx18_av_read4(cx, CXADEC_AFE_DIAG_CTRL3) | 1;
	/* enable TUNE_FIL_RST */
	cx18_av_write4_expect(cx, CXADEC_AFE_DIAG_CTRL3, v, v, 0x03009F0F);
	/* disable TUNE_FIL_RST */
	cx18_av_write4_expect(cx, CXADEC_AFE_DIAG_CTRL3,
			      v & 0xFFFFFFFE, v & 0xFFFFFFFE, 0x03009F0F);

	/* enable 656 output */
	cx18_av_and_or4(cx, CXADEC_PIN_CTRL1, ~0, 0x040C00);

	/* video output drive strength */
	cx18_av_and_or4(cx, CXADEC_PIN_CTRL2, ~0, 0x2);

	/* reset video */
	cx18_av_write4(cx, CXADEC_SOFT_RST_CTRL, 0x8000);
	cx18_av_write4(cx, CXADEC_SOFT_RST_CTRL, 0);

	/*
	 * Disable Video Auto-config of the Analog Front End and Video PLL.
	 *
	 * Since we only use BT.656 pixel mode, which works for both 525 and 625
	 * line systems, it's just easier for us to set registers
	 * 0x102 (CXADEC_CHIP_CTRL), 0x104-0x106 (CXADEC_AFE_CTRL),
	 * 0x108-0x109 (CXADEC_PLL_CTRL1), and 0x10c-0x10f (CXADEC_VID_PLL_FRAC)
	 * ourselves, than to run around cleaning up after the auto-config.
	 *
	 * (Note: my CX23418 chip doesn't seem to let the ACFG_DIS bit
	 * get set to 1, but OTOH, it doesn't seem to do AFE and VID PLL
	 * autoconfig either.)
	 *
	 * As a default, also turn off Dual mode for ADC2 and set ADC2 to CH3.
	 */
	cx18_av_and_or4(cx, CXADEC_CHIP_CTRL, 0xFFFBFFFF, 0x00120000);

	/* Setup the Video and and Aux/Audio PLLs */
	cx18_av_init(cx);

	/* set video to auto-detect */
	/* Clear bits 11-12 to enable slow locking mode.  Set autodetect mode */
	/* set the comb notch = 1 */
	cx18_av_and_or4(cx, CXADEC_MODE_CTRL, 0xFFF7E7F0, 0x02040800);

	/* Enable wtw_en in CRUSH_CTRL (Set bit 22) */
	/* Enable maj_sel in CRUSH_CTRL (Set bit 20) */
	cx18_av_and_or4(cx, CXADEC_CRUSH_CTRL, ~0, 0x00500000);

	/* Set VGA_TRACK_RANGE to 0x20 */
	cx18_av_and_or4(cx, CXADEC_DFE_CTRL2, 0xFFFF00FF, 0x00002000);

	/*
	 * Initial VBI setup
	 * VIP-1.1, 10 bit mode, enable Raw, disable sliced,
	 * don't clamp raw samples when codes are in use, 1 byte user D-words,
	 * IDID0 has line #, RP code V bit transition on VBLANK, data during
	 * blanking intervals
	 */
	cx18_av_write4(cx, CXADEC_OUT_CTRL1, 0x4013252e);

	/* Set the video input.
	   The setting in MODE_CTRL gets lost when we do the above setup */
	/* EncSetSignalStd(dwDevNum, pEnc->dwSigStd); */
	/* EncSetVideoInput(dwDevNum, pEnc->VidIndSelection); */

	/*
	 * Analog Front End (AFE)
	 * Default to luma on ch1/ADC1, chroma on ch2/ADC2, SIF on ch3/ADC2
	 *  bypass_ch[1-3]     use filter
	 *  droop_comp_ch[1-3] disable
	 *  clamp_en_ch[1-3]   disable
	 *  aud_in_sel         ADC2
	 *  luma_in_sel        ADC1
	 *  chroma_in_sel      ADC2
	 *  clamp_sel_ch[2-3]  midcode
	 *  clamp_sel_ch1      video decoder
	 *  vga_sel_ch3        audio decoder
	 *  vga_sel_ch[1-2]    video decoder
	 *  half_bw_ch[1-3]    disable
	 *  +12db_ch[1-3]      disable
	 */
	cx18_av_and_or4(cx, CXADEC_AFE_CTRL, 0xFF000000, 0x00005D00);

/*	if(dwEnable && dw3DCombAvailable) { */
/*		CxDevWrReg(CXADEC_SRC_COMB_CFG, 0x7728021F); */
/*    } else { */
/*		CxDevWrReg(CXADEC_SRC_COMB_CFG, 0x6628021F); */
/*    } */
	cx18_av_write4(cx, CXADEC_SRC_COMB_CFG, 0x6628021F);
	default_volume = cx18_av_read(cx, 0x8d4);
	/*
	 * Enforce the legacy volume scale mapping limits to avoid
	 * -ERANGE errors when initializing the volume control
	 */
	if (default_volume > 228) {
		/* Bottom out at -96 dB, v4l2 vol range 0x2e00-0x2fff */
		default_volume = 228;
		cx18_av_write(cx, 0x8d4, 228);
	} else if (default_volume < 20) {
		/* Top out at + 8 dB, v4l2 vol range 0xfe00-0xffff */
		default_volume = 20;
		cx18_av_write(cx, 0x8d4, 20);
	}
	default_volume = (((228 - default_volume) >> 1) + 23) << 9;
	state->volume->cur.val = state->volume->default_value = default_volume;
	v4l2_ctrl_handler_setup(&state->hdl);
}