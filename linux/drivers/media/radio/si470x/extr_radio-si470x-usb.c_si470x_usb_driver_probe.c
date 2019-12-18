#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; struct usb_host_interface* cur_altsetting; } ;
struct TYPE_11__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  wMaxPacketSize; } ;
struct usb_device_id {int idVendor; int idProduct; } ;
struct TYPE_14__ {int /*<<< orphan*/  release; } ;
struct TYPE_15__ {int error; } ;
struct TYPE_13__ {int device_caps; int /*<<< orphan*/  release; TYPE_5__* v4l2_dev; int /*<<< orphan*/ * lock; TYPE_7__* ctrl_handler; } ;
struct si470x_device {int band; int* registers; int software_version; int hardware_version; int buf_size; struct si470x_device* usb_buf; struct si470x_device* int_in_buffer; int /*<<< orphan*/  int_in_urb; TYPE_5__ v4l2_dev; TYPE_7__ hdl; struct si470x_device* buffer; TYPE_3__ videodev; int /*<<< orphan*/  read_queue; scalar_t__ rd_index; scalar_t__ wr_index; int /*<<< orphan*/  lock; int /*<<< orphan*/  usbdev; struct usb_endpoint_descriptor* int_in_endpoint; int /*<<< orphan*/  vidioc_querycap; int /*<<< orphan*/  fops_release; int /*<<< orphan*/  fops_open; int /*<<< orphan*/  set_register; int /*<<< orphan*/  get_register; int /*<<< orphan*/  completion; struct usb_interface* intf; } ;
struct TYPE_12__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLINK_GREEN_LED ; 
 size_t DEVICEID ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 double FREQ_MUL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_REQ_GET_REPORT ; 
 int MAX_REPORT_SIZE ; 
 int RADIO_FW_VERSION ; 
 int RADIO_HW_VERSION ; 
 size_t SI_CHIPID ; 
 int SI_CHIPID_FIRMWARE ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int V4L2_CAP_HW_FREQ_SEEK ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_RDS_CAPTURE ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_TUNER ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_MUTE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_VOLUME ; 
 int /*<<< orphan*/  VFL_TYPE_RADIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int get_unaligned_be16 (struct si470x_device*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct si470x_device*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct si470x_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radio_nr ; 
 int rds_buf ; 
 int /*<<< orphan*/  si470x_ctrl_ops ; 
 int /*<<< orphan*/  si470x_fops_open ; 
 int /*<<< orphan*/  si470x_fops_release ; 
 scalar_t__ si470x_get_all_registers (struct si470x_device*) ; 
 int /*<<< orphan*/  si470x_get_register ; 
 scalar_t__ si470x_get_scratch_page_versions (struct si470x_device*) ; 
 int /*<<< orphan*/  si470x_set_freq (struct si470x_device*,double) ; 
 int /*<<< orphan*/  si470x_set_led_state (struct si470x_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si470x_set_register ; 
 int si470x_start_usb (struct si470x_device*) ; 
 int /*<<< orphan*/  si470x_usb_release ; 
 TYPE_3__ si470x_viddev_template ; 
 int /*<<< orphan*/  si470x_vidioc_querycap ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,struct si470x_device*,int,int) ; 
 scalar_t__ usb_endpoint_is_int_in (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct si470x_device*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_7__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_7__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_5__*) ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int video_register_device (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_3__*,struct si470x_device*) ; 

__attribute__((used)) static int si470x_usb_driver_probe(struct usb_interface *intf,
		const struct usb_device_id *id)
{
	struct si470x_device *radio;
	struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *endpoint;
	int i, int_end_size, retval;
	unsigned char version_warning = 0;

	/* private data allocation and initialization */
	radio = kzalloc(sizeof(struct si470x_device), GFP_KERNEL);
	if (!radio) {
		retval = -ENOMEM;
		goto err_initial;
	}
	radio->usb_buf = kmalloc(MAX_REPORT_SIZE, GFP_KERNEL);
	if (radio->usb_buf == NULL) {
		retval = -ENOMEM;
		goto err_radio;
	}
	radio->usbdev = interface_to_usbdev(intf);
	radio->intf = intf;
	radio->band = 1; /* Default to 76 - 108 MHz */
	mutex_init(&radio->lock);
	init_completion(&radio->completion);

	radio->get_register = si470x_get_register;
	radio->set_register = si470x_set_register;
	radio->fops_open = si470x_fops_open;
	radio->fops_release = si470x_fops_release;
	radio->vidioc_querycap = si470x_vidioc_querycap;

	iface_desc = intf->cur_altsetting;

	/* Set up interrupt endpoint information. */
	for (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		endpoint = &iface_desc->endpoint[i].desc;
		if (usb_endpoint_is_int_in(endpoint))
			radio->int_in_endpoint = endpoint;
	}
	if (!radio->int_in_endpoint) {
		dev_info(&intf->dev, "could not find interrupt in endpoint\n");
		retval = -EIO;
		goto err_usbbuf;
	}

	int_end_size = le16_to_cpu(radio->int_in_endpoint->wMaxPacketSize);

	radio->int_in_buffer = kmalloc(int_end_size, GFP_KERNEL);
	if (!radio->int_in_buffer) {
		dev_info(&intf->dev, "could not allocate int_in_buffer");
		retval = -ENOMEM;
		goto err_usbbuf;
	}

	radio->int_in_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!radio->int_in_urb) {
		retval = -ENOMEM;
		goto err_intbuffer;
	}

	radio->v4l2_dev.release = si470x_usb_release;

	/*
	 * The si470x SiLabs reference design uses the same USB IDs as
	 * 'Thanko's Raremono' si4734 based receiver. So check here which we
	 * have: attempt to read the device ID from the si470x: the lower 12
	 * bits should be 0x0242 for the si470x.
	 *
	 * We use this check to determine which device we are dealing with.
	 */
	if (id->idVendor == 0x10c4 && id->idProduct == 0x818a) {
		retval = usb_control_msg(radio->usbdev,
				usb_rcvctrlpipe(radio->usbdev, 0),
				HID_REQ_GET_REPORT,
				USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_DIR_IN,
				1, 2,
				radio->usb_buf, 3, 500);
		if (retval != 3 ||
		    (get_unaligned_be16(&radio->usb_buf[1]) & 0xfff) != 0x0242) {
			dev_info(&intf->dev, "this is not a si470x device.\n");
			retval = -ENODEV;
			goto err_urb;
		}
	}

	retval = v4l2_device_register(&intf->dev, &radio->v4l2_dev);
	if (retval < 0) {
		dev_err(&intf->dev, "couldn't register v4l2_device\n");
		goto err_urb;
	}

	v4l2_ctrl_handler_init(&radio->hdl, 2);
	v4l2_ctrl_new_std(&radio->hdl, &si470x_ctrl_ops,
			  V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	v4l2_ctrl_new_std(&radio->hdl, &si470x_ctrl_ops,
			  V4L2_CID_AUDIO_VOLUME, 0, 15, 1, 15);
	if (radio->hdl.error) {
		retval = radio->hdl.error;
		dev_err(&intf->dev, "couldn't register control\n");
		goto err_dev;
	}
	radio->videodev = si470x_viddev_template;
	radio->videodev.ctrl_handler = &radio->hdl;
	radio->videodev.lock = &radio->lock;
	radio->videodev.v4l2_dev = &radio->v4l2_dev;
	radio->videodev.release = video_device_release_empty;
	radio->videodev.device_caps =
		V4L2_CAP_HW_FREQ_SEEK | V4L2_CAP_READWRITE | V4L2_CAP_TUNER |
		V4L2_CAP_RADIO | V4L2_CAP_RDS_CAPTURE;
	video_set_drvdata(&radio->videodev, radio);

	/* get device and chip versions */
	if (si470x_get_all_registers(radio) < 0) {
		retval = -EIO;
		goto err_ctrl;
	}
	dev_info(&intf->dev, "DeviceID=0x%4.4hx ChipID=0x%4.4hx\n",
			radio->registers[DEVICEID], radio->registers[SI_CHIPID]);
	if ((radio->registers[SI_CHIPID] & SI_CHIPID_FIRMWARE) < RADIO_FW_VERSION) {
		dev_warn(&intf->dev,
			"This driver is known to work with firmware version %hu,\n",
			RADIO_FW_VERSION);
		dev_warn(&intf->dev,
			"but the device has firmware version %hu.\n",
			radio->registers[SI_CHIPID] & SI_CHIPID_FIRMWARE);
		version_warning = 1;
	}

	/* get software and hardware versions */
	if (si470x_get_scratch_page_versions(radio) < 0) {
		retval = -EIO;
		goto err_ctrl;
	}
	dev_info(&intf->dev, "software version %d, hardware version %d\n",
			radio->software_version, radio->hardware_version);
	if (radio->hardware_version < RADIO_HW_VERSION) {
		dev_warn(&intf->dev,
			"This driver is known to work with hardware version %hu,\n",
			RADIO_HW_VERSION);
		dev_warn(&intf->dev,
			"but the device has hardware version %hu.\n",
			radio->hardware_version);
		version_warning = 1;
	}

	/* give out version warning */
	if (version_warning == 1) {
		dev_warn(&intf->dev,
			"If you have some trouble using this driver,\n");
		dev_warn(&intf->dev,
			"please report to V4L ML at linux-media@vger.kernel.org\n");
	}

	/* set led to connect state */
	si470x_set_led_state(radio, BLINK_GREEN_LED);

	/* rds buffer allocation */
	radio->buf_size = rds_buf * 3;
	radio->buffer = kmalloc(radio->buf_size, GFP_KERNEL);
	if (!radio->buffer) {
		retval = -EIO;
		goto err_ctrl;
	}

	/* rds buffer configuration */
	radio->wr_index = 0;
	radio->rd_index = 0;
	init_waitqueue_head(&radio->read_queue);
	usb_set_intfdata(intf, radio);

	/* start radio */
	retval = si470x_start_usb(radio);
	if (retval < 0)
		goto err_buf;

	/* set initial frequency */
	si470x_set_freq(radio, 87.5 * FREQ_MUL); /* available in all regions */

	/* register video device */
	retval = video_register_device(&radio->videodev, VFL_TYPE_RADIO,
			radio_nr);
	if (retval) {
		dev_err(&intf->dev, "Could not register video device\n");
		goto err_all;
	}

	return 0;
err_all:
	usb_kill_urb(radio->int_in_urb);
err_buf:
	kfree(radio->buffer);
err_ctrl:
	v4l2_ctrl_handler_free(&radio->hdl);
err_dev:
	v4l2_device_unregister(&radio->v4l2_dev);
err_urb:
	usb_free_urb(radio->int_in_urb);
err_intbuffer:
	kfree(radio->int_in_buffer);
err_usbbuf:
	kfree(radio->usb_buf);
err_radio:
	kfree(radio);
err_initial:
	return retval;
}