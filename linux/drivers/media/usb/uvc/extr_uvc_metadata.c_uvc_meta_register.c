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
struct video_device {int /*<<< orphan*/ * queue; } ;
struct uvc_video_queue {int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  format; struct uvc_video_queue queue; struct video_device vdev; } ;
struct uvc_streaming {TYPE_1__ meta; struct uvc_device* dev; } ;
struct uvc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_TYPE_META_CAPTURE ; 
 int /*<<< orphan*/  V4L2_META_FMT_UVC ; 
 int /*<<< orphan*/  uvc_meta_fops ; 
 int /*<<< orphan*/  uvc_meta_ioctl_ops ; 
 int uvc_register_video_device (struct uvc_device*,struct uvc_streaming*,struct video_device*,struct uvc_video_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int uvc_meta_register(struct uvc_streaming *stream)
{
	struct uvc_device *dev = stream->dev;
	struct video_device *vdev = &stream->meta.vdev;
	struct uvc_video_queue *queue = &stream->meta.queue;

	stream->meta.format = V4L2_META_FMT_UVC;

	/*
	 * The video interface queue uses manual locking and thus does not set
	 * the queue pointer. Set it manually here.
	 */
	vdev->queue = &queue->queue;

	return uvc_register_video_device(dev, stream, vdev, queue,
					 V4L2_BUF_TYPE_META_CAPTURE,
					 &uvc_meta_fops, &uvc_meta_ioctl_ops);
}