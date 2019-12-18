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
typedef  scalar_t__ u32 ;
struct ivtv_card_audio_input {scalar_t__ audio_input; scalar_t__ muxer_input; } ;
struct ivtv {size_t audio_input; TYPE_1__* card; int /*<<< orphan*/  sd_muxer; int /*<<< orphan*/  i_flags; } ;
struct TYPE_2__ {int hw_muxer; int hw_audio; struct ivtv_card_audio_input* audio_inputs; struct ivtv_card_audio_input radio_input; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_F_I_RADIO_USER ; 
 int IVTV_HW_M52790 ; 
 int IVTV_HW_MSP34XX ; 
 scalar_t__ M52790_OUT_STEREO ; 
 scalar_t__ MSP_OUTPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSP_SC_IN_DSP_SCART1 ; 
 int /*<<< orphan*/  audio ; 
 int /*<<< orphan*/  ivtv_call_hw (struct ivtv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_routing ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

void ivtv_audio_set_io(struct ivtv *itv)
{
	const struct ivtv_card_audio_input *in;
	u32 input, output = 0;

	/* Determine which input to use */
	if (test_bit(IVTV_F_I_RADIO_USER, &itv->i_flags))
		in = &itv->card->radio_input;
	else
		in = &itv->card->audio_inputs[itv->audio_input];

	/* handle muxer chips */
	input = in->muxer_input;
	if (itv->card->hw_muxer & IVTV_HW_M52790)
		output = M52790_OUT_STEREO;
	v4l2_subdev_call(itv->sd_muxer, audio, s_routing,
			input, output, 0);

	input = in->audio_input;
	output = 0;
	if (itv->card->hw_audio & IVTV_HW_MSP34XX)
		output = MSP_OUTPUT(MSP_SC_IN_DSP_SCART1);
	ivtv_call_hw(itv, itv->card->hw_audio, audio, s_routing,
			input, output, 0);
}