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
struct v4l2_selection {scalar_t__ type; int target; int /*<<< orphan*/  r; } ;
struct saa7134_dev {int /*<<< orphan*/  crop_bounds; int /*<<< orphan*/  crop_defrect; int /*<<< orphan*/  crop_current; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OVERLAY ; 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 struct saa7134_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int saa7134_g_selection(struct file *file, void *f, struct v4l2_selection *sel)
{
	struct saa7134_dev *dev = video_drvdata(file);

	if (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    sel->type != V4L2_BUF_TYPE_VIDEO_OVERLAY)
		return -EINVAL;

	switch (sel->target) {
	case V4L2_SEL_TGT_CROP:
		sel->r = dev->crop_current;
		break;
	case V4L2_SEL_TGT_CROP_DEFAULT:
		sel->r = dev->crop_defrect;
		break;
	case V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r  = dev->crop_bounds;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}