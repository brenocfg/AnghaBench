#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_6__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct TYPE_8__ {TYPE_3__* mc_head; } ;
struct pvr2_v4l2_fh {TYPE_4__ channel; } ;
struct pvr2_hdw {int dummy; } ;
struct pvr2_ctrl {int dummy; } ;
struct file {struct pvr2_v4l2_fh* private_data; } ;
struct TYPE_7__ {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_CID_HRES ; 
 int /*<<< orphan*/  PVR2_CID_VRES ; 
 int /*<<< orphan*/  pvr2_ctrl_set_value (struct pvr2_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_hdw_commit_ctl (struct pvr2_hdw*) ; 
 struct pvr2_ctrl* pvr2_hdw_get_ctrl_by_id (struct pvr2_hdw*,int /*<<< orphan*/ ) ; 
 int pvr2_try_fmt_vid_cap (struct file*,struct pvr2_v4l2_fh*,struct v4l2_format*) ; 

__attribute__((used)) static int pvr2_s_fmt_vid_cap(struct file *file, void *priv, struct v4l2_format *vf)
{
	struct pvr2_v4l2_fh *fh = file->private_data;
	struct pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	struct pvr2_ctrl *hcp, *vcp;
	int ret = pvr2_try_fmt_vid_cap(file, fh, vf);

	if (ret)
		return ret;
	hcp = pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_HRES);
	vcp = pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_VRES);
	pvr2_ctrl_set_value(hcp, vf->fmt.pix.width);
	pvr2_ctrl_set_value(vcp, vf->fmt.pix.height);
	pvr2_hdw_commit_ctl(hdw);
	return 0;
}