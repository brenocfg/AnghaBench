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
struct TYPE_5__ {int width; int height; } ;
struct TYPE_6__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct TYPE_7__ {TYPE_4__* mc_head; } ;
struct pvr2_v4l2_fh {TYPE_3__ channel; } ;
struct pvr2_hdw {int dummy; } ;
struct file {struct pvr2_v4l2_fh* private_data; } ;
struct TYPE_8__ {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_CID_HRES ; 
 int /*<<< orphan*/  PVR2_CID_VRES ; 
 size_t PVR_FORMAT_PIX ; 
 int /*<<< orphan*/  memcpy (struct v4l2_format*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pvr2_ctrl_get_value (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pvr2_hdw_get_ctrl_by_id (struct pvr2_hdw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pvr_format ; 

__attribute__((used)) static int pvr2_g_fmt_vid_cap(struct file *file, void *priv, struct v4l2_format *vf)
{
	struct pvr2_v4l2_fh *fh = file->private_data;
	struct pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	int val;

	memcpy(vf, &pvr_format[PVR_FORMAT_PIX], sizeof(struct v4l2_format));
	val = 0;
	pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_HRES),
			&val);
	vf->fmt.pix.width = val;
	val = 0;
	pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_VRES),
			&val);
	vf->fmt.pix.height = val;
	return 0;
}