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
typedef  int u8 ;
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct cx18_av_state {int vid_input; int aud_input; struct v4l2_subdev sd; } ;
struct cx18 {struct cx18_av_state av_state; } ;
typedef  enum cx18_av_video_input { ____Placeholder_cx18_av_video_input } cx18_av_video_input ;
typedef  enum cx18_av_audio_input { ____Placeholder_cx18_av_audio_input } cx18_av_audio_input ;

/* Variables and functions */
#define  CX18_AV_AUDIO4 134 
#define  CX18_AV_AUDIO5 133 
#define  CX18_AV_AUDIO6 132 
#define  CX18_AV_AUDIO7 131 
#define  CX18_AV_AUDIO8 130 
#define  CX18_AV_AUDIO_SERIAL1 129 
#define  CX18_AV_AUDIO_SERIAL2 128 
 int CX18_AV_COMPONENT_B_CHROMA7 ; 
 int CX18_AV_COMPONENT_B_CHROMA8 ; 
 int CX18_AV_COMPONENT_LUMA1 ; 
 int CX18_AV_COMPONENT_LUMA8 ; 
 int CX18_AV_COMPONENT_R_CHROMA4 ; 
 int CX18_AV_COMPONENT_R_CHROMA6 ; 
 int CX18_AV_COMPOSITE1 ; 
 int CX18_AV_COMPOSITE8 ; 
 int CX18_AV_SVIDEO_CHROMA4 ; 
 int CX18_AV_SVIDEO_CHROMA7 ; 
 int CX18_AV_SVIDEO_CHROMA8 ; 
 int CX18_AV_SVIDEO_LUMA1 ; 
 int CX18_AV_SVIDEO_LUMA8 ; 
 int /*<<< orphan*/  CX18_DEBUG_INFO_DEV (struct v4l2_subdev*,char*,int,int) ; 
 int /*<<< orphan*/  CX18_ERR_DEV (struct v4l2_subdev*,char*,int) ; 
 int /*<<< orphan*/  CXADEC_AFE_CTRL ; 
 int EINVAL ; 
 int /*<<< orphan*/  cx18_av_and_or (struct cx18*,int,int,int) ; 
 int /*<<< orphan*/  cx18_av_audio_set_path (struct cx18*) ; 
 int cx18_av_read (struct cx18*,int) ; 
 int cx18_av_read4 (struct cx18*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_av_write4 (struct cx18*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx18_av_write_expect (struct cx18*,int,int,int,int) ; 
 int /*<<< orphan*/  input_change (struct cx18*) ; 

__attribute__((used)) static int set_input(struct cx18 *cx, enum cx18_av_video_input vid_input,
					enum cx18_av_audio_input aud_input)
{
	struct cx18_av_state *state = &cx->av_state;
	struct v4l2_subdev *sd = &state->sd;

	enum analog_signal_type {
		NONE, CVBS, Y, C, SIF, Pb, Pr
	} ch[3] = {NONE, NONE, NONE};

	u8 afe_mux_cfg;
	u8 adc2_cfg;
	u8 input_mode;
	u32 afe_cfg;
	int i;

	CX18_DEBUG_INFO_DEV(sd, "decoder set video input %d, audio input %d\n",
			    vid_input, aud_input);

	if (vid_input >= CX18_AV_COMPOSITE1 &&
	    vid_input <= CX18_AV_COMPOSITE8) {
		afe_mux_cfg = 0xf0 + (vid_input - CX18_AV_COMPOSITE1);
		ch[0] = CVBS;
		input_mode = 0x0;
	} else if (vid_input >= CX18_AV_COMPONENT_LUMA1) {
		int luma = vid_input & 0xf000;
		int r_chroma = vid_input & 0xf0000;
		int b_chroma = vid_input & 0xf00000;

		if ((vid_input & ~0xfff000) ||
		    luma < CX18_AV_COMPONENT_LUMA1 ||
		    luma > CX18_AV_COMPONENT_LUMA8 ||
		    r_chroma < CX18_AV_COMPONENT_R_CHROMA4 ||
		    r_chroma > CX18_AV_COMPONENT_R_CHROMA6 ||
		    b_chroma < CX18_AV_COMPONENT_B_CHROMA7 ||
		    b_chroma > CX18_AV_COMPONENT_B_CHROMA8) {
			CX18_ERR_DEV(sd, "0x%06x is not a valid video input!\n",
				     vid_input);
			return -EINVAL;
		}
		afe_mux_cfg = (luma - CX18_AV_COMPONENT_LUMA1) >> 12;
		ch[0] = Y;
		afe_mux_cfg |= (r_chroma - CX18_AV_COMPONENT_R_CHROMA4) >> 12;
		ch[1] = Pr;
		afe_mux_cfg |= (b_chroma - CX18_AV_COMPONENT_B_CHROMA7) >> 14;
		ch[2] = Pb;
		input_mode = 0x6;
	} else {
		int luma = vid_input & 0xf0;
		int chroma = vid_input & 0xf00;

		if ((vid_input & ~0xff0) ||
		    luma < CX18_AV_SVIDEO_LUMA1 ||
		    luma > CX18_AV_SVIDEO_LUMA8 ||
		    chroma < CX18_AV_SVIDEO_CHROMA4 ||
		    chroma > CX18_AV_SVIDEO_CHROMA8) {
			CX18_ERR_DEV(sd, "0x%06x is not a valid video input!\n",
				     vid_input);
			return -EINVAL;
		}
		afe_mux_cfg = 0xf0 + ((luma - CX18_AV_SVIDEO_LUMA1) >> 4);
		ch[0] = Y;
		if (chroma >= CX18_AV_SVIDEO_CHROMA7) {
			afe_mux_cfg &= 0x3f;
			afe_mux_cfg |= (chroma - CX18_AV_SVIDEO_CHROMA7) >> 2;
			ch[2] = C;
		} else {
			afe_mux_cfg &= 0xcf;
			afe_mux_cfg |= (chroma - CX18_AV_SVIDEO_CHROMA4) >> 4;
			ch[1] = C;
		}
		input_mode = 0x2;
	}

	switch (aud_input) {
	case CX18_AV_AUDIO_SERIAL1:
	case CX18_AV_AUDIO_SERIAL2:
		/* do nothing, use serial audio input */
		break;
	case CX18_AV_AUDIO4:
		afe_mux_cfg &= ~0x30;
		ch[1] = SIF;
		break;
	case CX18_AV_AUDIO5:
		afe_mux_cfg = (afe_mux_cfg & ~0x30) | 0x10;
		ch[1] = SIF;
		break;
	case CX18_AV_AUDIO6:
		afe_mux_cfg = (afe_mux_cfg & ~0x30) | 0x20;
		ch[1] = SIF;
		break;
	case CX18_AV_AUDIO7:
		afe_mux_cfg &= ~0xc0;
		ch[2] = SIF;
		break;
	case CX18_AV_AUDIO8:
		afe_mux_cfg = (afe_mux_cfg & ~0xc0) | 0x40;
		ch[2] = SIF;
		break;

	default:
		CX18_ERR_DEV(sd, "0x%04x is not a valid audio input!\n",
			     aud_input);
		return -EINVAL;
	}

	/* Set up analog front end multiplexers */
	cx18_av_write_expect(cx, 0x103, afe_mux_cfg, afe_mux_cfg, 0xf7);
	/* Set INPUT_MODE to Composite, S-Video, or Component */
	cx18_av_and_or(cx, 0x401, ~0x6, input_mode);

	/* Set CH_SEL_ADC2 to 1 if input comes from CH3 */
	adc2_cfg = cx18_av_read(cx, 0x102);
	if (ch[2] == NONE)
		adc2_cfg &= ~0x2; /* No sig on CH3, set ADC2 to CH2 for input */
	else
		adc2_cfg |= 0x2;  /* Signal on CH3, set ADC2 to CH3 for input */

	/* Set DUAL_MODE_ADC2 to 1 if input comes from both CH2 and CH3 */
	if (ch[1] != NONE && ch[2] != NONE)
		adc2_cfg |= 0x4; /* Set dual mode */
	else
		adc2_cfg &= ~0x4; /* Clear dual mode */
	cx18_av_write_expect(cx, 0x102, adc2_cfg, adc2_cfg, 0x17);

	/* Configure the analog front end */
	afe_cfg = cx18_av_read4(cx, CXADEC_AFE_CTRL);
	afe_cfg &= 0xff000000;
	afe_cfg |= 0x00005000; /* CHROMA_IN, AUD_IN: ADC2; LUMA_IN: ADC1 */
	if (ch[1] != NONE && ch[2] != NONE)
		afe_cfg |= 0x00000030; /* half_bw_ch[2-3] since in dual mode */

	for (i = 0; i < 3; i++) {
		switch (ch[i]) {
		default:
		case NONE:
			/* CLAMP_SEL = Fixed to midcode clamp level */
			afe_cfg |= (0x00000200 << i);
			break;
		case CVBS:
		case Y:
			if (i > 0)
				afe_cfg |= 0x00002000; /* LUMA_IN_SEL: ADC2 */
			break;
		case C:
		case Pb:
		case Pr:
			/* CLAMP_SEL = Fixed to midcode clamp level */
			afe_cfg |= (0x00000200 << i);
			if (i == 0 && ch[i] == C)
				afe_cfg &= ~0x00001000; /* CHROMA_IN_SEL ADC1 */
			break;
		case SIF:
			/*
			 * VGA_GAIN_SEL = Audio Decoder
			 * CLAMP_SEL = Fixed to midcode clamp level
			 */
			afe_cfg |= (0x00000240 << i);
			if (i == 0)
				afe_cfg &= ~0x00004000; /* AUD_IN_SEL ADC1 */
			break;
		}
	}

	cx18_av_write4(cx, CXADEC_AFE_CTRL, afe_cfg);

	state->vid_input = vid_input;
	state->aud_input = aud_input;
	cx18_av_audio_set_path(cx);
	input_change(cx);
	return 0;
}