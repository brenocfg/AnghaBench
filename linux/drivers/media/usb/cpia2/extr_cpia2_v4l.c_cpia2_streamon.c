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
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  stream_mode; } ;
struct TYPE_4__ {TYPE_1__ camera_state; } ;
struct camera_data {int /*<<< orphan*/  usb_alt; TYPE_2__ params; int /*<<< orphan*/  streaming; int /*<<< orphan*/  mmapped; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int cpia2_usb_stream_start (struct camera_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_grab (int /*<<< orphan*/ ,int) ; 
 struct camera_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int cpia2_streamon(struct file *file, void *fh, enum v4l2_buf_type type)
{
	struct camera_data *cam = video_drvdata(file);
	int ret = -EINVAL;

	DBG("VIDIOC_STREAMON, streaming=%d\n", cam->streaming);
	if (!cam->mmapped || type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	if (!cam->streaming) {
		ret = cpia2_usb_stream_start(cam,
				cam->params.camera_state.stream_mode);
		if (!ret)
			v4l2_ctrl_grab(cam->usb_alt, true);
	}
	return ret;
}