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
typedef  int u16 ;
struct v4l2_audio {int index; int /*<<< orphan*/  capability; int /*<<< orphan*/  name; } ;
struct ivtv_card_audio_input {int audio_type; } ;
struct ivtv {int nof_audio_inputs; TYPE_1__* card; } ;
struct TYPE_2__ {struct ivtv_card_audio_input* audio_inputs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_AUDCAP_STEREO ; 
 int /*<<< orphan*/  memset (struct v4l2_audio*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const* const,int) ; 

int ivtv_get_audio_input(struct ivtv *itv, u16 index, struct v4l2_audio *audio)
{
	const struct ivtv_card_audio_input *aud_input = itv->card->audio_inputs + index;
	static const char * const input_strs[] = {
		"Tuner 1",
		"Line In 1",
		"Line In 2"
	};

	memset(audio, 0, sizeof(*audio));
	if (index >= itv->nof_audio_inputs)
		return -EINVAL;
	strlcpy(audio->name, input_strs[aud_input->audio_type - 1],
			sizeof(audio->name));
	audio->index = index;
	audio->capability = V4L2_AUDCAP_STEREO;
	return 0;
}