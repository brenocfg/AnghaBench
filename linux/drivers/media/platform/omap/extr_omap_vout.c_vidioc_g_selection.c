#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int width; int height; } ;
struct v4l2_selection {scalar_t__ type; int target; TYPE_1__ r; } ;
struct v4l2_pix_format {int width; int height; } ;
struct omap_vout_device {int /*<<< orphan*/  fbuf; struct v4l2_pix_format pix; TYPE_1__ crop; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 int /*<<< orphan*/  omap_vout_default_crop (struct v4l2_pix_format*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct omap_vout_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_selection(struct file *file, void *fh, struct v4l2_selection *sel)
{
	struct omap_vout_device *vout = video_drvdata(file);
	struct v4l2_pix_format *pix = &vout->pix;

	if (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		return -EINVAL;

	switch (sel->target) {
	case V4L2_SEL_TGT_CROP:
		sel->r = vout->crop;
		break;
	case V4L2_SEL_TGT_CROP_DEFAULT:
		omap_vout_default_crop(&vout->pix, &vout->fbuf, &sel->r);
		break;
	case V4L2_SEL_TGT_CROP_BOUNDS:
		/* Width and height are always even */
		sel->r.width = pix->width & ~1;
		sel->r.height = pix->height & ~1;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}