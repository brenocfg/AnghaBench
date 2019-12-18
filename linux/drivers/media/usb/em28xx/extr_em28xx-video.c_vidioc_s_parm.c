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
struct v4l2_subdev_frame_interval {int /*<<< orphan*/  interval; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/  timeperframe; int /*<<< orphan*/  capability; int /*<<< orphan*/  readbuffers; } ;
struct TYPE_6__ {TYPE_2__ capture; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_3__ parm; } ;
struct file {int dummy; } ;
struct em28xx {TYPE_1__* v4l2; int /*<<< orphan*/  is_webcam; } ;
struct TYPE_4__ {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EM28XX_MIN_BUF ; 
 int ENOTTY ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int /*<<< orphan*/  V4L2_CAP_TIMEPERFRAME ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_frame_interval ; 
 int v4l2_device_call_until_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_subdev_frame_interval*) ; 
 int /*<<< orphan*/  video ; 
 struct em28xx* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_parm(struct file *file, void *priv,
			 struct v4l2_streamparm *p)
{
	struct em28xx *dev = video_drvdata(file);
	struct v4l2_subdev_frame_interval ival = {
		0,
		p->parm.capture.timeperframe
	};
	int rc = 0;

	if (!dev->is_webcam)
		return -ENOTTY;

	if (p->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    p->type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		return -EINVAL;

	memset(&p->parm, 0, sizeof(p->parm));
	p->parm.capture.readbuffers = EM28XX_MIN_BUF;
	p->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	rc = v4l2_device_call_until_err(&dev->v4l2->v4l2_dev, 0,
					video, s_frame_interval, &ival);
	if (!rc)
		p->parm.capture.timeperframe = ival.interval;
	return rc;
}