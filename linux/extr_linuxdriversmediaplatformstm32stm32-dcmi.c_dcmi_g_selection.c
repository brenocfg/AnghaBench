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
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  left; int /*<<< orphan*/  top; } ;
struct v4l2_selection {scalar_t__ type; int target; TYPE_1__ r; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_7__ {TYPE_2__ pix; } ;
struct TYPE_8__ {TYPE_3__ fmt; } ;
struct stm32_dcmi {TYPE_4__ fmt; TYPE_1__ crop; int /*<<< orphan*/  do_crop; TYPE_1__ sd_bounds; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 struct stm32_dcmi* video_drvdata (struct file*) ; 

__attribute__((used)) static int dcmi_g_selection(struct file *file, void *fh,
			    struct v4l2_selection *s)
{
	struct stm32_dcmi *dcmi = video_drvdata(file);

	if (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	switch (s->target) {
	case V4L2_SEL_TGT_CROP_DEFAULT:
	case V4L2_SEL_TGT_CROP_BOUNDS:
		s->r = dcmi->sd_bounds;
		return 0;
	case V4L2_SEL_TGT_CROP:
		if (dcmi->do_crop) {
			s->r = dcmi->crop;
		} else {
			s->r.top = 0;
			s->r.left = 0;
			s->r.width = dcmi->fmt.fmt.pix.width;
			s->r.height = dcmi->fmt.fmt.pix.height;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}