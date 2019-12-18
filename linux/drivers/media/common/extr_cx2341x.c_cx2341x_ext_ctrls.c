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
struct v4l2_queryctrl {scalar_t__ type; int /*<<< orphan*/  id; } ;
struct v4l2_ext_controls {int count; int error_idx; struct v4l2_ext_control* controls; } ;
struct v4l2_ext_control {int /*<<< orphan*/  id; } ;
struct cx2341x_mpeg_params {scalar_t__ video_bitrate_mode; scalar_t__ video_bitrate_peak; scalar_t__ video_bitrate; } ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ V4L2_CTRL_TYPE_MENU ; 
 scalar_t__ V4L2_MPEG_VIDEO_BITRATE_MODE_VBR ; 
 unsigned int VIDIOC_G_EXT_CTRLS ; 
 int /*<<< orphan*/  cx2341x_calc_audio_properties (struct cx2341x_mpeg_params*) ; 
 char** cx2341x_ctrl_get_menu (struct cx2341x_mpeg_params*,int /*<<< orphan*/ ) ; 
 int cx2341x_ctrl_query (struct cx2341x_mpeg_params*,struct v4l2_queryctrl*) ; 
 int cx2341x_get_ctrl (struct cx2341x_mpeg_params*,struct v4l2_ext_control*) ; 
 int cx2341x_set_ctrl (struct cx2341x_mpeg_params*,int,struct v4l2_ext_control*) ; 
 int v4l2_ctrl_check (struct v4l2_ext_control*,struct v4l2_queryctrl*,char const* const*) ; 

int cx2341x_ext_ctrls(struct cx2341x_mpeg_params *params, int busy,
		  struct v4l2_ext_controls *ctrls, unsigned int cmd)
{
	int err = 0;
	int i;

	if (cmd == VIDIOC_G_EXT_CTRLS) {
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			err = cx2341x_get_ctrl(params, ctrl);
			if (err) {
				ctrls->error_idx = i;
				break;
			}
		}
		return err;
	}
	for (i = 0; i < ctrls->count; i++) {
		struct v4l2_ext_control *ctrl = ctrls->controls + i;
		struct v4l2_queryctrl qctrl;
		const char * const *menu_items = NULL;

		qctrl.id = ctrl->id;
		err = cx2341x_ctrl_query(params, &qctrl);
		if (err)
			break;
		if (qctrl.type == V4L2_CTRL_TYPE_MENU)
			menu_items = cx2341x_ctrl_get_menu(params, qctrl.id);
		err = v4l2_ctrl_check(ctrl, &qctrl, menu_items);
		if (err)
			break;
		err = cx2341x_set_ctrl(params, busy, ctrl);
		if (err)
			break;
	}
	if (err == 0 &&
	    params->video_bitrate_mode == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR &&
	    params->video_bitrate_peak < params->video_bitrate) {
		err = -ERANGE;
		ctrls->error_idx = ctrls->count;
	}
	if (err)
		ctrls->error_idx = i;
	else
		cx2341x_calc_audio_properties(params);
	return err;
}