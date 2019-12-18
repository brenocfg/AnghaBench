#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_device {TYPE_1__* udev; struct cxusb_medion_dev* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  release; } ;
struct cxusb_medion_dev {int width; int height; int /*<<< orphan*/  v4l2_release; TYPE_2__ v4l2dev; int /*<<< orphan*/  videodev; int /*<<< orphan*/  buflist; int /*<<< orphan*/  urbwork; int /*<<< orphan*/  dev_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cxusb_medion_register_analog_radio (struct dvb_usb_device*) ; 
 int cxusb_medion_register_analog_subdevs (struct dvb_usb_device*) ; 
 int cxusb_medion_register_analog_video (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  cxusb_medion_v4l2_release ; 
 int /*<<< orphan*/  cxusb_medion_v_complete_work ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_put (TYPE_2__*) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int cxusb_medion_register_analog(struct dvb_usb_device *dvbdev)
{
	struct cxusb_medion_dev *cxdev = dvbdev->priv;
	int ret;

	mutex_init(&cxdev->dev_lock);

	init_completion(&cxdev->v4l2_release);

	cxdev->v4l2dev.release = cxusb_medion_v4l2_release;

	ret = v4l2_device_register(&dvbdev->udev->dev, &cxdev->v4l2dev);
	if (ret != 0) {
		dev_err(&dvbdev->udev->dev,
			"V4L2 device registration failed, ret = %d\n", ret);
		mutex_destroy(&cxdev->dev_lock);
		return ret;
	}

	ret = cxusb_medion_register_analog_subdevs(dvbdev);
	if (ret)
		goto ret_unregister;

	INIT_WORK(&cxdev->urbwork, cxusb_medion_v_complete_work);
	INIT_LIST_HEAD(&cxdev->buflist);

	cxdev->width = 320;
	cxdev->height = 240;

	ret = cxusb_medion_register_analog_video(dvbdev);
	if (ret)
		goto ret_unregister;

	ret = cxusb_medion_register_analog_radio(dvbdev);
	if (ret)
		goto ret_vunreg;

	return 0;

ret_vunreg:
	video_unregister_device(cxdev->videodev);

ret_unregister:
	v4l2_device_put(&cxdev->v4l2dev);
	wait_for_completion(&cxdev->v4l2_release);

	return ret;
}