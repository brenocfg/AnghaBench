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
struct v4l2_ext_controls {unsigned int count; scalar_t__ which; unsigned int error_idx; struct v4l2_ext_control* controls; } ;
struct v4l2_ext_control {int value; scalar_t__ value64; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__* mc_head; } ;
struct pvr2_v4l2_fh {TYPE_2__ channel; } ;
struct pvr2_hdw {int dummy; } ;
struct pvr2_ctrl {int dummy; } ;
struct file {struct pvr2_v4l2_fh* private_data; } ;
struct TYPE_3__ {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_CTRL_WHICH_DEF_VAL ; 
 int /*<<< orphan*/  pvr2_ctrl_get_def (struct pvr2_ctrl*,int*) ; 
 int pvr2_ctrl_get_value (struct pvr2_ctrl*,int*) ; 
 struct pvr2_ctrl* pvr2_hdw_get_ctrl_v4l (struct pvr2_hdw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvr2_g_ext_ctrls(struct file *file, void *priv,
					struct v4l2_ext_controls *ctls)
{
	struct pvr2_v4l2_fh *fh = file->private_data;
	struct pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	struct v4l2_ext_control *ctrl;
	struct pvr2_ctrl *cptr;
	unsigned int idx;
	int val;
	int ret;

	ret = 0;
	for (idx = 0; idx < ctls->count; idx++) {
		ctrl = ctls->controls + idx;
		cptr = pvr2_hdw_get_ctrl_v4l(hdw, ctrl->id);
		if (cptr) {
			if (ctls->which == V4L2_CTRL_WHICH_DEF_VAL)
				pvr2_ctrl_get_def(cptr, &val);
			else
				ret = pvr2_ctrl_get_value(cptr, &val);
		} else
			ret = -EINVAL;

		if (ret) {
			ctls->error_idx = idx;
			return ret;
		}
		/* Ensure that if read as a 64 bit value, the user
		   will still get a hopefully sane value */
		ctrl->value64 = 0;
		ctrl->value = val;
	}
	return 0;
}