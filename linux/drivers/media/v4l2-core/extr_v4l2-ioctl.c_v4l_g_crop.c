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
struct video_device {int /*<<< orphan*/  flags; } ;
struct v4l2_selection {scalar_t__ target; int /*<<< orphan*/  r; int /*<<< orphan*/  type; } ;
struct v4l2_ioctl_ops {int dummy; } ;
struct v4l2_crop {int /*<<< orphan*/  c; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FL_QUIRK_INVERTED_CROP ; 
 scalar_t__ V4L2_SEL_TGT_COMPOSE ; 
 scalar_t__ V4L2_SEL_TGT_CROP ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int v4l_g_selection (struct v4l2_ioctl_ops const*,struct file*,void*,struct v4l2_selection*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int v4l_g_crop(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
	struct video_device *vfd = video_devdata(file);
	struct v4l2_crop *p = arg;
	struct v4l2_selection s = {
		.type = p->type,
	};
	int ret;

	/* simulate capture crop using selection api */

	/* crop means compose for output devices */
	if (V4L2_TYPE_IS_OUTPUT(p->type))
		s.target = V4L2_SEL_TGT_COMPOSE;
	else
		s.target = V4L2_SEL_TGT_CROP;

	if (test_bit(V4L2_FL_QUIRK_INVERTED_CROP, &vfd->flags))
		s.target = s.target == V4L2_SEL_TGT_COMPOSE ?
			V4L2_SEL_TGT_CROP : V4L2_SEL_TGT_COMPOSE;

	ret = v4l_g_selection(ops, file, fh, &s);

	/* copying results to old structure on success */
	if (!ret)
		p->c = s.r;
	return ret;
}