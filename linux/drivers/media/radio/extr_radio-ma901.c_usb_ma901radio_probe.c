#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {scalar_t__ manufacturer; scalar_t__ product; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; int /*<<< orphan*/  release; TYPE_5__* ctrl_handler; } ;
struct TYPE_11__ {int error; } ;
struct TYPE_9__ {int device_caps; int /*<<< orphan*/ * lock; int /*<<< orphan*/  release; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; TYPE_3__* v4l2_dev; int /*<<< orphan*/  name; } ;
struct ma901radio_device {double curfreq; struct ma901radio_device* buffer; TYPE_3__ v4l2_dev; TYPE_5__ hdl; TYPE_1__ vdev; struct usb_interface* intf; void* usbdev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_LENGTH ; 
 int ENODEV ; 
 int ENOMEM ; 
 double FREQ_MUL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MA901_VOLUME_MAX ; 
 int /*<<< orphan*/  MA901_VOLUME_MIN ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_TUNER ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_VOLUME ; 
 int /*<<< orphan*/  VFL_TYPE_RADIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct ma901radio_device*) ; 
 struct ma901radio_device* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ma901radio_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radio_nr ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_ma901radio_ctrl_ops ; 
 int /*<<< orphan*/  usb_ma901radio_fops ; 
 int /*<<< orphan*/  usb_ma901radio_ioctl_ops ; 
 int /*<<< orphan*/  usb_ma901radio_release ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_5__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_5__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_3__*) ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int video_register_device (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_1__*,struct ma901radio_device*) ; 

__attribute__((used)) static int usb_ma901radio_probe(struct usb_interface *intf,
				const struct usb_device_id *id)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	struct ma901radio_device *radio;
	int retval = 0;

	/* Masterkit MA901 usb radio has the same USB ID as many others
	 * Atmel V-USB devices. Let's make additional checks to be sure
	 * that this is our device.
	 */

	if (dev->product && dev->manufacturer &&
		(strncmp(dev->product, "MA901", 5) != 0
		|| strncmp(dev->manufacturer, "www.masterkit.ru", 16) != 0))
		return -ENODEV;

	radio = kzalloc(sizeof(struct ma901radio_device), GFP_KERNEL);
	if (!radio) {
		dev_err(&intf->dev, "kzalloc for ma901radio_device failed\n");
		retval = -ENOMEM;
		goto err;
	}

	radio->buffer = kmalloc(BUFFER_LENGTH, GFP_KERNEL);
	if (!radio->buffer) {
		dev_err(&intf->dev, "kmalloc for radio->buffer failed\n");
		retval = -ENOMEM;
		goto err_nobuf;
	}

	retval = v4l2_device_register(&intf->dev, &radio->v4l2_dev);
	if (retval < 0) {
		dev_err(&intf->dev, "couldn't register v4l2_device\n");
		goto err_v4l2;
	}

	v4l2_ctrl_handler_init(&radio->hdl, 1);

	/* TODO:It looks like this radio doesn't have mute/unmute control
	 * and windows program just emulate it using volume control.
	 * Let's plan to do the same in this driver.
	 *
	 * v4l2_ctrl_new_std(&radio->hdl, &usb_ma901radio_ctrl_ops,
	 *		  V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	 */

	v4l2_ctrl_new_std(&radio->hdl, &usb_ma901radio_ctrl_ops,
			  V4L2_CID_AUDIO_VOLUME, MA901_VOLUME_MIN,
			  MA901_VOLUME_MAX, 1, MA901_VOLUME_MAX);

	if (radio->hdl.error) {
		retval = radio->hdl.error;
		dev_err(&intf->dev, "couldn't register control\n");
		goto err_ctrl;
	}
	mutex_init(&radio->lock);

	radio->v4l2_dev.ctrl_handler = &radio->hdl;
	radio->v4l2_dev.release = usb_ma901radio_release;
	strscpy(radio->vdev.name, radio->v4l2_dev.name,
		sizeof(radio->vdev.name));
	radio->vdev.v4l2_dev = &radio->v4l2_dev;
	radio->vdev.fops = &usb_ma901radio_fops;
	radio->vdev.ioctl_ops = &usb_ma901radio_ioctl_ops;
	radio->vdev.release = video_device_release_empty;
	radio->vdev.lock = &radio->lock;
	radio->vdev.device_caps = V4L2_CAP_RADIO | V4L2_CAP_TUNER;

	radio->usbdev = interface_to_usbdev(intf);
	radio->intf = intf;
	usb_set_intfdata(intf, &radio->v4l2_dev);
	radio->curfreq = 95.21 * FREQ_MUL;

	video_set_drvdata(&radio->vdev, radio);

	/* TODO: we can get some statistics (freq, volume) from device
	 * but it's not implemented yet. After insertion in usb-port radio
	 * setups frequency and starts playing without any initialization.
	 * So we don't call usb_ma901radio_init/get_stat() here.
	 * retval = usb_ma901radio_init(radio);
	 */

	retval = video_register_device(&radio->vdev, VFL_TYPE_RADIO,
					radio_nr);
	if (retval < 0) {
		dev_err(&intf->dev, "could not register video device\n");
		goto err_vdev;
	}

	return 0;

err_vdev:
	v4l2_ctrl_handler_free(&radio->hdl);
err_ctrl:
	v4l2_device_unregister(&radio->v4l2_dev);
err_v4l2:
	kfree(radio->buffer);
err_nobuf:
	kfree(radio);
err:
	return retval;
}