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
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct vpfe_device {size_t std_index; TYPE_1__ crop; int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_selection {scalar_t__ type; int target; TYPE_1__ r; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct vpfe_device* video_drvdata (struct file*) ; 
 TYPE_2__* vpfe_standards ; 

__attribute__((used)) static int vpfe_g_selection(struct file *file, void *priv,
			    struct v4l2_selection *sel)
{
	struct vpfe_device *vpfe_dev = video_drvdata(file);

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_g_selection\n");

	if (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	switch (sel->target) {
	case V4L2_SEL_TGT_CROP:
		sel->r = vpfe_dev->crop;
		break;
	case V4L2_SEL_TGT_CROP_DEFAULT:
	case V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.width = vpfe_standards[vpfe_dev->std_index].width;
		sel->r.height = vpfe_standards[vpfe_dev->std_index].height;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}