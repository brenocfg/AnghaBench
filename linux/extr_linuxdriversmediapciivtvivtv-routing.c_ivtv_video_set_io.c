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
typedef  scalar_t__ u32 ;
struct ivtv {int active_input; TYPE_2__* card; int /*<<< orphan*/  sd_video; } ;
struct TYPE_4__ {int hw_video; scalar_t__ gr_config; scalar_t__ type; TYPE_1__* video_inputs; } ;
struct TYPE_3__ {scalar_t__ video_type; int /*<<< orphan*/  video_input; } ;

/* Variables and functions */
 scalar_t__ IVTV_CARD_CX23416GYC ; 
 scalar_t__ IVTV_CARD_INPUT_COMPOSITE1 ; 
 scalar_t__ IVTV_CARD_INPUT_VID_TUNER ; 
 int IVTV_HW_GPIO ; 
 int IVTV_HW_UPD64031A ; 
 int IVTV_HW_UPD6408X ; 
 scalar_t__ UPD64031A_3DYCS_COMPOSITE ; 
 scalar_t__ UPD64031A_3DYCS_DISABLE ; 
 scalar_t__ UPD64031A_GR_OFF ; 
 scalar_t__ UPD64031A_GR_ON ; 
 scalar_t__ UPD64083_EXT_Y_ADC ; 
 scalar_t__ UPD64083_YCNR_MODE ; 
 scalar_t__ UPD64083_YCS_MODE ; 
 int /*<<< orphan*/  ivtv_call_hw (struct ivtv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_routing ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 

void ivtv_video_set_io(struct ivtv *itv)
{
	int inp = itv->active_input;
	u32 input;
	u32 type;

	v4l2_subdev_call(itv->sd_video, video, s_routing,
		itv->card->video_inputs[inp].video_input, 0, 0);

	type = itv->card->video_inputs[inp].video_type;

	if (type == IVTV_CARD_INPUT_VID_TUNER) {
		input = 0;  /* Tuner */
	} else if (type < IVTV_CARD_INPUT_COMPOSITE1) {
		input = 2;  /* S-Video */
	} else {
		input = 1;  /* Composite */
	}

	if (itv->card->hw_video & IVTV_HW_GPIO)
		ivtv_call_hw(itv, IVTV_HW_GPIO, video, s_routing,
				input, 0, 0);

	if (itv->card->hw_video & IVTV_HW_UPD64031A) {
		if (type == IVTV_CARD_INPUT_VID_TUNER ||
		    type >= IVTV_CARD_INPUT_COMPOSITE1) {
			/* Composite: GR on, connect to 3DYCS */
			input = UPD64031A_GR_ON | UPD64031A_3DYCS_COMPOSITE;
		} else {
			/* S-Video: GR bypassed, turn it off */
			input = UPD64031A_GR_OFF | UPD64031A_3DYCS_DISABLE;
		}
		input |= itv->card->gr_config;

		ivtv_call_hw(itv, IVTV_HW_UPD64031A, video, s_routing,
				input, 0, 0);
	}

	if (itv->card->hw_video & IVTV_HW_UPD6408X) {
		input = UPD64083_YCS_MODE;
		if (type > IVTV_CARD_INPUT_VID_TUNER &&
		    type < IVTV_CARD_INPUT_COMPOSITE1) {
			/* S-Video uses YCNR mode and internal Y-ADC, the
			   upd64031a is not used. */
			input |= UPD64083_YCNR_MODE;
		}
		else if (itv->card->hw_video & IVTV_HW_UPD64031A) {
			/* Use upd64031a output for tuner and
			   composite(CX23416GYC only) inputs */
			if (type == IVTV_CARD_INPUT_VID_TUNER ||
			    itv->card->type == IVTV_CARD_CX23416GYC) {
				input |= UPD64083_EXT_Y_ADC;
			}
		}
		ivtv_call_hw(itv, IVTV_HW_UPD6408X, video, s_routing,
				input, 0, 0);
	}
}