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
struct cx18_card_audio_input {int audio_input; scalar_t__ muxer_input; } ;
struct cx18 {size_t audio_input; TYPE_1__* card; int /*<<< orphan*/  sd_extmux; int /*<<< orphan*/  i_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_audio_ctrl; struct cx18_card_audio_input* audio_inputs; struct cx18_card_audio_input radio_input; } ;

/* Variables and functions */
 int CX18_AI1_MUX_843_I2S ; 
 int CX18_AI1_MUX_I2S1 ; 
 int CX18_AI1_MUX_I2S2 ; 
 int CX18_AI1_MUX_MASK ; 
 int /*<<< orphan*/  CX18_AUDIO_ENABLE ; 
#define  CX18_AV_AUDIO_SERIAL1 129 
#define  CX18_AV_AUDIO_SERIAL2 128 
 int /*<<< orphan*/  CX18_F_I_RADIO_USER ; 
 int /*<<< orphan*/  audio ; 
 int cx18_call_hw_err (struct cx18*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cx18_read_reg (struct cx18*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_write_reg_expect (struct cx18*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  s_routing ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cx18_audio_set_io(struct cx18 *cx)
{
	const struct cx18_card_audio_input *in;
	u32 u, v;
	int err;

	/* Determine which input to use */
	if (test_bit(CX18_F_I_RADIO_USER, &cx->i_flags))
		in = &cx->card->radio_input;
	else
		in = &cx->card->audio_inputs[cx->audio_input];

	/* handle muxer chips */
	v4l2_subdev_call(cx->sd_extmux, audio, s_routing,
			 (u32) in->muxer_input, 0, 0);

	err = cx18_call_hw_err(cx, cx->card->hw_audio_ctrl,
			       audio, s_routing, in->audio_input, 0, 0);
	if (err)
		return err;

	/* FIXME - this internal mux should be abstracted to a subdev */
	u = cx18_read_reg(cx, CX18_AUDIO_ENABLE);
	v = u & ~CX18_AI1_MUX_MASK;
	switch (in->audio_input) {
	case CX18_AV_AUDIO_SERIAL1:
		v |= CX18_AI1_MUX_I2S1;
		break;
	case CX18_AV_AUDIO_SERIAL2:
		v |= CX18_AI1_MUX_I2S2;
		break;
	default:
		v |= CX18_AI1_MUX_843_I2S;
		break;
	}
	if (v == u) {
		/* force a toggle of some AI1 MUX control bits */
		u &= ~CX18_AI1_MUX_MASK;
		switch (in->audio_input) {
		case CX18_AV_AUDIO_SERIAL1:
			u |= CX18_AI1_MUX_843_I2S;
			break;
		case CX18_AV_AUDIO_SERIAL2:
			u |= CX18_AI1_MUX_843_I2S;
			break;
		default:
			u |= CX18_AI1_MUX_I2S1;
			break;
		}
		cx18_write_reg_expect(cx, u | 0xb00, CX18_AUDIO_ENABLE,
				      u, CX18_AI1_MUX_MASK);
	}
	cx18_write_reg_expect(cx, v | 0xb00, CX18_AUDIO_ENABLE,
			      v, CX18_AI1_MUX_MASK);
	return 0;
}