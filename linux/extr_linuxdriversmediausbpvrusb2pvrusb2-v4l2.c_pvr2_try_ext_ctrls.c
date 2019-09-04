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
struct v4l2_ext_controls {unsigned int count; unsigned int error_idx; struct v4l2_ext_control* controls; } ;
struct v4l2_ext_control {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__* mc_head; } ;
struct pvr2_v4l2_fh {TYPE_2__ channel; } ;
struct pvr2_hdw {int dummy; } ;
struct pvr2_ctrl {int dummy; } ;
struct file {struct pvr2_v4l2_fh* private_data; } ;
struct TYPE_3__ {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pvr2_ctrl* pvr2_hdw_get_ctrl_v4l (struct pvr2_hdw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvr2_try_ext_ctrls(struct file *file, void *priv,
		struct v4l2_ext_controls *ctls)
{
	struct pvr2_v4l2_fh *fh = file->private_data;
	struct pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	struct v4l2_ext_control *ctrl;
	struct pvr2_ctrl *pctl;
	unsigned int idx;

	/* For the moment just validate that the requested control
	   actually exists. */
	for (idx = 0; idx < ctls->count; idx++) {
		ctrl = ctls->controls + idx;
		pctl = pvr2_hdw_get_ctrl_v4l(hdw, ctrl->id);
		if (!pctl) {
			ctls->error_idx = idx;
			return -EINVAL;
		}
	}
	return 0;
}