#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_lcd {int /*<<< orphan*/  kref; TYPE_2__* udev; int /*<<< orphan*/  bulk_out_endpointAddr; int /*<<< orphan*/  bulk_in_buffer; int /*<<< orphan*/  bulk_in_size; int /*<<< orphan*/  bulk_in_endpointAddr; struct usb_interface* interface; int /*<<< orphan*/  submitted; int /*<<< orphan*/  io_rwsem; int /*<<< orphan*/  limit_sem; } ;
struct usb_interface {int /*<<< orphan*/  minor; int /*<<< orphan*/  dev; int /*<<< orphan*/  cur_altsetting; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bcdDevice; int /*<<< orphan*/  idProduct; } ;
struct TYPE_4__ {int /*<<< orphan*/  devnum; TYPE_1__ descriptor; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_LCD_CONCURRENT_WRITES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct usb_lcd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_class ; 
 int /*<<< orphan*/  lcd_delete ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_endpoint_maxp (struct usb_endpoint_descriptor*) ; 
 int usb_find_common_endpoints (int /*<<< orphan*/ ,struct usb_endpoint_descriptor**,struct usb_endpoint_descriptor**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* usb_get_dev (int /*<<< orphan*/ ) ; 
 int usb_register_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct usb_lcd*) ; 

__attribute__((used)) static int lcd_probe(struct usb_interface *interface,
		     const struct usb_device_id *id)
{
	struct usb_lcd *dev = NULL;
	struct usb_endpoint_descriptor *bulk_in, *bulk_out;
	int i;
	int retval;

	/* allocate memory for our device state and initialize it */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	kref_init(&dev->kref);
	sema_init(&dev->limit_sem, USB_LCD_CONCURRENT_WRITES);
	init_rwsem(&dev->io_rwsem);
	init_usb_anchor(&dev->submitted);

	dev->udev = usb_get_dev(interface_to_usbdev(interface));
	dev->interface = interface;

	if (le16_to_cpu(dev->udev->descriptor.idProduct) != 0x0001) {
		dev_warn(&interface->dev, "USBLCD model not supported.\n");
		retval = -ENODEV;
		goto error;
	}

	/* set up the endpoint information */
	/* use only the first bulk-in and bulk-out endpoints */
	retval = usb_find_common_endpoints(interface->cur_altsetting,
			&bulk_in, &bulk_out, NULL, NULL);
	if (retval) {
		dev_err(&interface->dev,
			"Could not find both bulk-in and bulk-out endpoints\n");
		goto error;
	}

	dev->bulk_in_size = usb_endpoint_maxp(bulk_in);
	dev->bulk_in_endpointAddr = bulk_in->bEndpointAddress;
	dev->bulk_in_buffer = kmalloc(dev->bulk_in_size, GFP_KERNEL);
	if (!dev->bulk_in_buffer) {
		retval = -ENOMEM;
		goto error;
	}

	dev->bulk_out_endpointAddr = bulk_out->bEndpointAddress;

	/* save our data pointer in this interface device */
	usb_set_intfdata(interface, dev);

	/* we can register the device now, as it is ready */
	retval = usb_register_dev(interface, &lcd_class);
	if (retval) {
		/* something prevented us from registering this driver */
		dev_err(&interface->dev,
			"Not able to get a minor for this device.\n");
		goto error;
	}

	i = le16_to_cpu(dev->udev->descriptor.bcdDevice);

	dev_info(&interface->dev, "USBLCD Version %1d%1d.%1d%1d found "
		 "at address %d\n", (i & 0xF000)>>12, (i & 0xF00)>>8,
		 (i & 0xF0)>>4, (i & 0xF), dev->udev->devnum);

	/* let the user know what node this device is now attached to */
	dev_info(&interface->dev, "USB LCD device now attached to USBLCD-%d\n",
		 interface->minor);
	return 0;

error:
	kref_put(&dev->kref, lcd_delete);
	return retval;
}