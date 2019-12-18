#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl_handler {int error; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {scalar_t__ product; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/  release; struct v4l2_ctrl_handler* ctrl_handler; } ;
struct TYPE_7__ {int device_caps; int /*<<< orphan*/  vfl_dir; int /*<<< orphan*/  release; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; TYPE_4__* v4l2_dev; int /*<<< orphan*/  name; } ;
struct keene_device {int pa; int tx; int stereo; struct keene_device* buffer; TYPE_4__ v4l2_dev; TYPE_1__ vdev; struct usb_interface* intf; void* usbdev; int /*<<< orphan*/  lock; struct v4l2_ctrl_handler hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_LENGTH ; 
 int ENODEV ; 
 int ENOMEM ; 
 double FREQ_MUL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int V4L2_CAP_MODULATOR ; 
 int V4L2_CAP_RADIO ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_COMPRESSION_GAIN ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_MUTE ; 
 int /*<<< orphan*/  V4L2_CID_TUNE_POWER_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_TUNE_PREEMPHASIS ; 
 int /*<<< orphan*/  V4L2_PREEMPHASIS_50_uS ; 
 int /*<<< orphan*/  V4L2_PREEMPHASIS_75_uS ; 
 int /*<<< orphan*/  VFL_DIR_TX ; 
 int /*<<< orphan*/  VFL_TYPE_RADIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 void* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  keene_cmd_main (struct keene_device*,double,int) ; 
 int /*<<< orphan*/  keene_ctrl_ops ; 
 int /*<<< orphan*/  kfree (struct keene_device*) ; 
 struct keene_device* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct keene_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_keene_fops ; 
 int /*<<< orphan*/  usb_keene_ioctl_ops ; 
 int /*<<< orphan*/  usb_keene_video_device_release ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_4__*) ; 
 int /*<<< orphan*/  video_device_node_name (TYPE_1__*) ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int video_register_device (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_1__*,struct keene_device*) ; 

__attribute__((used)) static int usb_keene_probe(struct usb_interface *intf,
				const struct usb_device_id *id)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	struct keene_device *radio;
	struct v4l2_ctrl_handler *hdl;
	int retval = 0;

	/*
	 * The Keene FM transmitter USB device has the same USB ID as
	 * the Logitech AudioHub Speaker, but it should ignore the hid.
	 * Check if the name is that of the Keene device.
	 * If not, then someone connected the AudioHub and we shouldn't
	 * attempt to handle this driver.
	 * For reference: the product name of the AudioHub is
	 * "AudioHub Speaker".
	 */
	if (dev->product && strcmp(dev->product, "B-LINK USB Audio  "))
		return -ENODEV;

	radio = kzalloc(sizeof(struct keene_device), GFP_KERNEL);
	if (radio)
		radio->buffer = kmalloc(BUFFER_LENGTH, GFP_KERNEL);

	if (!radio || !radio->buffer) {
		dev_err(&intf->dev, "kmalloc for keene_device failed\n");
		kfree(radio);
		retval = -ENOMEM;
		goto err;
	}

	hdl = &radio->hdl;
	v4l2_ctrl_handler_init(hdl, 4);
	v4l2_ctrl_new_std(hdl, &keene_ctrl_ops, V4L2_CID_AUDIO_MUTE,
			0, 1, 1, 0);
	v4l2_ctrl_new_std_menu(hdl, &keene_ctrl_ops, V4L2_CID_TUNE_PREEMPHASIS,
			V4L2_PREEMPHASIS_75_uS, 1, V4L2_PREEMPHASIS_50_uS);
	v4l2_ctrl_new_std(hdl, &keene_ctrl_ops, V4L2_CID_TUNE_POWER_LEVEL,
			84, 118, 1, 118);
	v4l2_ctrl_new_std(hdl, &keene_ctrl_ops, V4L2_CID_AUDIO_COMPRESSION_GAIN,
			-15, 18, 3, 0);
	radio->pa = 118;
	radio->tx = 0x32;
	radio->stereo = true;
	if (hdl->error) {
		retval = hdl->error;

		v4l2_ctrl_handler_free(hdl);
		goto err_v4l2;
	}
	retval = v4l2_device_register(&intf->dev, &radio->v4l2_dev);
	if (retval < 0) {
		dev_err(&intf->dev, "couldn't register v4l2_device\n");
		goto err_v4l2;
	}

	mutex_init(&radio->lock);

	radio->v4l2_dev.ctrl_handler = hdl;
	radio->v4l2_dev.release = usb_keene_video_device_release;
	strscpy(radio->vdev.name, radio->v4l2_dev.name,
		sizeof(radio->vdev.name));
	radio->vdev.v4l2_dev = &radio->v4l2_dev;
	radio->vdev.fops = &usb_keene_fops;
	radio->vdev.ioctl_ops = &usb_keene_ioctl_ops;
	radio->vdev.lock = &radio->lock;
	radio->vdev.release = video_device_release_empty;
	radio->vdev.vfl_dir = VFL_DIR_TX;
	radio->vdev.device_caps = V4L2_CAP_RADIO | V4L2_CAP_MODULATOR;

	radio->usbdev = interface_to_usbdev(intf);
	radio->intf = intf;
	usb_set_intfdata(intf, &radio->v4l2_dev);

	video_set_drvdata(&radio->vdev, radio);

	/* at least 11ms is needed in order to settle hardware */
	msleep(20);
	keene_cmd_main(radio, 95.16 * FREQ_MUL, false);

	retval = video_register_device(&radio->vdev, VFL_TYPE_RADIO, -1);
	if (retval < 0) {
		dev_err(&intf->dev, "could not register video device\n");
		goto err_vdev;
	}
	v4l2_ctrl_handler_setup(hdl);
	dev_info(&intf->dev, "V4L2 device registered as %s\n",
			video_device_node_name(&radio->vdev));
	return 0;

err_vdev:
	v4l2_device_unregister(&radio->v4l2_dev);
err_v4l2:
	kfree(radio->buffer);
	kfree(radio);
err:
	return retval;
}