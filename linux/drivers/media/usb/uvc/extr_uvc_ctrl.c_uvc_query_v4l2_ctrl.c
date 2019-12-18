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
struct v4l2_queryctrl {int /*<<< orphan*/  id; } ;
struct uvc_video_chain {int /*<<< orphan*/  ctrl_mutex; } ;
struct uvc_control_mapping {int dummy; } ;
struct uvc_control {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERESTARTSYS ; 
 int __uvc_query_v4l2_ctrl (struct uvc_video_chain*,struct uvc_control*,struct uvc_control_mapping*,struct v4l2_queryctrl*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct uvc_control* uvc_find_control (struct uvc_video_chain*,int /*<<< orphan*/ ,struct uvc_control_mapping**) ; 

int uvc_query_v4l2_ctrl(struct uvc_video_chain *chain,
	struct v4l2_queryctrl *v4l2_ctrl)
{
	struct uvc_control *ctrl;
	struct uvc_control_mapping *mapping;
	int ret;

	ret = mutex_lock_interruptible(&chain->ctrl_mutex);
	if (ret < 0)
		return -ERESTARTSYS;

	ctrl = uvc_find_control(chain, v4l2_ctrl->id, &mapping);
	if (ctrl == NULL) {
		ret = -EINVAL;
		goto done;
	}

	ret = __uvc_query_v4l2_ctrl(chain, ctrl, mapping, v4l2_ctrl);
done:
	mutex_unlock(&chain->ctrl_mutex);
	return ret;
}