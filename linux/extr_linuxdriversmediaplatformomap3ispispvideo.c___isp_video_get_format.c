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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev_format {int /*<<< orphan*/  format; int /*<<< orphan*/  which; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {TYPE_1__ fmt; int /*<<< orphan*/  type; } ;
struct isp_video {int /*<<< orphan*/  type; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  get_fmt ; 
 int isp_video_mbus_to_pix (struct isp_video*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct v4l2_subdev* isp_video_remote_subdev (struct isp_video*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 

__attribute__((used)) static int
__isp_video_get_format(struct isp_video *video, struct v4l2_format *format)
{
	struct v4l2_subdev_format fmt;
	struct v4l2_subdev *subdev;
	u32 pad;
	int ret;

	subdev = isp_video_remote_subdev(video, &pad);
	if (subdev == NULL)
		return -EINVAL;

	fmt.pad = pad;
	fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;

	mutex_lock(&video->mutex);
	ret = v4l2_subdev_call(subdev, pad, get_fmt, NULL, &fmt);
	mutex_unlock(&video->mutex);

	if (ret)
		return ret;

	format->type = video->type;
	return isp_video_mbus_to_pix(video, &fmt.format, &format->fmt.pix);
}