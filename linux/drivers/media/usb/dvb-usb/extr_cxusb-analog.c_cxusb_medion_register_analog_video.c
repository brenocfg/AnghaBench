#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_device {TYPE_1__* udev; struct cxusb_medion_dev* priv; } ;
struct cxusb_medion_vbuffer {int dummy; } ;
struct TYPE_10__ {int io_modes; int buf_struct_size; int min_buffers_needed; int /*<<< orphan*/ * lock; int /*<<< orphan*/  timestamp_flags; struct dvb_usb_device* drv_priv; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; int /*<<< orphan*/  type; } ;
struct cxusb_medion_dev {TYPE_6__ videoqueue; TYPE_2__* videodev; int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  v4l2dev; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lock; int /*<<< orphan*/  release; int /*<<< orphan*/  tvnorms; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/  vfl_dir; int /*<<< orphan*/  name; TYPE_6__* queue; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/ * fops; int /*<<< orphan*/  device_caps; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_STD_ALL ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int VB2_READ ; 
 int VB2_USERPTR ; 
 int /*<<< orphan*/  VFL_DIR_RX ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  cxdev_video_qops ; 
 int /*<<< orphan*/  cxusb_medion_videodev_release ; 
 int /*<<< orphan*/  cxusb_video_fops ; 
 int /*<<< orphan*/  cxusb_video_ioctl ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int vb2_queue_init (TYPE_6__*) ; 
 int /*<<< orphan*/  vb2_queue_release (TYPE_6__*) ; 
 int /*<<< orphan*/  vb2_vmalloc_memops ; 
 TYPE_2__* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release (TYPE_2__*) ; 
 int video_register_device (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_2__*,struct dvb_usb_device*) ; 
 int /*<<< orphan*/  videocaps ; 

__attribute__((used)) static int cxusb_medion_register_analog_video(struct dvb_usb_device *dvbdev)
{
	struct cxusb_medion_dev *cxdev = dvbdev->priv;
	int ret;

	cxdev->videoqueue.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	cxdev->videoqueue.io_modes = VB2_MMAP | VB2_USERPTR | VB2_READ |
		VB2_DMABUF;
	cxdev->videoqueue.ops = &cxdev_video_qops;
	cxdev->videoqueue.mem_ops = &vb2_vmalloc_memops;
	cxdev->videoqueue.drv_priv = dvbdev;
	cxdev->videoqueue.buf_struct_size =
		sizeof(struct cxusb_medion_vbuffer);
	cxdev->videoqueue.timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	cxdev->videoqueue.min_buffers_needed = 6;
	cxdev->videoqueue.lock = &cxdev->dev_lock;

	ret = vb2_queue_init(&cxdev->videoqueue);
	if (ret) {
		dev_err(&dvbdev->udev->dev,
			"video queue init failed, ret = %d\n", ret);
		return ret;
	}

	cxdev->videodev = video_device_alloc();
	if (!cxdev->videodev) {
		dev_err(&dvbdev->udev->dev, "video device alloc failed\n");
		ret = -ENOMEM;
		goto ret_qrelease;
	}

	cxdev->videodev->device_caps = videocaps;
	cxdev->videodev->fops = &cxusb_video_fops;
	cxdev->videodev->v4l2_dev = &cxdev->v4l2dev;
	cxdev->videodev->queue = &cxdev->videoqueue;
	strscpy(cxdev->videodev->name, "cxusb", sizeof(cxdev->videodev->name));
	cxdev->videodev->vfl_dir = VFL_DIR_RX;
	cxdev->videodev->ioctl_ops = &cxusb_video_ioctl;
	cxdev->videodev->tvnorms = V4L2_STD_ALL;
	cxdev->videodev->release = cxusb_medion_videodev_release;
	cxdev->videodev->lock = &cxdev->dev_lock;
	video_set_drvdata(cxdev->videodev, dvbdev);

	ret = video_register_device(cxdev->videodev, VFL_TYPE_GRABBER, -1);
	if (ret) {
		dev_err(&dvbdev->udev->dev,
			"video device register failed, ret = %d\n", ret);
		goto ret_vrelease;
	}

	return 0;

ret_vrelease:
	video_device_release(cxdev->videodev);

ret_qrelease:
	vb2_queue_release(&cxdev->videoqueue);

	return ret;
}