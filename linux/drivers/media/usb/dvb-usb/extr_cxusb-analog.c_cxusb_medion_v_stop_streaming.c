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
struct vb2_queue {int dummy; } ;
struct dvb_usb_device {TYPE_1__* udev; struct cxusb_medion_dev* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  buf; } ;
struct cxusb_medion_dev {int stop_streaming; TYPE_3__ auxbuf; TYPE_2__* videodev; int /*<<< orphan*/  urbwork; scalar_t__* streamurbs; int /*<<< orphan*/  cx25840; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_STREAMING_OFF ; 
 unsigned int CXUSB_VIDEO_URBS ; 
 int /*<<< orphan*/  OPS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cxusb_ctrl_msg (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxusb_medion_return_buffers (struct cxusb_medion_dev*,int) ; 
 int /*<<< orphan*/  cxusb_medion_urbs_free (struct cxusb_medion_dev*) ; 
 int /*<<< orphan*/  cxusb_vprintk (struct dvb_usb_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dvb_usb_device* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static void cxusb_medion_v_stop_streaming(struct vb2_queue *q)
{
	struct dvb_usb_device *dvbdev = vb2_get_drv_priv(q);
	struct cxusb_medion_dev *cxdev = dvbdev->priv;
	int ret;
	unsigned int i;

	cxusb_vprintk(dvbdev, OPS, "should stop streaming\n");

	if (WARN_ON(cxdev->stop_streaming))
		return;

	cxdev->stop_streaming = true;

	cxusb_ctrl_msg(dvbdev, CMD_STREAMING_OFF, NULL, 0, NULL, 0);

	ret = v4l2_subdev_call(cxdev->cx25840, video, s_stream, 0);
	if (ret != 0)
		dev_err(&dvbdev->udev->dev, "unable to stop stream (%d)\n",
			ret);

	/* let URB completion run */
	mutex_unlock(cxdev->videodev->lock);

	for (i = 0; i < CXUSB_VIDEO_URBS; i++)
		if (cxdev->streamurbs[i])
			usb_kill_urb(cxdev->streamurbs[i]);

	flush_work(&cxdev->urbwork);

	mutex_lock(cxdev->videodev->lock);

	/* free transfer buffer and URB */
	vfree(cxdev->auxbuf.buf);

	cxusb_medion_urbs_free(cxdev);

	cxusb_medion_return_buffers(cxdev, false);

	cxdev->stop_streaming = false;
}