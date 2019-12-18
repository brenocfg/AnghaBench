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
struct v4l2_fract {int dummy; } ;
struct v4l2_cropcap {int type; struct v4l2_fract pixelaspect; } ;
struct TYPE_4__ {TYPE_1__* mc_head; } ;
struct pvr2_v4l2_fh {TYPE_2__ channel; } ;
struct pvr2_hdw {int dummy; } ;
struct file {struct pvr2_v4l2_fh* private_data; } ;
struct TYPE_3__ {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int pvr2_hdw_get_cropcap (struct pvr2_hdw*,struct v4l2_cropcap*) ; 

__attribute__((used)) static int pvr2_g_pixelaspect(struct file *file, void *priv,
			      int type, struct v4l2_fract *f)
{
	struct pvr2_v4l2_fh *fh = file->private_data;
	struct pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	struct v4l2_cropcap cap = { .type = type };
	int ret;

	if (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;
	ret = pvr2_hdw_get_cropcap(hdw, &cap);
	if (!ret)
		*f = cap.pixelaspect;
	return ret;
}