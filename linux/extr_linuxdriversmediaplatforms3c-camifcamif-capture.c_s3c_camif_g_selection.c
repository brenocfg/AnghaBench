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
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_selection {scalar_t__ type; int target; TYPE_2__ r; } ;
struct file {int dummy; } ;
struct TYPE_3__ {TYPE_2__ rect; int /*<<< orphan*/  f_height; int /*<<< orphan*/  f_width; } ;
struct camif_vp {TYPE_1__ out_frame; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
#define  V4L2_SEL_TGT_COMPOSE 130 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 129 
#define  V4L2_SEL_TGT_COMPOSE_DEFAULT 128 
 struct camif_vp* video_drvdata (struct file*) ; 

__attribute__((used)) static int s3c_camif_g_selection(struct file *file, void *priv,
				 struct v4l2_selection *sel)
{
	struct camif_vp *vp = video_drvdata(file);

	if (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	switch (sel->target) {
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
	case V4L2_SEL_TGT_COMPOSE_DEFAULT:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = vp->out_frame.f_width;
		sel->r.height = vp->out_frame.f_height;
		return 0;

	case V4L2_SEL_TGT_COMPOSE:
		sel->r = vp->out_frame.rect;
		return 0;
	}

	return -EINVAL;
}