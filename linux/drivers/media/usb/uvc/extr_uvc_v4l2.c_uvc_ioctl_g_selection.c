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
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct v4l2_selection {scalar_t__ type; int target; TYPE_1__ r; } ;
struct uvc_streaming {scalar_t__ type; int /*<<< orphan*/  mutex; TYPE_2__* cur_frame; } ;
struct uvc_fh {struct uvc_streaming* stream; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  wHeight; int /*<<< orphan*/  wWidth; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 131 
#define  V4L2_SEL_TGT_COMPOSE_DEFAULT 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uvc_ioctl_g_selection(struct file *file, void *fh,
				 struct v4l2_selection *sel)
{
	struct uvc_fh *handle = fh;
	struct uvc_streaming *stream = handle->stream;

	if (sel->type != stream->type)
		return -EINVAL;

	switch (sel->target) {
	case V4L2_SEL_TGT_CROP_DEFAULT:
	case V4L2_SEL_TGT_CROP_BOUNDS:
		if (stream->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
			return -EINVAL;
		break;
	case V4L2_SEL_TGT_COMPOSE_DEFAULT:
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
		if (stream->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	sel->r.left = 0;
	sel->r.top = 0;
	mutex_lock(&stream->mutex);
	sel->r.width = stream->cur_frame->wWidth;
	sel->r.height = stream->cur_frame->wHeight;
	mutex_unlock(&stream->mutex);

	return 0;
}