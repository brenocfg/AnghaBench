#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {TYPE_4__* cur_altsetting; int /*<<< orphan*/  dev; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/ * parent; } ;
struct input_dev {int /*<<< orphan*/  mscbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  absbit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_2__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;
struct hanwang {int /*<<< orphan*/  data_dma; int /*<<< orphan*/  data; TYPE_5__* features; TYPE_6__* irq; struct input_dev* dev; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; struct usb_device* usbdev; } ;
struct TYPE_14__ {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_13__ {int /*<<< orphan*/  pkg_len; int /*<<< orphan*/  max_pressure; int /*<<< orphan*/  max_tilt_y; int /*<<< orphan*/  max_tilt_x; int /*<<< orphan*/  max_y; int /*<<< orphan*/  max_x; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int bNumEndpoints; } ;
struct TYPE_12__ {TYPE_3__* endpoint; TYPE_1__ desc; } ;
struct TYPE_11__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_TILT_X ; 
 int /*<<< orphan*/  ABS_TILT_Y ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_features (struct usb_device*,struct hanwang*) ; 
 int /*<<< orphan*/  hanwang_close ; 
 int /*<<< orphan*/  hanwang_irq ; 
 int /*<<< orphan*/  hanwang_open ; 
 int /*<<< orphan*/ * hw_absevents ; 
 int /*<<< orphan*/ * hw_btnevents ; 
 int /*<<< orphan*/ * hw_eventtypes ; 
 int /*<<< orphan*/ * hw_mscevents ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct hanwang*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct hanwang*) ; 
 struct hanwang* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_alloc_coherent (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_6__* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_6__*,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hanwang*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_coherent (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_6__*) ; 
 int /*<<< orphan*/  usb_make_path (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct hanwang*) ; 
 int /*<<< orphan*/  usb_to_input_id (struct usb_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hanwang_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	struct usb_endpoint_descriptor *endpoint;
	struct hanwang *hanwang;
	struct input_dev *input_dev;
	int error;
	int i;

	if (intf->cur_altsetting->desc.bNumEndpoints < 1)
		return -ENODEV;

	hanwang = kzalloc(sizeof(struct hanwang), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!hanwang || !input_dev) {
		error = -ENOMEM;
		goto fail1;
	}

	if (!get_features(dev, hanwang)) {
		error = -ENXIO;
		goto fail1;
	}

	hanwang->data = usb_alloc_coherent(dev, hanwang->features->pkg_len,
					GFP_KERNEL, &hanwang->data_dma);
	if (!hanwang->data) {
		error = -ENOMEM;
		goto fail1;
	}

	hanwang->irq = usb_alloc_urb(0, GFP_KERNEL);
	if (!hanwang->irq) {
		error = -ENOMEM;
		goto fail2;
	}

	hanwang->usbdev = dev;
	hanwang->dev = input_dev;

	usb_make_path(dev, hanwang->phys, sizeof(hanwang->phys));
	strlcat(hanwang->phys, "/input0", sizeof(hanwang->phys));

	strlcpy(hanwang->name, hanwang->features->name, sizeof(hanwang->name));
	input_dev->name = hanwang->name;
	input_dev->phys = hanwang->phys;
	usb_to_input_id(dev, &input_dev->id);
	input_dev->dev.parent = &intf->dev;

	input_set_drvdata(input_dev, hanwang);

	input_dev->open = hanwang_open;
	input_dev->close = hanwang_close;

	for (i = 0; i < ARRAY_SIZE(hw_eventtypes); ++i)
		__set_bit(hw_eventtypes[i], input_dev->evbit);

	for (i = 0; i < ARRAY_SIZE(hw_absevents); ++i)
		__set_bit(hw_absevents[i], input_dev->absbit);

	for (i = 0; i < ARRAY_SIZE(hw_btnevents); ++i)
		__set_bit(hw_btnevents[i], input_dev->keybit);

	for (i = 0; i < ARRAY_SIZE(hw_mscevents); ++i)
		__set_bit(hw_mscevents[i], input_dev->mscbit);

	input_set_abs_params(input_dev, ABS_X,
			     0, hanwang->features->max_x, 4, 0);
	input_set_abs_params(input_dev, ABS_Y,
			     0, hanwang->features->max_y, 4, 0);
	input_set_abs_params(input_dev, ABS_TILT_X,
			     0, hanwang->features->max_tilt_x, 0, 0);
	input_set_abs_params(input_dev, ABS_TILT_Y,
			     0, hanwang->features->max_tilt_y, 0, 0);
	input_set_abs_params(input_dev, ABS_PRESSURE,
			     0, hanwang->features->max_pressure, 0, 0);

	endpoint = &intf->cur_altsetting->endpoint[0].desc;
	usb_fill_int_urb(hanwang->irq, dev,
			usb_rcvintpipe(dev, endpoint->bEndpointAddress),
			hanwang->data, hanwang->features->pkg_len,
			hanwang_irq, hanwang, endpoint->bInterval);
	hanwang->irq->transfer_dma = hanwang->data_dma;
	hanwang->irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	error = input_register_device(hanwang->dev);
	if (error)
		goto fail3;

	usb_set_intfdata(intf, hanwang);

	return 0;

 fail3:	usb_free_urb(hanwang->irq);
 fail2:	usb_free_coherent(dev, hanwang->features->pkg_len,
			hanwang->data, hanwang->data_dma);
 fail1:	input_free_device(input_dev);
	kfree(hanwang);
	return error;

}