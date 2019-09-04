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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct bttv {scalar_t__ sd_tvaudio; scalar_t__ sd_msp34xx; TYPE_1__ c; int /*<<< orphan*/  radio_uses_msp_demodulator; int /*<<< orphan*/  mute; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTTV_BOARD_VOODOOTV_200 ; 
 int /*<<< orphan*/  MSP_DSP_IN_SCART ; 
 int /*<<< orphan*/  MSP_DSP_IN_TUNER ; 
 int MSP_INPUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MSP_INPUT_DEFAULT ; 
 int /*<<< orphan*/  MSP_IN_SCART1 ; 
 int /*<<< orphan*/  MSP_IN_SCART2 ; 
 int /*<<< orphan*/  MSP_IN_TUNER1 ; 
 int /*<<< orphan*/  MSP_IN_TUNER2 ; 
 int /*<<< orphan*/  MSP_OUTPUT_DEFAULT ; 
#define  TVAUDIO_INPUT_EXTERN 131 
#define  TVAUDIO_INPUT_INTERN 130 
#define  TVAUDIO_INPUT_RADIO 129 
#define  TVAUDIO_INPUT_TUNER 128 
 int /*<<< orphan*/  audio ; 
 int /*<<< orphan*/  audio_mux_gpio (struct bttv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_routing ; 
 int /*<<< orphan*/  v4l2_subdev_call (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
audio_input(struct bttv *btv, int input)
{
	audio_mux_gpio(btv, input, btv->mute);

	if (btv->sd_msp34xx) {
		u32 in;

		/* Note: the inputs tuner/radio/extern/intern are translated
		   to msp routings. This assumes common behavior for all msp3400
		   based TV cards. When this assumption fails, then the
		   specific MSP routing must be added to the card table.
		   For now this is sufficient. */
		switch (input) {
		case TVAUDIO_INPUT_RADIO:
			/* Some boards need the msp do to the radio demod */
			if (btv->radio_uses_msp_demodulator) {
				in = MSP_INPUT_DEFAULT;
				break;
			}
			in = MSP_INPUT(MSP_IN_SCART2, MSP_IN_TUNER1,
				    MSP_DSP_IN_SCART, MSP_DSP_IN_SCART);
			break;
		case TVAUDIO_INPUT_EXTERN:
			in = MSP_INPUT(MSP_IN_SCART1, MSP_IN_TUNER1,
				    MSP_DSP_IN_SCART, MSP_DSP_IN_SCART);
			break;
		case TVAUDIO_INPUT_INTERN:
			/* Yes, this is the same input as for RADIO. I doubt
			   if this is ever used. The only board with an INTERN
			   input is the BTTV_BOARD_AVERMEDIA98. I wonder how
			   that was tested. My guess is that the whole INTERN
			   input does not work. */
			in = MSP_INPUT(MSP_IN_SCART2, MSP_IN_TUNER1,
				    MSP_DSP_IN_SCART, MSP_DSP_IN_SCART);
			break;
		case TVAUDIO_INPUT_TUNER:
		default:
			/* This is the only card that uses TUNER2, and afaik,
			   is the only difference between the VOODOOTV_FM
			   and VOODOOTV_200 */
			if (btv->c.type == BTTV_BOARD_VOODOOTV_200)
				in = MSP_INPUT(MSP_IN_SCART1, MSP_IN_TUNER2, \
					MSP_DSP_IN_TUNER, MSP_DSP_IN_TUNER);
			else
				in = MSP_INPUT_DEFAULT;
			break;
		}
		v4l2_subdev_call(btv->sd_msp34xx, audio, s_routing,
			       in, MSP_OUTPUT_DEFAULT, 0);
	}
	if (btv->sd_tvaudio) {
		v4l2_subdev_call(btv->sd_tvaudio, audio, s_routing,
				 input, 0, 0);
	}
	return 0;
}