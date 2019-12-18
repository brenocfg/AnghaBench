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
struct TYPE_3__ {int width; int height; int /*<<< orphan*/  left; int /*<<< orphan*/  top; } ;
struct v4l2_selection {scalar_t__ type; int target; TYPE_1__ r; } ;
struct file {int dummy; } ;
struct cx18 {int /*<<< orphan*/  is_50hz; } ;
struct TYPE_4__ {struct cx18* cx; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 TYPE_2__* fh2id (void*) ; 

__attribute__((used)) static int cx18_g_selection(struct file *file, void *fh,
			    struct v4l2_selection *sel)
{
	struct cx18 *cx = fh2id(fh)->cx;

	if (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;
	switch (sel->target) {
	case V4L2_SEL_TGT_CROP_BOUNDS:
	case V4L2_SEL_TGT_CROP_DEFAULT:
		sel->r.top = sel->r.left = 0;
		sel->r.width = 720;
		sel->r.height = cx->is_50hz ? 576 : 480;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}