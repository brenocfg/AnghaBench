#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int /*<<< orphan*/  ctrl_handler; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; int /*<<< orphan*/  release; } ;
struct TYPE_8__ {int device_caps; int /*<<< orphan*/  vfl_dir; int /*<<< orphan*/  release; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; TYPE_4__* v4l2_dev; int /*<<< orphan*/  name; int /*<<< orphan*/  ctrl_handler; } ;
struct i2c_adapter {int dummy; } ;
struct si4713_usb_device {struct si4713_usb_device* buffer; TYPE_4__ v4l2_dev; TYPE_1__ vdev; int /*<<< orphan*/  lock; struct v4l2_subdev* v4l2_subdev; struct i2c_adapter i2c_adapter; struct usb_interface* intf; int /*<<< orphan*/  usbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_LENGTH ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int V4L2_CAP_MODULATOR ; 
 int V4L2_CAP_RDS_OUTPUT ; 
 int /*<<< orphan*/  VFL_DIR_TX ; 
 int /*<<< orphan*/  VFL_TYPE_RADIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  i2c_del_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct si4713_usb_device*) ; 
 struct si4713_usb_device* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct si4713_usb_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  si4713_board_info ; 
 int si4713_register_i2c_adapter (struct si4713_usb_device*) ; 
 int si4713_start_seq (struct si4713_usb_device*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,TYPE_4__*) ; 
 int /*<<< orphan*/  usb_si4713_fops ; 
 int /*<<< orphan*/  usb_si4713_ioctl_ops ; 
 int /*<<< orphan*/  usb_si4713_video_device_release ; 
 int v4l2_device_register (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_4__*) ; 
 struct v4l2_subdev* v4l2_i2c_new_subdev_board (TYPE_4__*,struct i2c_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_device_node_name (TYPE_1__*) ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int video_register_device (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_1__*,struct si4713_usb_device*) ; 

__attribute__((used)) static int usb_si4713_probe(struct usb_interface *intf,
				const struct usb_device_id *id)
{
	struct si4713_usb_device *radio;
	struct i2c_adapter *adapter;
	struct v4l2_subdev *sd;
	int retval = -ENOMEM;

	dev_info(&intf->dev, "Si4713 development board discovered: (%04X:%04X)\n",
			id->idVendor, id->idProduct);

	/* Initialize local device structure */
	radio = kzalloc(sizeof(struct si4713_usb_device), GFP_KERNEL);
	if (radio)
		radio->buffer = kmalloc(BUFFER_LENGTH, GFP_KERNEL);

	if (!radio || !radio->buffer) {
		dev_err(&intf->dev, "kmalloc for si4713_usb_device failed\n");
		kfree(radio);
		return -ENOMEM;
	}

	mutex_init(&radio->lock);

	radio->usbdev = interface_to_usbdev(intf);
	radio->intf = intf;
	usb_set_intfdata(intf, &radio->v4l2_dev);

	retval = si4713_start_seq(radio);
	if (retval < 0)
		goto err_v4l2;

	retval = v4l2_device_register(&intf->dev, &radio->v4l2_dev);
	if (retval < 0) {
		dev_err(&intf->dev, "couldn't register v4l2_device\n");
		goto err_v4l2;
	}

	retval = si4713_register_i2c_adapter(radio);
	if (retval < 0) {
		dev_err(&intf->dev, "could not register i2c device\n");
		goto err_i2cdev;
	}

	adapter = &radio->i2c_adapter;
	sd = v4l2_i2c_new_subdev_board(&radio->v4l2_dev, adapter,
					  &si4713_board_info, NULL);
	radio->v4l2_subdev = sd;
	if (!sd) {
		dev_err(&intf->dev, "cannot get v4l2 subdevice\n");
		retval = -ENODEV;
		goto del_adapter;
	}

	radio->vdev.ctrl_handler = sd->ctrl_handler;
	radio->v4l2_dev.release = usb_si4713_video_device_release;
	strscpy(radio->vdev.name, radio->v4l2_dev.name,
		sizeof(radio->vdev.name));
	radio->vdev.v4l2_dev = &radio->v4l2_dev;
	radio->vdev.fops = &usb_si4713_fops;
	radio->vdev.ioctl_ops = &usb_si4713_ioctl_ops;
	radio->vdev.lock = &radio->lock;
	radio->vdev.release = video_device_release_empty;
	radio->vdev.vfl_dir = VFL_DIR_TX;
	radio->vdev.device_caps = V4L2_CAP_MODULATOR | V4L2_CAP_RDS_OUTPUT;

	video_set_drvdata(&radio->vdev, radio);

	retval = video_register_device(&radio->vdev, VFL_TYPE_RADIO, -1);
	if (retval < 0) {
		dev_err(&intf->dev, "could not register video device\n");
		goto del_adapter;
	}

	dev_info(&intf->dev, "V4L2 device registered as %s\n",
			video_device_node_name(&radio->vdev));

	return 0;

del_adapter:
	i2c_del_adapter(adapter);
err_i2cdev:
	v4l2_device_unregister(&radio->v4l2_dev);
err_v4l2:
	kfree(radio->buffer);
	kfree(radio);
	return retval;
}