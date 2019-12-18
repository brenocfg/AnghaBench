#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ioctl_ops {int (* vidioc_create_bufs ) (struct file*,void*,struct v4l2_create_buffers*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  priv; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_2__ fmt; } ;
struct v4l2_create_buffers {TYPE_3__ format; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_AFTER_FIELD (struct v4l2_create_buffers*,int /*<<< orphan*/ ) ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_PRIV_MAGIC ; 
 int /*<<< orphan*/  capabilities ; 
 int check_fmt (struct file*,scalar_t__) ; 
 int stub1 (struct file*,void*,struct v4l2_create_buffers*) ; 
 int /*<<< orphan*/  v4l_sanitize_format (TYPE_3__*) ; 

__attribute__((used)) static int v4l_create_bufs(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
	struct v4l2_create_buffers *create = arg;
	int ret = check_fmt(file, create->format.type);

	if (ret)
		return ret;

	CLEAR_AFTER_FIELD(create, capabilities);

	v4l_sanitize_format(&create->format);

	ret = ops->vidioc_create_bufs(file, fh, create);

	if (create->format.type == V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	    create->format.type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		create->format.fmt.pix.priv = V4L2_PIX_FMT_PRIV_MAGIC;

	return ret;
}