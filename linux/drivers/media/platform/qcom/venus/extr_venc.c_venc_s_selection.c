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
struct venus_inst {int /*<<< orphan*/  out_height; int /*<<< orphan*/  out_width; } ;
struct TYPE_2__ {int /*<<< orphan*/  left; int /*<<< orphan*/  top; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_selection {scalar_t__ type; int target; TYPE_1__ r; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
#define  V4L2_SEL_TGT_CROP 128 
 struct venus_inst* to_inst (struct file*) ; 

__attribute__((used)) static int
venc_s_selection(struct file *file, void *fh, struct v4l2_selection *s)
{
	struct venus_inst *inst = to_inst(file);

	if (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		return -EINVAL;

	switch (s->target) {
	case V4L2_SEL_TGT_CROP:
		if (s->r.width != inst->out_width ||
		    s->r.height != inst->out_height ||
		    s->r.top != 0 || s->r.left != 0)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}