#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; TYPE_5__* cur_altsetting; TYPE_3__* altsetting; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {char* product; TYPE_6__ descriptor; scalar_t__ manufacturer; } ;
struct pegasus {int /*<<< orphan*/  data_dma; int /*<<< orphan*/  data; int /*<<< orphan*/  data_len; TYPE_8__* irq; struct input_dev* dev; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; int /*<<< orphan*/  init; struct usb_interface* intf; struct usb_device* usbdev; int /*<<< orphan*/  pm_mutex; } ;
struct TYPE_17__ {int /*<<< orphan*/ * parent; } ;
struct input_dev {int /*<<< orphan*/  propbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  absbit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_7__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;
struct TYPE_18__ {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_11__ {int bInterfaceNumber; } ;
struct TYPE_15__ {TYPE_4__* endpoint; TYPE_1__ desc; } ;
struct TYPE_14__ {struct usb_endpoint_descriptor desc; } ;
struct TYPE_12__ {int bNumEndpoints; } ;
struct TYPE_13__ {TYPE_2__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_TOOL_PEN ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INPUT_PROP_DIRECT ; 
 int /*<<< orphan*/  INPUT_PROP_POINTER ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct pegasus*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct pegasus*) ; 
 struct pegasus* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pegasus_close ; 
 int /*<<< orphan*/  pegasus_init ; 
 int /*<<< orphan*/  pegasus_irq ; 
 int /*<<< orphan*/  pegasus_open ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_alloc_coherent (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_8__* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_8__*,struct usb_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pegasus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_coherent (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_8__*) ; 
 int /*<<< orphan*/  usb_make_path (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_maxpacket (struct usb_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipeout (int) ; 
 int usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct pegasus*) ; 
 int /*<<< orphan*/  usb_to_input_id (struct usb_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pegasus_probe(struct usb_interface *intf,
			 const struct usb_device_id *id)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	struct usb_endpoint_descriptor *endpoint;
	struct pegasus *pegasus;
	struct input_dev *input_dev;
	int error;
	int pipe;

	/* We control interface 0 */
	if (intf->cur_altsetting->desc.bInterfaceNumber >= 1)
		return -ENODEV;

	/* Sanity check that the device has an endpoint */
	if (intf->altsetting[0].desc.bNumEndpoints < 1) {
		dev_err(&intf->dev, "Invalid number of endpoints\n");
		return -EINVAL;
	}

	endpoint = &intf->cur_altsetting->endpoint[0].desc;

	pegasus = kzalloc(sizeof(*pegasus), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!pegasus || !input_dev) {
		error = -ENOMEM;
		goto err_free_mem;
	}

	mutex_init(&pegasus->pm_mutex);

	pegasus->usbdev = dev;
	pegasus->dev = input_dev;
	pegasus->intf = intf;

	pipe = usb_rcvintpipe(dev, endpoint->bEndpointAddress);
	pegasus->data_len = usb_maxpacket(dev, pipe, usb_pipeout(pipe));

	pegasus->data = usb_alloc_coherent(dev, pegasus->data_len, GFP_KERNEL,
					   &pegasus->data_dma);
	if (!pegasus->data) {
		error = -ENOMEM;
		goto err_free_mem;
	}

	pegasus->irq = usb_alloc_urb(0, GFP_KERNEL);
	if (!pegasus->irq) {
		error = -ENOMEM;
		goto err_free_dma;
	}

	usb_fill_int_urb(pegasus->irq, dev, pipe,
			 pegasus->data, pegasus->data_len,
			 pegasus_irq, pegasus, endpoint->bInterval);

	pegasus->irq->transfer_dma = pegasus->data_dma;
	pegasus->irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	if (dev->manufacturer)
		strlcpy(pegasus->name, dev->manufacturer,
			sizeof(pegasus->name));

	if (dev->product) {
		if (dev->manufacturer)
			strlcat(pegasus->name, " ", sizeof(pegasus->name));
		strlcat(pegasus->name, dev->product, sizeof(pegasus->name));
	}

	if (!strlen(pegasus->name))
		snprintf(pegasus->name, sizeof(pegasus->name),
			 "USB Pegasus Device %04x:%04x",
			 le16_to_cpu(dev->descriptor.idVendor),
			 le16_to_cpu(dev->descriptor.idProduct));

	usb_make_path(dev, pegasus->phys, sizeof(pegasus->phys));
	strlcat(pegasus->phys, "/input0", sizeof(pegasus->phys));

	INIT_WORK(&pegasus->init, pegasus_init);

	usb_set_intfdata(intf, pegasus);

	input_dev->name = pegasus->name;
	input_dev->phys = pegasus->phys;
	usb_to_input_id(dev, &input_dev->id);
	input_dev->dev.parent = &intf->dev;

	input_set_drvdata(input_dev, pegasus);

	input_dev->open = pegasus_open;
	input_dev->close = pegasus_close;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);

	__set_bit(ABS_X, input_dev->absbit);
	__set_bit(ABS_Y, input_dev->absbit);

	__set_bit(BTN_TOUCH, input_dev->keybit);
	__set_bit(BTN_RIGHT, input_dev->keybit);
	__set_bit(BTN_TOOL_PEN, input_dev->keybit);

	__set_bit(INPUT_PROP_DIRECT, input_dev->propbit);
	__set_bit(INPUT_PROP_POINTER, input_dev->propbit);

	input_set_abs_params(input_dev, ABS_X, -1500, 1500, 8, 0);
	input_set_abs_params(input_dev, ABS_Y, 1600, 3000, 8, 0);

	error = input_register_device(pegasus->dev);
	if (error)
		goto err_free_urb;

	return 0;

err_free_urb:
	usb_free_urb(pegasus->irq);
err_free_dma:
	usb_free_coherent(dev, pegasus->data_len,
			  pegasus->data, pegasus->data_dma);
err_free_mem:
	input_free_device(input_dev);
	kfree(pegasus);
	usb_set_intfdata(intf, NULL);

	return error;
}