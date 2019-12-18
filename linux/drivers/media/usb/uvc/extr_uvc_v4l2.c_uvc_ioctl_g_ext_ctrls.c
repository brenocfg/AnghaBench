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
struct v4l2_queryctrl {int /*<<< orphan*/  default_value; int /*<<< orphan*/  id; } ;
struct v4l2_ext_controls {scalar_t__ which; unsigned int count; unsigned int error_idx; struct v4l2_ext_control* controls; } ;
struct v4l2_ext_control {int /*<<< orphan*/  value; int /*<<< orphan*/  id; } ;
struct uvc_video_chain {int dummy; } ;
struct uvc_fh {struct uvc_video_chain* chain; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ V4L2_CTRL_WHICH_DEF_VAL ; 
 int uvc_ctrl_begin (struct uvc_video_chain*) ; 
 int uvc_ctrl_get (struct uvc_video_chain*,struct v4l2_ext_control*) ; 
 int uvc_ctrl_rollback (struct uvc_fh*) ; 
 int uvc_query_v4l2_ctrl (struct uvc_video_chain*,struct v4l2_queryctrl*) ; 

__attribute__((used)) static int uvc_ioctl_g_ext_ctrls(struct file *file, void *fh,
				 struct v4l2_ext_controls *ctrls)
{
	struct uvc_fh *handle = fh;
	struct uvc_video_chain *chain = handle->chain;
	struct v4l2_ext_control *ctrl = ctrls->controls;
	unsigned int i;
	int ret;

	if (ctrls->which == V4L2_CTRL_WHICH_DEF_VAL) {
		for (i = 0; i < ctrls->count; ++ctrl, ++i) {
			struct v4l2_queryctrl qc = { .id = ctrl->id };

			ret = uvc_query_v4l2_ctrl(chain, &qc);
			if (ret < 0) {
				ctrls->error_idx = i;
				return ret;
			}

			ctrl->value = qc.default_value;
		}

		return 0;
	}

	ret = uvc_ctrl_begin(chain);
	if (ret < 0)
		return ret;

	for (i = 0; i < ctrls->count; ++ctrl, ++i) {
		ret = uvc_ctrl_get(chain, ctrl);
		if (ret < 0) {
			uvc_ctrl_rollback(handle);
			ctrls->error_idx = i;
			return ret;
		}
	}

	ctrls->error_idx = 0;

	return uvc_ctrl_rollback(handle);
}