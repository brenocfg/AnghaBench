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
struct v4l2_subdev_frame_interval {int /*<<< orphan*/  interval; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/  timeperframe; int /*<<< orphan*/  capability; int /*<<< orphan*/  readbuffers; } ;
struct TYPE_4__ {TYPE_1__ capture; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_2__ parm; } ;
struct file {int dummy; } ;
struct em28xx_v4l2 {int /*<<< orphan*/  norm; int /*<<< orphan*/  v4l2_dev; } ;
struct em28xx {scalar_t__ is_webcam; struct em28xx_v4l2* v4l2; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EM28XX_MIN_BUF ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int /*<<< orphan*/  V4L2_CAP_TIMEPERFRAME ; 
 int /*<<< orphan*/  g_frame_interval ; 
 int v4l2_device_call_until_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_subdev_frame_interval*) ; 
 int /*<<< orphan*/  v4l2_video_std_frame_period (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video ; 
 struct em28xx* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_parm(struct file *file, void *priv,
			 struct v4l2_streamparm *p)
{
	struct v4l2_subdev_frame_interval ival = { 0 };
	struct em28xx      *dev  = video_drvdata(file);
	struct em28xx_v4l2 *v4l2 = dev->v4l2;
	int rc = 0;

	if (p->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    p->type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		return -EINVAL;

	p->parm.capture.readbuffers = EM28XX_MIN_BUF;
	p->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	if (dev->is_webcam) {
		rc = v4l2_device_call_until_err(&v4l2->v4l2_dev, 0,
						video, g_frame_interval, &ival);
		if (!rc)
			p->parm.capture.timeperframe = ival.interval;
	} else {
		v4l2_video_std_frame_period(v4l2->norm,
					    &p->parm.capture.timeperframe);
	}

	return rc;
}