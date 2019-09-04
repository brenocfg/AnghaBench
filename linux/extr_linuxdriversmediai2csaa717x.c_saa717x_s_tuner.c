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
struct v4l2_tuner {int audmode; } ;
struct v4l2_subdev {int dummy; } ;
struct saa717x_state {int tuner_audio_mode; } ;

/* Variables and functions */
 int TUNER_AUDIO_LANG1 ; 
 int TUNER_AUDIO_LANG2 ; 
 int TUNER_AUDIO_MONO ; 
 int TUNER_AUDIO_STEREO ; 
#define  V4L2_TUNER_MODE_LANG1 131 
#define  V4L2_TUNER_MODE_LANG2 130 
#define  V4L2_TUNER_MODE_MONO 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  set_audio_mode (struct v4l2_subdev*,int) ; 
 struct saa717x_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,char*) ; 

__attribute__((used)) static int saa717x_s_tuner(struct v4l2_subdev *sd, const struct v4l2_tuner *vt)
{
	struct saa717x_state *decoder = to_state(sd);
	int audio_mode;
	char *mes[4] = {
		"MONO", "STEREO", "LANG1", "LANG2/SAP"
	};

	audio_mode = TUNER_AUDIO_STEREO;

	switch (vt->audmode) {
		case V4L2_TUNER_MODE_MONO:
			audio_mode = TUNER_AUDIO_MONO;
			break;
		case V4L2_TUNER_MODE_STEREO:
			audio_mode = TUNER_AUDIO_STEREO;
			break;
		case V4L2_TUNER_MODE_LANG2:
			audio_mode = TUNER_AUDIO_LANG2;
			break;
		case V4L2_TUNER_MODE_LANG1:
			audio_mode = TUNER_AUDIO_LANG1;
			break;
	}

	v4l2_dbg(1, debug, sd, "change audio mode to %s\n",
			mes[audio_mode]);
	decoder->tuner_audio_mode = audio_mode;
	/* The registers are not changed here. */
	/* See DECODER_ENABLE_OUTPUT section. */
	set_audio_mode(sd, decoder->tuner_audio_mode);
	return 0;
}