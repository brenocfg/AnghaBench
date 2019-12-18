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
union v4l2_ctrl_ptr {int /*<<< orphan*/ * p_s32; int /*<<< orphan*/ * p_s64; } ;
struct video_device {int dummy; } ;
struct v4l2_ext_controls {unsigned int error_idx; unsigned int count; TYPE_2__* controls; } ;
struct v4l2_ctrl_helper {TYPE_1__* ref; } ;
struct v4l2_ctrl {int flags; scalar_t__ type; scalar_t__ is_ptr; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  value64; } ;
struct TYPE_3__ {struct v4l2_ctrl* ctrl; } ;

/* Variables and functions */
 int EACCES ; 
 int EBUSY ; 
 int V4L2_CTRL_FLAG_GRABBED ; 
 int V4L2_CTRL_FLAG_READ_ONLY ; 
 scalar_t__ V4L2_CTRL_TYPE_INTEGER64 ; 
 int /*<<< orphan*/  dprintk (struct video_device*,char*,int /*<<< orphan*/ ) ; 
 int validate_new (struct v4l2_ctrl*,union v4l2_ctrl_ptr) ; 

__attribute__((used)) static int validate_ctrls(struct v4l2_ext_controls *cs,
			  struct v4l2_ctrl_helper *helpers,
			  struct video_device *vdev,
			  bool set)
{
	unsigned i;
	int ret = 0;

	cs->error_idx = cs->count;
	for (i = 0; i < cs->count; i++) {
		struct v4l2_ctrl *ctrl = helpers[i].ref->ctrl;
		union v4l2_ctrl_ptr p_new;

		cs->error_idx = i;

		if (ctrl->flags & V4L2_CTRL_FLAG_READ_ONLY) {
			dprintk(vdev,
				"control id 0x%x is read-only\n",
				ctrl->id);
			return -EACCES;
		}
		/* This test is also done in try_set_control_cluster() which
		   is called in atomic context, so that has the final say,
		   but it makes sense to do an up-front check as well. Once
		   an error occurs in try_set_control_cluster() some other
		   controls may have been set already and we want to do a
		   best-effort to avoid that. */
		if (set && (ctrl->flags & V4L2_CTRL_FLAG_GRABBED)) {
			dprintk(vdev,
				"control id 0x%x is grabbed, cannot set\n",
				ctrl->id);
			return -EBUSY;
		}
		/*
		 * Skip validation for now if the payload needs to be copied
		 * from userspace into kernelspace. We'll validate those later.
		 */
		if (ctrl->is_ptr)
			continue;
		if (ctrl->type == V4L2_CTRL_TYPE_INTEGER64)
			p_new.p_s64 = &cs->controls[i].value64;
		else
			p_new.p_s32 = &cs->controls[i].value;
		ret = validate_new(ctrl, p_new);
		if (ret)
			return ret;
	}
	return 0;
}