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
struct TYPE_7__ {int height; int width; } ;
struct TYPE_8__ {TYPE_3__ pix; } ;
struct v4l2_format {TYPE_4__ fmt; } ;
struct TYPE_6__ {TYPE_1__* mc_head; } ;
struct pvr2_v4l2_fh {TYPE_2__ channel; } ;
struct pvr2_hdw {int dummy; } ;
struct pvr2_ctrl {int dummy; } ;
struct file {struct pvr2_v4l2_fh* private_data; } ;
struct TYPE_5__ {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_CID_HRES ; 
 int /*<<< orphan*/  PVR2_CID_VRES ; 
 size_t PVR_FORMAT_PIX ; 
 int /*<<< orphan*/  memcpy (struct v4l2_format*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pvr2_ctrl_get_def (struct pvr2_ctrl*,int*) ; 
 int pvr2_ctrl_get_max (struct pvr2_ctrl*) ; 
 int pvr2_ctrl_get_min (struct pvr2_ctrl*) ; 
 struct pvr2_ctrl* pvr2_hdw_get_ctrl_by_id (struct pvr2_hdw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pvr_format ; 

__attribute__((used)) static int pvr2_try_fmt_vid_cap(struct file *file, void *priv, struct v4l2_format *vf)
{
	struct pvr2_v4l2_fh *fh = file->private_data;
	struct pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	int lmin, lmax, ldef;
	struct pvr2_ctrl *hcp, *vcp;
	int h = vf->fmt.pix.height;
	int w = vf->fmt.pix.width;

	hcp = pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_HRES);
	vcp = pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_VRES);

	lmin = pvr2_ctrl_get_min(hcp);
	lmax = pvr2_ctrl_get_max(hcp);
	pvr2_ctrl_get_def(hcp, &ldef);
	if (w == -1)
		w = ldef;
	else if (w < lmin)
		w = lmin;
	else if (w > lmax)
		w = lmax;
	lmin = pvr2_ctrl_get_min(vcp);
	lmax = pvr2_ctrl_get_max(vcp);
	pvr2_ctrl_get_def(vcp, &ldef);
	if (h == -1)
		h = ldef;
	else if (h < lmin)
		h = lmin;
	else if (h > lmax)
		h = lmax;

	memcpy(vf, &pvr_format[PVR_FORMAT_PIX],
			sizeof(struct v4l2_format));
	vf->fmt.pix.width = w;
	vf->fmt.pix.height = h;
	return 0;
}