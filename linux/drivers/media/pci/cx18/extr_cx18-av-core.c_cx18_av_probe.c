#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {TYPE_2__* ctrl_handler; int /*<<< orphan*/  grp_id; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int error; } ;
struct cx18_av_state {int rev; int audclk_freq; TYPE_2__ hdl; int /*<<< orphan*/  volume; struct v4l2_subdev sd; scalar_t__ slicer_line_delay; scalar_t__ slicer_line_offset; int /*<<< orphan*/  audmode; int /*<<< orphan*/  aud_input; int /*<<< orphan*/  vid_input; } ;
struct TYPE_5__ {char* name; } ;
struct cx18 {TYPE_1__ v4l2_dev; struct cx18_av_state av_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_AV_AUDIO8 ; 
 int /*<<< orphan*/  CX18_AV_COMPOSITE7 ; 
 int /*<<< orphan*/  CX18_HW_418_AV ; 
 int /*<<< orphan*/  CXADEC_CHIP_CTRL ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_BASS ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_MUTE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_TREBLE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_VOLUME ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_HUE ; 
 int /*<<< orphan*/  V4L2_CID_SATURATION ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_LANG1 ; 
 int /*<<< orphan*/  cx18_av_audio_ctrl_ops ; 
 int /*<<< orphan*/  cx18_av_ctrl_ops ; 
 int /*<<< orphan*/  cx18_av_init (struct cx18*) ; 
 int /*<<< orphan*/  cx18_av_ops ; 
 int cx18_av_read4 (struct cx18*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_2__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int v4l2_device_register_subdev (TYPE_1__*,struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (struct v4l2_subdev*,struct cx18*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 

int cx18_av_probe(struct cx18 *cx)
{
	struct cx18_av_state *state = &cx->av_state;
	struct v4l2_subdev *sd;
	int err;

	state->rev = cx18_av_read4(cx, CXADEC_CHIP_CTRL) & 0xffff;

	state->vid_input = CX18_AV_COMPOSITE7;
	state->aud_input = CX18_AV_AUDIO8;
	state->audclk_freq = 48000;
	state->audmode = V4L2_TUNER_MODE_LANG1;
	state->slicer_line_delay = 0;
	state->slicer_line_offset = (10 + state->slicer_line_delay - 2);

	sd = &state->sd;
	v4l2_subdev_init(sd, &cx18_av_ops);
	v4l2_set_subdevdata(sd, cx);
	snprintf(sd->name, sizeof(sd->name),
		 "%s %03x", cx->v4l2_dev.name, (state->rev >> 4));
	sd->grp_id = CX18_HW_418_AV;
	v4l2_ctrl_handler_init(&state->hdl, 9);
	v4l2_ctrl_new_std(&state->hdl, &cx18_av_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&state->hdl, &cx18_av_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 127, 1, 64);
	v4l2_ctrl_new_std(&state->hdl, &cx18_av_ctrl_ops,
			V4L2_CID_SATURATION, 0, 127, 1, 64);
	v4l2_ctrl_new_std(&state->hdl, &cx18_av_ctrl_ops,
			V4L2_CID_HUE, -128, 127, 1, 0);

	state->volume = v4l2_ctrl_new_std(&state->hdl,
			&cx18_av_audio_ctrl_ops, V4L2_CID_AUDIO_VOLUME,
			0, 65535, 65535 / 100, 0);
	v4l2_ctrl_new_std(&state->hdl,
			&cx18_av_audio_ctrl_ops, V4L2_CID_AUDIO_MUTE,
			0, 1, 1, 0);
	v4l2_ctrl_new_std(&state->hdl, &cx18_av_audio_ctrl_ops,
			V4L2_CID_AUDIO_BALANCE,
			0, 65535, 65535 / 100, 32768);
	v4l2_ctrl_new_std(&state->hdl, &cx18_av_audio_ctrl_ops,
			V4L2_CID_AUDIO_BASS,
			0, 65535, 65535 / 100, 32768);
	v4l2_ctrl_new_std(&state->hdl, &cx18_av_audio_ctrl_ops,
			V4L2_CID_AUDIO_TREBLE,
			0, 65535, 65535 / 100, 32768);
	sd->ctrl_handler = &state->hdl;
	if (state->hdl.error) {
		int err = state->hdl.error;

		v4l2_ctrl_handler_free(&state->hdl);
		return err;
	}
	err = v4l2_device_register_subdev(&cx->v4l2_dev, sd);
	if (err)
		v4l2_ctrl_handler_free(&state->hdl);
	else
		cx18_av_init(cx);
	return err;
}