#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; scalar_t__ minor; int /*<<< orphan*/ * altsetting; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  iSerialNumber; } ;
struct usb_device {TYPE_1__ descriptor; } ;
struct adu_device {scalar_t__ minor; int /*<<< orphan*/  serial_number; void* interrupt_out_urb; void* interrupt_out_buffer; void* interrupt_in_urb; void* interrupt_in_buffer; void* read_buffer_secondary; void* read_buffer_primary; int /*<<< orphan*/  interrupt_out_endpoint; int /*<<< orphan*/  interrupt_in_endpoint; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  udev; int /*<<< orphan*/  buflock; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 scalar_t__ ADU_MINOR_BASE ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  adu_class ; 
 int /*<<< orphan*/  adu_delete (struct adu_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct adu_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,char,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_endpoint_maxp (int /*<<< orphan*/ ) ; 
 int usb_find_common_endpoints_reverse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int usb_register_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct adu_device*) ; 
 int /*<<< orphan*/  usb_string (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adu_probe(struct usb_interface *interface,
		     const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(interface);
	struct adu_device *dev = NULL;
	int retval = -ENOMEM;
	int in_end_size;
	int out_end_size;
	int res;

	/* allocate memory for our device state and initialize it */
	dev = kzalloc(sizeof(struct adu_device), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	mutex_init(&dev->mtx);
	spin_lock_init(&dev->buflock);
	dev->udev = usb_get_dev(udev);
	init_waitqueue_head(&dev->read_wait);
	init_waitqueue_head(&dev->write_wait);

	res = usb_find_common_endpoints_reverse(&interface->altsetting[0],
			NULL, NULL,
			&dev->interrupt_in_endpoint,
			&dev->interrupt_out_endpoint);
	if (res) {
		dev_err(&interface->dev, "interrupt endpoints not found\n");
		retval = res;
		goto error;
	}

	in_end_size = usb_endpoint_maxp(dev->interrupt_in_endpoint);
	out_end_size = usb_endpoint_maxp(dev->interrupt_out_endpoint);

	dev->read_buffer_primary = kmalloc((4 * in_end_size), GFP_KERNEL);
	if (!dev->read_buffer_primary)
		goto error;

	/* debug code prime the buffer */
	memset(dev->read_buffer_primary, 'a', in_end_size);
	memset(dev->read_buffer_primary + in_end_size, 'b', in_end_size);
	memset(dev->read_buffer_primary + (2 * in_end_size), 'c', in_end_size);
	memset(dev->read_buffer_primary + (3 * in_end_size), 'd', in_end_size);

	dev->read_buffer_secondary = kmalloc((4 * in_end_size), GFP_KERNEL);
	if (!dev->read_buffer_secondary)
		goto error;

	/* debug code prime the buffer */
	memset(dev->read_buffer_secondary, 'e', in_end_size);
	memset(dev->read_buffer_secondary + in_end_size, 'f', in_end_size);
	memset(dev->read_buffer_secondary + (2 * in_end_size), 'g', in_end_size);
	memset(dev->read_buffer_secondary + (3 * in_end_size), 'h', in_end_size);

	dev->interrupt_in_buffer = kmalloc(in_end_size, GFP_KERNEL);
	if (!dev->interrupt_in_buffer)
		goto error;

	/* debug code prime the buffer */
	memset(dev->interrupt_in_buffer, 'i', in_end_size);

	dev->interrupt_in_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->interrupt_in_urb)
		goto error;
	dev->interrupt_out_buffer = kmalloc(out_end_size, GFP_KERNEL);
	if (!dev->interrupt_out_buffer)
		goto error;
	dev->interrupt_out_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->interrupt_out_urb)
		goto error;

	if (!usb_string(udev, udev->descriptor.iSerialNumber, dev->serial_number,
			sizeof(dev->serial_number))) {
		dev_err(&interface->dev, "Could not retrieve serial number\n");
		retval = -EIO;
		goto error;
	}
	dev_dbg(&interface->dev,"serial_number=%s", dev->serial_number);

	/* we can register the device now, as it is ready */
	usb_set_intfdata(interface, dev);

	retval = usb_register_dev(interface, &adu_class);

	if (retval) {
		/* something prevented us from registering this driver */
		dev_err(&interface->dev, "Not able to get a minor for this device.\n");
		usb_set_intfdata(interface, NULL);
		goto error;
	}

	dev->minor = interface->minor;

	/* let the user know what node this device is now attached to */
	dev_info(&interface->dev, "ADU%d %s now attached to /dev/usb/adutux%d\n",
		 le16_to_cpu(udev->descriptor.idProduct), dev->serial_number,
		 (dev->minor - ADU_MINOR_BASE));

	return 0;

error:
	adu_delete(dev);
	return retval;
}