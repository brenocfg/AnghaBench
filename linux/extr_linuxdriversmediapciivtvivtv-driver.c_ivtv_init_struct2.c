#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int sliced_size; } ;
struct ivtv {int nof_inputs; int nof_audio_inputs; int active_input; TYPE_4__* card; int /*<<< orphan*/  audio_input; TYPE_2__ vbi; } ;
struct TYPE_8__ {int hw_all; TYPE_3__* video_inputs; TYPE_1__* audio_inputs; } ;
struct TYPE_7__ {scalar_t__ video_type; int /*<<< orphan*/  audio_index; } ;
struct TYPE_5__ {scalar_t__ audio_type; } ;

/* Variables and functions */
 scalar_t__ IVTV_CARD_INPUT_VID_TUNER ; 
 int IVTV_CARD_MAX_AUDIO_INPUTS ; 
 int IVTV_CARD_MAX_VIDEO_INPUTS ; 
 int IVTV_HW_CX25840 ; 

__attribute__((used)) static void ivtv_init_struct2(struct ivtv *itv)
{
	int i;

	for (i = 0; i < IVTV_CARD_MAX_VIDEO_INPUTS; i++)
		if (itv->card->video_inputs[i].video_type == 0)
			break;
	itv->nof_inputs = i;
	for (i = 0; i < IVTV_CARD_MAX_AUDIO_INPUTS; i++)
		if (itv->card->audio_inputs[i].audio_type == 0)
			break;
	itv->nof_audio_inputs = i;

	if (itv->card->hw_all & IVTV_HW_CX25840) {
		itv->vbi.sliced_size = 288;  /* multiple of 16, real size = 284 */
	} else {
		itv->vbi.sliced_size = 64;   /* multiple of 16, real size = 52 */
	}

	/* Find tuner input */
	for (i = 0; i < itv->nof_inputs; i++) {
		if (itv->card->video_inputs[i].video_type ==
				IVTV_CARD_INPUT_VID_TUNER)
			break;
	}
	if (i >= itv->nof_inputs)
		i = 0;
	itv->active_input = i;
	itv->audio_input = itv->card->video_inputs[i].audio_index;
}