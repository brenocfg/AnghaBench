#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_16__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
struct usb_interface {int /*<<< orphan*/  dev; struct usb_host_interface* altsetting; } ;
struct TYPE_19__ {int bInterfaceClass; int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {scalar_t__ bEndpointAddress; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct TYPE_24__ {TYPE_10__* ctrl_handler; int /*<<< orphan*/  name; } ;
struct TYPE_22__ {TYPE_7__* queue; int /*<<< orphan*/ * lock; TYPE_8__* v4l2_dev; } ;
struct TYPE_17__ {scalar_t__ error; } ;
struct TYPE_23__ {int /*<<< orphan*/ * dev; int /*<<< orphan*/ * lock; struct sur40_state* drv_priv; } ;
struct sur40_state {scalar_t__ bulk_in_epaddr; int vsvideo; struct input_polled_dev* input; struct sur40_state* bulk_in_buffer; TYPE_8__ v4l2; TYPE_4__ vdev; TYPE_10__ hdl; TYPE_7__ queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/ * dev; int /*<<< orphan*/  bulk_in_size; struct usb_device* usbdev; int /*<<< orphan*/  phys; int /*<<< orphan*/  qlock; int /*<<< orphan*/  buf_list; } ;
struct input_polled_dev {TYPE_16__* input; int /*<<< orphan*/  close; int /*<<< orphan*/  poll; int /*<<< orphan*/  open; int /*<<< orphan*/  poll_interval; struct sur40_state* private; } ;
struct TYPE_21__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_20__ {struct usb_endpoint_descriptor desc; } ;
struct TYPE_18__ {char* name; TYPE_3__ dev; int /*<<< orphan*/  phys; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_DESC ; 
 char* DRIVER_LONG ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POLL_INTERVAL ; 
 int /*<<< orphan*/  SUR40_BACKLIGHT_DEF ; 
 scalar_t__ SUR40_BACKLIGHT_MAX ; 
 scalar_t__ SUR40_BACKLIGHT_MIN ; 
 scalar_t__ SUR40_BRIGHTNESS_MAX ; 
 scalar_t__ SUR40_BRIGHTNESS_MIN ; 
 int SUR40_CONTRAST_DEF ; 
 scalar_t__ SUR40_CONTRAST_MAX ; 
 scalar_t__ SUR40_CONTRAST_MIN ; 
 int SUR40_GAIN_DEF ; 
 scalar_t__ SUR40_GAIN_MAX ; 
 scalar_t__ SUR40_GAIN_MIN ; 
 scalar_t__ TOUCH_ENDPOINT ; 
 int /*<<< orphan*/  V4L2_CID_BACKLIGHT_COMPENSATION ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int /*<<< orphan*/  VFL_TYPE_TOUCH ; 
 int /*<<< orphan*/  brightness ; 
 int /*<<< orphan*/  clamp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  contrast ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gain ; 
 struct input_polled_dev* input_allocate_polled_device () ; 
 int /*<<< orphan*/  input_free_polled_device (struct input_polled_dev*) ; 
 int input_register_polled_device (struct input_polled_dev*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct sur40_state*) ; 
 struct sur40_state* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sur40_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sur40_close ; 
 int /*<<< orphan*/  sur40_ctrl_ops ; 
 int /*<<< orphan*/  sur40_input_setup (TYPE_16__*) ; 
 int /*<<< orphan*/  sur40_open ; 
 int /*<<< orphan*/ * sur40_pix_format ; 
 int /*<<< orphan*/  sur40_poll ; 
 TYPE_7__ sur40_queue ; 
 TYPE_4__ sur40_video_device ; 
 int /*<<< orphan*/  usb_endpoint_maxp (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_make_path (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct sur40_state*) ; 
 int /*<<< orphan*/  usb_to_input_id (struct usb_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_10__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_10__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (TYPE_10__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_8__*) ; 
 int vb2_queue_init (TYPE_7__*) ; 
 int video_register_device (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_4__*,struct sur40_state*) ; 
 int /*<<< orphan*/  video_unregister_device (TYPE_4__*) ; 

__attribute__((used)) static int sur40_probe(struct usb_interface *interface,
		       const struct usb_device_id *id)
{
	struct usb_device *usbdev = interface_to_usbdev(interface);
	struct sur40_state *sur40;
	struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *endpoint;
	struct input_polled_dev *poll_dev;
	int error;

	/* Check if we really have the right interface. */
	iface_desc = &interface->altsetting[0];
	if (iface_desc->desc.bInterfaceClass != 0xFF)
		return -ENODEV;

	if (iface_desc->desc.bNumEndpoints < 5)
		return -ENODEV;

	/* Use endpoint #4 (0x86). */
	endpoint = &iface_desc->endpoint[4].desc;
	if (endpoint->bEndpointAddress != TOUCH_ENDPOINT)
		return -ENODEV;

	/* Allocate memory for our device state and initialize it. */
	sur40 = kzalloc(sizeof(struct sur40_state), GFP_KERNEL);
	if (!sur40)
		return -ENOMEM;

	poll_dev = input_allocate_polled_device();
	if (!poll_dev) {
		error = -ENOMEM;
		goto err_free_dev;
	}

	/* initialize locks/lists */
	INIT_LIST_HEAD(&sur40->buf_list);
	spin_lock_init(&sur40->qlock);
	mutex_init(&sur40->lock);

	/* Set up polled input device control structure */
	poll_dev->private = sur40;
	poll_dev->poll_interval = POLL_INTERVAL;
	poll_dev->open = sur40_open;
	poll_dev->poll = sur40_poll;
	poll_dev->close = sur40_close;

	/* Set up regular input device structure */
	sur40_input_setup(poll_dev->input);

	poll_dev->input->name = DRIVER_LONG;
	usb_to_input_id(usbdev, &poll_dev->input->id);
	usb_make_path(usbdev, sur40->phys, sizeof(sur40->phys));
	strlcat(sur40->phys, "/input0", sizeof(sur40->phys));
	poll_dev->input->phys = sur40->phys;
	poll_dev->input->dev.parent = &interface->dev;

	sur40->usbdev = usbdev;
	sur40->dev = &interface->dev;
	sur40->input = poll_dev;

	/* use the bulk-in endpoint tested above */
	sur40->bulk_in_size = usb_endpoint_maxp(endpoint);
	sur40->bulk_in_epaddr = endpoint->bEndpointAddress;
	sur40->bulk_in_buffer = kmalloc(sur40->bulk_in_size, GFP_KERNEL);
	if (!sur40->bulk_in_buffer) {
		dev_err(&interface->dev, "Unable to allocate input buffer.");
		error = -ENOMEM;
		goto err_free_polldev;
	}

	/* register the polled input device */
	error = input_register_polled_device(poll_dev);
	if (error) {
		dev_err(&interface->dev,
			"Unable to register polled input device.");
		goto err_free_buffer;
	}

	/* register the video master device */
	snprintf(sur40->v4l2.name, sizeof(sur40->v4l2.name), "%s", DRIVER_LONG);
	error = v4l2_device_register(sur40->dev, &sur40->v4l2);
	if (error) {
		dev_err(&interface->dev,
			"Unable to register video master device.");
		goto err_unreg_v4l2;
	}

	/* initialize the lock and subdevice */
	sur40->queue = sur40_queue;
	sur40->queue.drv_priv = sur40;
	sur40->queue.lock = &sur40->lock;
	sur40->queue.dev = sur40->dev;

	/* initialize the queue */
	error = vb2_queue_init(&sur40->queue);
	if (error)
		goto err_unreg_v4l2;

	sur40->pix_fmt = sur40_pix_format[0];
	sur40->vdev = sur40_video_device;
	sur40->vdev.v4l2_dev = &sur40->v4l2;
	sur40->vdev.lock = &sur40->lock;
	sur40->vdev.queue = &sur40->queue;
	video_set_drvdata(&sur40->vdev, sur40);

	/* initialize the control handler for 4 controls */
	v4l2_ctrl_handler_init(&sur40->hdl, 4);
	sur40->v4l2.ctrl_handler = &sur40->hdl;
	sur40->vsvideo = (SUR40_CONTRAST_DEF << 4) | SUR40_GAIN_DEF;

	v4l2_ctrl_new_std(&sur40->hdl, &sur40_ctrl_ops, V4L2_CID_BRIGHTNESS,
	  SUR40_BRIGHTNESS_MIN, SUR40_BRIGHTNESS_MAX, 1, clamp(brightness,
	  (uint)SUR40_BRIGHTNESS_MIN, (uint)SUR40_BRIGHTNESS_MAX));

	v4l2_ctrl_new_std(&sur40->hdl, &sur40_ctrl_ops, V4L2_CID_CONTRAST,
	  SUR40_CONTRAST_MIN, SUR40_CONTRAST_MAX, 1, clamp(contrast,
	  (uint)SUR40_CONTRAST_MIN, (uint)SUR40_CONTRAST_MAX));

	v4l2_ctrl_new_std(&sur40->hdl, &sur40_ctrl_ops, V4L2_CID_GAIN,
	  SUR40_GAIN_MIN, SUR40_GAIN_MAX, 1, clamp(gain,
	  (uint)SUR40_GAIN_MIN, (uint)SUR40_GAIN_MAX));

	v4l2_ctrl_new_std(&sur40->hdl, &sur40_ctrl_ops,
	  V4L2_CID_BACKLIGHT_COMPENSATION, SUR40_BACKLIGHT_MIN,
	  SUR40_BACKLIGHT_MAX, 1, SUR40_BACKLIGHT_DEF);

	v4l2_ctrl_handler_setup(&sur40->hdl);

	if (sur40->hdl.error) {
		dev_err(&interface->dev,
			"Unable to register video controls.");
		v4l2_ctrl_handler_free(&sur40->hdl);
		goto err_unreg_v4l2;
	}

	error = video_register_device(&sur40->vdev, VFL_TYPE_TOUCH, -1);
	if (error) {
		dev_err(&interface->dev,
			"Unable to register video subdevice.");
		goto err_unreg_video;
	}

	/* we can register the device now, as it is ready */
	usb_set_intfdata(interface, sur40);
	dev_dbg(&interface->dev, "%s is now attached\n", DRIVER_DESC);

	return 0;

err_unreg_video:
	video_unregister_device(&sur40->vdev);
err_unreg_v4l2:
	v4l2_device_unregister(&sur40->v4l2);
err_free_buffer:
	kfree(sur40->bulk_in_buffer);
err_free_polldev:
	input_free_polled_device(sur40->input);
err_free_dev:
	kfree(sur40);

	return error;
}