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
struct v4l2_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  device_caps; struct v4l2_device* v4l2_dev; } ;
struct iss_video {scalar_t__ type; TYPE_1__* iss; TYPE_2__ video; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_CAP_STREAMING ; 
 int /*<<< orphan*/  V4L2_CAP_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_CAP_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int video_register_device (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int omap4iss_video_register(struct iss_video *video, struct v4l2_device *vdev)
{
	int ret;

	video->video.v4l2_dev = vdev;
	if (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		video->video.device_caps = V4L2_CAP_VIDEO_CAPTURE;
	else
		video->video.device_caps = V4L2_CAP_VIDEO_OUTPUT;
	video->video.device_caps |= V4L2_CAP_STREAMING;

	ret = video_register_device(&video->video, VFL_TYPE_GRABBER, -1);
	if (ret < 0)
		dev_err(video->iss->dev,
			"could not register video device (%d)\n", ret);

	return ret;
}