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
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_selection {scalar_t__ type; int target; TYPE_1__ r; } ;
struct flite_frame {TYPE_1__ rect; int /*<<< orphan*/  f_height; int /*<<< orphan*/  f_width; } ;
struct fimc_lite {struct flite_frame out_frame; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
#define  V4L2_SEL_TGT_COMPOSE 130 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 129 
#define  V4L2_SEL_TGT_COMPOSE_DEFAULT 128 
 struct fimc_lite* video_drvdata (struct file*) ; 

__attribute__((used)) static int fimc_lite_g_selection(struct file *file, void *fh,
				 struct v4l2_selection *sel)
{
	struct fimc_lite *fimc = video_drvdata(file);
	struct flite_frame *f = &fimc->out_frame;

	if (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	switch (sel->target) {
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
	case V4L2_SEL_TGT_COMPOSE_DEFAULT:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = f->f_width;
		sel->r.height = f->f_height;
		return 0;

	case V4L2_SEL_TGT_COMPOSE:
		sel->r = f->rect;
		return 0;
	}

	return -EINVAL;
}