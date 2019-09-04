#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cx18 {int nof_inputs; int nof_audio_inputs; int active_input; TYPE_3__* card; int /*<<< orphan*/  audio_input; } ;
struct TYPE_6__ {TYPE_2__* video_inputs; TYPE_1__* audio_inputs; } ;
struct TYPE_5__ {scalar_t__ video_type; int /*<<< orphan*/  audio_index; } ;
struct TYPE_4__ {scalar_t__ audio_type; } ;

/* Variables and functions */
 scalar_t__ CX18_CARD_INPUT_VID_TUNER ; 
 int CX18_CARD_MAX_AUDIO_INPUTS ; 
 int CX18_CARD_MAX_VIDEO_INPUTS ; 

__attribute__((used)) static void cx18_init_struct2(struct cx18 *cx)
{
	int i;

	for (i = 0; i < CX18_CARD_MAX_VIDEO_INPUTS - 1; i++)
		if (cx->card->video_inputs[i].video_type == 0)
			break;
	cx->nof_inputs = i;
	for (i = 0; i < CX18_CARD_MAX_AUDIO_INPUTS - 1; i++)
		if (cx->card->audio_inputs[i].audio_type == 0)
			break;
	cx->nof_audio_inputs = i;

	/* Find tuner input */
	for (i = 0; i < cx->nof_inputs; i++) {
		if (cx->card->video_inputs[i].video_type ==
				CX18_CARD_INPUT_VID_TUNER)
			break;
	}
	if (i == cx->nof_inputs)
		i = 0;
	cx->active_input = i;
	cx->audio_input = cx->card->video_inputs[i].audio_index;
}