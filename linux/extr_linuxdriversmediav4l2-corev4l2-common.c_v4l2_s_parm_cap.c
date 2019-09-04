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
struct video_device {int device_caps; } ;
struct v4l2_subdev_frame_interval {int /*<<< orphan*/  interval; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_3__ {int readbuffers; int /*<<< orphan*/  timeperframe; int /*<<< orphan*/  capability; } ;
struct TYPE_4__ {TYPE_1__ capture; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_2__ parm; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int V4L2_CAP_READWRITE ; 
 int /*<<< orphan*/  V4L2_CAP_TIMEPERFRAME ; 
 int /*<<< orphan*/  g_frame_interval ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_frame_interval ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_subdev_frame_interval*) ; 
 scalar_t__ v4l2_subdev_has_op (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 

int v4l2_s_parm_cap(struct video_device *vdev,
		    struct v4l2_subdev *sd, struct v4l2_streamparm *a)
{
	struct v4l2_subdev_frame_interval ival = {
		.interval = a->parm.capture.timeperframe
	};
	int ret;

	if (a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		return -EINVAL;

	memset(&a->parm, 0, sizeof(a->parm));
	if (vdev->device_caps & V4L2_CAP_READWRITE)
		a->parm.capture.readbuffers = 2;
	else
		a->parm.capture.readbuffers = 0;

	if (v4l2_subdev_has_op(sd, video, g_frame_interval))
		a->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	ret = v4l2_subdev_call(sd, video, s_frame_interval, &ival);
	if (!ret)
		a->parm.capture.timeperframe = ival.interval;
	return ret;
}