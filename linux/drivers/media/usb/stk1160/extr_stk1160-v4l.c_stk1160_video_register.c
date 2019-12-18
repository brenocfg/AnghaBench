#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int device_caps; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * queue; } ;
struct stk1160 {int width; int height; TYPE_1__ vdev; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  norm; int /*<<< orphan*/ * fmt; int /*<<< orphan*/  v4l_lock; int /*<<< orphan*/  vb_vidq; } ;

/* Variables and functions */
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_STD_NTSC_M ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/ * format ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  stk1160_err (char*,int) ; 
 int /*<<< orphan*/  stk1160_set_std (struct stk1160*) ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ v4l_template ; 
 int /*<<< orphan*/  video ; 
 int /*<<< orphan*/  video_device_node_name (TYPE_1__*) ; 
 int video_register_device (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_1__*,struct stk1160*) ; 

int stk1160_video_register(struct stk1160 *dev)
{
	int rc;

	/* Initialize video_device with a template structure */
	dev->vdev = v4l_template;
	dev->vdev.queue = &dev->vb_vidq;

	/*
	 * Provide mutexes for v4l2 core and for videobuf2 queue.
	 * It will be used to protect *only* v4l2 ioctls.
	 */
	dev->vdev.lock = &dev->v4l_lock;

	/* This will be used to set video_device parent */
	dev->vdev.v4l2_dev = &dev->v4l2_dev;
	dev->vdev.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING |
				V4L2_CAP_READWRITE;

	/* NTSC is default */
	dev->norm = V4L2_STD_NTSC_M;
	dev->width = 720;
	dev->height = 480;

	/* set default format */
	dev->fmt = &format[0];
	stk1160_set_std(dev);

	v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_std,
			dev->norm);

	video_set_drvdata(&dev->vdev, dev);
	rc = video_register_device(&dev->vdev, VFL_TYPE_GRABBER, -1);
	if (rc < 0) {
		stk1160_err("video_register_device failed (%d)\n", rc);
		return rc;
	}

	v4l2_info(&dev->v4l2_dev, "V4L2 device registered as %s\n",
		  video_device_node_name(&dev->vdev));

	return 0;
}