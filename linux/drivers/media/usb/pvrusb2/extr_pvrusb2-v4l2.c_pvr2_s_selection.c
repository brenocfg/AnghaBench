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
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_selection {scalar_t__ type; scalar_t__ target; TYPE_3__ r; } ;
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
 scalar_t__ V4L2_SEL_TGT_CROP ; 
 int pvr2_ctrl_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_hdw_commit_ctl (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_hdw_get_ctrl_by_id (struct pvr2_hdw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvr2_s_selection(struct file *file, void *priv,
			    struct v4l2_selection *sel)
{
	struct pvr2_v4l2_fh *fh = file->private_data;
	struct pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	int ret;

	if (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	    sel->target != V4L2_SEL_TGT_CROP)
		return -EINVAL;
	ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPL),
			sel->r.left);
	if (ret != 0)
		goto commit;
	ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPT),
			sel->r.top);
	if (ret != 0)
		goto commit;
	ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPW),
			sel->r.width);
	if (ret != 0)
		goto commit;
	ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPH),
			sel->r.height);
commit:
	pvr2_hdw_commit_ctl(hdw);
	return ret;
}