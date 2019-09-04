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
struct v4l2_selection {int /*<<< orphan*/  r; int /*<<< orphan*/  target; int /*<<< orphan*/  type; } ;
struct v4l2_ioctl_ops {int (* vidioc_g_crop ) (struct file*,void*,struct v4l2_crop*) ;} ;
struct v4l2_crop {int /*<<< orphan*/  c; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_SEL_TGT_COMPOSE_ACTIVE ; 
 int /*<<< orphan*/  V4L2_SEL_TGT_CROP_ACTIVE ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 int stub1 (struct file*,void*,struct v4l2_crop*) ; 
 int v4l_g_selection (struct v4l2_ioctl_ops const*,struct file*,void*,struct v4l2_selection*) ; 

__attribute__((used)) static int v4l_g_crop(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
	struct v4l2_crop *p = arg;
	struct v4l2_selection s = {
		.type = p->type,
	};
	int ret;

	if (ops->vidioc_g_crop)
		return ops->vidioc_g_crop(file, fh, p);
	/* simulate capture crop using selection api */

	/* crop means compose for output devices */
	if (V4L2_TYPE_IS_OUTPUT(p->type))
		s.target = V4L2_SEL_TGT_COMPOSE_ACTIVE;
	else
		s.target = V4L2_SEL_TGT_CROP_ACTIVE;

	ret = v4l_g_selection(ops, file, fh, &s);

	/* copying results to old structure on success */
	if (!ret)
		p->c = s.r;
	return ret;
}