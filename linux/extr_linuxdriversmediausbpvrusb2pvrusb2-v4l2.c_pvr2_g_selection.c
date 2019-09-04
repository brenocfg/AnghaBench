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
struct TYPE_6__ {int left; int top; int width; int height; } ;
struct v4l2_selection {scalar_t__ type; int target; TYPE_3__ r; } ;
struct v4l2_cropcap {TYPE_3__ bounds; TYPE_3__ defrect; scalar_t__ type; } ;
struct TYPE_5__ {TYPE_1__* mc_head; } ;
struct pvr2_v4l2_fh {TYPE_2__ channel; } ;
struct pvr2_hdw {int dummy; } ;
struct file {struct pvr2_v4l2_fh* private_data; } ;
struct TYPE_4__ {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PVR2_CID_CROPH ; 
 int /*<<< orphan*/  PVR2_CID_CROPL ; 
 int /*<<< orphan*/  PVR2_CID_CROPT ; 
 int /*<<< orphan*/  PVR2_CID_CROPW ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 int pvr2_ctrl_get_value (int /*<<< orphan*/ ,int*) ; 
 int pvr2_hdw_get_cropcap (struct pvr2_hdw*,struct v4l2_cropcap*) ; 
 int /*<<< orphan*/  pvr2_hdw_get_ctrl_by_id (struct pvr2_hdw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvr2_g_selection(struct file *file, void *priv,
			    struct v4l2_selection *sel)
{
	struct pvr2_v4l2_fh *fh = file->private_data;
	struct pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	struct v4l2_cropcap cap;
	int val = 0;
	int ret;

	if (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	cap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	switch (sel->target) {
	case V4L2_SEL_TGT_CROP:
		ret = pvr2_ctrl_get_value(
			  pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPL), &val);
		if (ret != 0)
			return -EINVAL;
		sel->r.left = val;
		ret = pvr2_ctrl_get_value(
			  pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPT), &val);
		if (ret != 0)
			return -EINVAL;
		sel->r.top = val;
		ret = pvr2_ctrl_get_value(
			  pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPW), &val);
		if (ret != 0)
			return -EINVAL;
		sel->r.width = val;
		ret = pvr2_ctrl_get_value(
			  pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPH), &val);
		if (ret != 0)
			return -EINVAL;
		sel->r.height = val;
		break;
	case V4L2_SEL_TGT_CROP_DEFAULT:
		ret = pvr2_hdw_get_cropcap(hdw, &cap);
		sel->r = cap.defrect;
		break;
	case V4L2_SEL_TGT_CROP_BOUNDS:
		ret = pvr2_hdw_get_cropcap(hdw, &cap);
		sel->r = cap.bounds;
		break;
	default:
		return -EINVAL;
	}
	return ret;
}