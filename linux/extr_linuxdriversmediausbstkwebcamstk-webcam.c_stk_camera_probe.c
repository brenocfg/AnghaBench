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
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl_handler {int error; } ;
struct usb_interface {struct usb_host_interface* cur_altsetting; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {int dummy; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct TYPE_8__ {int hflip; int vflip; int /*<<< orphan*/  mode; int /*<<< orphan*/  palette; } ;
struct stk_camera {int first_init; int frame_size; TYPE_4__ v4l2_dev; int /*<<< orphan*/  sio_full; int /*<<< orphan*/  sio_avail; TYPE_3__ vsettings; scalar_t__ isoc_ep; scalar_t__ n_sbufs; struct usb_interface* interface; struct usb_device* udev; int /*<<< orphan*/  wait_frame; int /*<<< orphan*/  lock; int /*<<< orphan*/  spinlock; struct v4l2_ctrl_handler hdl; } ;
struct TYPE_7__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MODE_VGA ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_RGB565 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 int hflip ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct stk_camera*) ; 
 struct stk_camera* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  set_present (struct stk_camera*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stk_ctrl_ops ; 
 int stk_register_video_device (struct stk_camera*) ; 
 int /*<<< orphan*/  stk_upside_down_dmi_table ; 
 scalar_t__ usb_endpoint_is_isoc_in (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_num (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_get_intf (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct stk_camera*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_4__*) ; 
 int vflip ; 

__attribute__((used)) static int stk_camera_probe(struct usb_interface *interface,
		const struct usb_device_id *id)
{
	struct v4l2_ctrl_handler *hdl;
	int err = 0;
	int i;

	struct stk_camera *dev = NULL;
	struct usb_device *udev = interface_to_usbdev(interface);
	struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *endpoint;

	dev = kzalloc(sizeof(struct stk_camera), GFP_KERNEL);
	if (dev == NULL) {
		pr_err("Out of memory !\n");
		return -ENOMEM;
	}
	err = v4l2_device_register(&interface->dev, &dev->v4l2_dev);
	if (err < 0) {
		dev_err(&udev->dev, "couldn't register v4l2_device\n");
		kfree(dev);
		return err;
	}
	hdl = &dev->hdl;
	v4l2_ctrl_handler_init(hdl, 3);
	v4l2_ctrl_new_std(hdl, &stk_ctrl_ops,
			  V4L2_CID_BRIGHTNESS, 0, 0xff, 0x1, 0x60);
	v4l2_ctrl_new_std(hdl, &stk_ctrl_ops,
			  V4L2_CID_HFLIP, 0, 1, 1, 1);
	v4l2_ctrl_new_std(hdl, &stk_ctrl_ops,
			  V4L2_CID_VFLIP, 0, 1, 1, 1);
	if (hdl->error) {
		err = hdl->error;
		dev_err(&udev->dev, "couldn't register control\n");
		goto error;
	}
	dev->v4l2_dev.ctrl_handler = hdl;

	spin_lock_init(&dev->spinlock);
	mutex_init(&dev->lock);
	init_waitqueue_head(&dev->wait_frame);
	dev->first_init = 1; /* webcam LED management */

	dev->udev = udev;
	dev->interface = interface;
	usb_get_intf(interface);

	if (hflip != -1)
		dev->vsettings.hflip = hflip;
	else if (dmi_check_system(stk_upside_down_dmi_table))
		dev->vsettings.hflip = 1;
	else
		dev->vsettings.hflip = 0;
	if (vflip != -1)
		dev->vsettings.vflip = vflip;
	else if (dmi_check_system(stk_upside_down_dmi_table))
		dev->vsettings.vflip = 1;
	else
		dev->vsettings.vflip = 0;
	dev->n_sbufs = 0;
	set_present(dev);

	/* Set up the endpoint information
	 * use only the first isoc-in endpoint
	 * for the current alternate setting */
	iface_desc = interface->cur_altsetting;

	for (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		endpoint = &iface_desc->endpoint[i].desc;

		if (!dev->isoc_ep
			&& usb_endpoint_is_isoc_in(endpoint)) {
			/* we found an isoc in endpoint */
			dev->isoc_ep = usb_endpoint_num(endpoint);
			break;
		}
	}
	if (!dev->isoc_ep) {
		pr_err("Could not find isoc-in endpoint\n");
		err = -ENODEV;
		goto error;
	}
	dev->vsettings.palette = V4L2_PIX_FMT_RGB565;
	dev->vsettings.mode = MODE_VGA;
	dev->frame_size = 640 * 480 * 2;

	INIT_LIST_HEAD(&dev->sio_avail);
	INIT_LIST_HEAD(&dev->sio_full);

	usb_set_intfdata(interface, dev);

	err = stk_register_video_device(dev);
	if (err)
		goto error;

	return 0;

error:
	v4l2_ctrl_handler_free(hdl);
	v4l2_device_unregister(&dev->v4l2_dev);
	kfree(dev);
	return err;
}