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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_bt_timings {int /*<<< orphan*/  polarities; scalar_t__ pixelclock; scalar_t__ interlaced; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct ths7303_state {struct v4l2_bt_timings bt; scalar_t__ stream_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  THS7303_CHANNEL_1 ; 
 int /*<<< orphan*/  THS7303_CHANNEL_2 ; 
 int /*<<< orphan*/  THS7303_CHANNEL_3 ; 
 int V4L2_DV_BT_FRAME_HEIGHT (struct v4l2_bt_timings*) ; 
 int V4L2_DV_BT_FRAME_WIDTH (struct v4l2_bt_timings*) ; 
 int /*<<< orphan*/  ths7303_log_channel_status (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct ths7303_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,...) ; 

__attribute__((used)) static int ths7303_log_status(struct v4l2_subdev *sd)
{
	struct ths7303_state *state = to_state(sd);

	v4l2_info(sd, "stream %s\n", state->stream_on ? "On" : "Off");

	if (state->bt.pixelclock) {
		struct v4l2_bt_timings *bt = &state->bt;
		u32 frame_width, frame_height;

		frame_width = V4L2_DV_BT_FRAME_WIDTH(bt);
		frame_height = V4L2_DV_BT_FRAME_HEIGHT(bt);
		v4l2_info(sd,
			  "timings: %dx%d%s%d (%dx%d). Pix freq. = %d Hz. Polarities = 0x%x\n",
			  bt->width, bt->height, bt->interlaced ? "i" : "p",
			  (frame_height * frame_width) > 0 ?
			  (int)bt->pixelclock /
			  (frame_height * frame_width) : 0,
			  frame_width, frame_height,
			  (int)bt->pixelclock, bt->polarities);
	} else {
		v4l2_info(sd, "no timings set\n");
	}

	ths7303_log_channel_status(sd, THS7303_CHANNEL_1);
	ths7303_log_channel_status(sd, THS7303_CHANNEL_2);
	ths7303_log_channel_status(sd, THS7303_CHANNEL_3);

	return 0;
}