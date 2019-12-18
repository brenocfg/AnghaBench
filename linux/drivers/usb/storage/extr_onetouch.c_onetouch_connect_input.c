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
struct usb_onetouch {int /*<<< orphan*/  data_dma; int /*<<< orphan*/  data; TYPE_6__* irq; struct input_dev* dev; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; struct usb_device* udev; } ;
struct TYPE_10__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_3__* endpoint; TYPE_2__ desc; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_12__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {char* product; int /*<<< orphan*/  dev; TYPE_4__ descriptor; scalar_t__ manufacturer; } ;
struct us_data {int /*<<< orphan*/  suspend_resume_hook; struct usb_onetouch* extra; int /*<<< orphan*/  extra_destructor; TYPE_1__* pusb_intf; struct usb_device* pusb_dev; } ;
struct TYPE_13__ {int /*<<< orphan*/ * parent; } ;
struct input_dev {int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; TYPE_5__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;
struct TYPE_14__ {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_11__ {struct usb_endpoint_descriptor desc; } ;
struct TYPE_9__ {struct usb_host_interface* cur_altsetting; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ONETOUCH_BUTTON ; 
 int /*<<< orphan*/  ONETOUCH_PKT_LEN ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct usb_onetouch*) ; 
 int /*<<< orphan*/  kfree (struct usb_onetouch*) ; 
 struct usb_onetouch* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onetouch_release_input ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_alloc_coherent (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_6__* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_endpoint_is_int_in (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_6__*,struct usb_device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct usb_onetouch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_coherent (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_6__*) ; 
 int /*<<< orphan*/  usb_make_path (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int usb_maxpacket (struct usb_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_onetouch_close ; 
 int /*<<< orphan*/  usb_onetouch_irq ; 
 int /*<<< orphan*/  usb_onetouch_open ; 
 int /*<<< orphan*/  usb_onetouch_pm_hook ; 
 int /*<<< orphan*/  usb_pipeout (int) ; 
 int usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_to_input_id (struct usb_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int onetouch_connect_input(struct us_data *ss)
{
	struct usb_device *udev = ss->pusb_dev;
	struct usb_host_interface *interface;
	struct usb_endpoint_descriptor *endpoint;
	struct usb_onetouch *onetouch;
	struct input_dev *input_dev;
	int pipe, maxp;
	int error = -ENOMEM;

	interface = ss->pusb_intf->cur_altsetting;

	if (interface->desc.bNumEndpoints != 3)
		return -ENODEV;

	endpoint = &interface->endpoint[2].desc;
	if (!usb_endpoint_is_int_in(endpoint))
		return -ENODEV;

	pipe = usb_rcvintpipe(udev, endpoint->bEndpointAddress);
	maxp = usb_maxpacket(udev, pipe, usb_pipeout(pipe));
	maxp = min(maxp, ONETOUCH_PKT_LEN);

	onetouch = kzalloc(sizeof(struct usb_onetouch), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!onetouch || !input_dev)
		goto fail1;

	onetouch->data = usb_alloc_coherent(udev, ONETOUCH_PKT_LEN,
					    GFP_KERNEL, &onetouch->data_dma);
	if (!onetouch->data)
		goto fail1;

	onetouch->irq = usb_alloc_urb(0, GFP_KERNEL);
	if (!onetouch->irq)
		goto fail2;

	onetouch->udev = udev;
	onetouch->dev = input_dev;

	if (udev->manufacturer)
		strlcpy(onetouch->name, udev->manufacturer,
			sizeof(onetouch->name));
	if (udev->product) {
		if (udev->manufacturer)
			strlcat(onetouch->name, " ", sizeof(onetouch->name));
		strlcat(onetouch->name, udev->product, sizeof(onetouch->name));
	}

	if (!strlen(onetouch->name))
		snprintf(onetouch->name, sizeof(onetouch->name),
			 "Maxtor Onetouch %04x:%04x",
			 le16_to_cpu(udev->descriptor.idVendor),
			 le16_to_cpu(udev->descriptor.idProduct));

	usb_make_path(udev, onetouch->phys, sizeof(onetouch->phys));
	strlcat(onetouch->phys, "/input0", sizeof(onetouch->phys));

	input_dev->name = onetouch->name;
	input_dev->phys = onetouch->phys;
	usb_to_input_id(udev, &input_dev->id);
	input_dev->dev.parent = &udev->dev;

	set_bit(EV_KEY, input_dev->evbit);
	set_bit(ONETOUCH_BUTTON, input_dev->keybit);
	clear_bit(0, input_dev->keybit);

	input_set_drvdata(input_dev, onetouch);

	input_dev->open = usb_onetouch_open;
	input_dev->close = usb_onetouch_close;

	usb_fill_int_urb(onetouch->irq, udev, pipe, onetouch->data, maxp,
			 usb_onetouch_irq, onetouch, endpoint->bInterval);
	onetouch->irq->transfer_dma = onetouch->data_dma;
	onetouch->irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	ss->extra_destructor = onetouch_release_input;
	ss->extra = onetouch;
#ifdef CONFIG_PM
	ss->suspend_resume_hook = usb_onetouch_pm_hook;
#endif

	error = input_register_device(onetouch->dev);
	if (error)
		goto fail3;

	return 0;

 fail3:	usb_free_urb(onetouch->irq);
 fail2:	usb_free_coherent(udev, ONETOUCH_PKT_LEN,
			  onetouch->data, onetouch->data_dma);
 fail1:	kfree(onetouch);
	input_free_device(input_dev);
	return error;
}