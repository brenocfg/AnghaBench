#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct vpfe_device {scalar_t__ std_index; TYPE_1__ crop; } ;
struct v4l2_selection {scalar_t__ type; int target; TYPE_1__ r; } ;
struct file {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 struct vpfe_device* video_drvdata (struct file*) ; 
 TYPE_2__* vpfe_standards ; 

__attribute__((used)) static int
vpfe_g_selection(struct file *file, void *fh, struct v4l2_selection *s)
{
	struct vpfe_device *vpfe = video_drvdata(file);

	if (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	    vpfe->std_index >= ARRAY_SIZE(vpfe_standards))
		return -EINVAL;

	switch (s->target) {
	case V4L2_SEL_TGT_CROP_BOUNDS:
	case V4L2_SEL_TGT_CROP_DEFAULT:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = vpfe_standards[vpfe->std_index].width;
		s->r.height = vpfe_standards[vpfe->std_index].height;
		break;

	case V4L2_SEL_TGT_CROP:
		s->r = vpfe->crop;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}