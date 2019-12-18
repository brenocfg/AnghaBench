#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {scalar_t__ minor; int /*<<< orphan*/  dev; struct usb_host_interface* cur_altsetting; } ;
struct usb_host_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_5__ {void* bMaxPacketSize0; int /*<<< orphan*/  bcdDevice; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_1__ descriptor; } ;
struct ld_usb {int interrupt_in_endpoint_size; TYPE_2__* interrupt_out_endpoint; scalar_t__ interrupt_out_interval; TYPE_2__* interrupt_in_endpoint; scalar_t__ interrupt_in_interval; void* interrupt_out_urb; int /*<<< orphan*/  interrupt_out_buffer; void* interrupt_out_endpoint_size; void* interrupt_in_urb; void* interrupt_in_buffer; int /*<<< orphan*/  ring_buffer; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  read_wait; struct usb_interface* intf; int /*<<< orphan*/  rbsl; int /*<<< orphan*/  mutex; } ;
struct TYPE_6__ {scalar_t__ bInterval; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int USB_DEVICE_ID_LD_CASSY ; 
 int USB_DEVICE_ID_LD_COM3LAB ; 
 scalar_t__ USB_LD_MINOR_BASE ; 
 int /*<<< orphan*/  USB_MAJOR ; 
 int USB_VENDOR_ID_LD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc_array (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 struct ld_usb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ld_usb_class ; 
 int /*<<< orphan*/  ld_usb_delete (struct ld_usb*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ min_interrupt_in_interval ; 
 scalar_t__ min_interrupt_out_interval ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_buffer_size ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* usb_endpoint_maxp (TYPE_2__*) ; 
 int usb_find_last_int_in_endpoint (struct usb_host_interface*,TYPE_2__**) ; 
 int usb_find_last_int_out_endpoint (struct usb_host_interface*,TYPE_2__**) ; 
 int usb_register_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct ld_usb*) ; 
 int /*<<< orphan*/  usb_string (struct usb_device*,int,char*,int) ; 
 int /*<<< orphan*/  write_buffer_size ; 

__attribute__((used)) static int ld_usb_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct ld_usb *dev = NULL;
	struct usb_host_interface *iface_desc;
	char *buffer;
	int retval = -ENOMEM;
	int res;

	/* allocate memory for our device state and initialize it */

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		goto exit;
	mutex_init(&dev->mutex);
	spin_lock_init(&dev->rbsl);
	dev->intf = intf;
	init_waitqueue_head(&dev->read_wait);
	init_waitqueue_head(&dev->write_wait);

	/* workaround for early firmware versions on fast computers */
	if ((le16_to_cpu(udev->descriptor.idVendor) == USB_VENDOR_ID_LD) &&
	    ((le16_to_cpu(udev->descriptor.idProduct) == USB_DEVICE_ID_LD_CASSY) ||
	     (le16_to_cpu(udev->descriptor.idProduct) == USB_DEVICE_ID_LD_COM3LAB)) &&
	    (le16_to_cpu(udev->descriptor.bcdDevice) <= 0x103)) {
		buffer = kmalloc(256, GFP_KERNEL);
		if (!buffer)
			goto error;
		/* usb_string makes SETUP+STALL to leave always ControlReadLoop */
		usb_string(udev, 255, buffer, 256);
		kfree(buffer);
	}

	iface_desc = intf->cur_altsetting;

	res = usb_find_last_int_in_endpoint(iface_desc,
			&dev->interrupt_in_endpoint);
	if (res) {
		dev_err(&intf->dev, "Interrupt in endpoint not found\n");
		retval = res;
		goto error;
	}

	res = usb_find_last_int_out_endpoint(iface_desc,
			&dev->interrupt_out_endpoint);
	if (res)
		dev_warn(&intf->dev, "Interrupt out endpoint not found (using control endpoint instead)\n");

	dev->interrupt_in_endpoint_size = usb_endpoint_maxp(dev->interrupt_in_endpoint);
	dev->ring_buffer = kcalloc(ring_buffer_size,
			sizeof(size_t) + dev->interrupt_in_endpoint_size,
			GFP_KERNEL);
	if (!dev->ring_buffer)
		goto error;
	dev->interrupt_in_buffer = kmalloc(dev->interrupt_in_endpoint_size, GFP_KERNEL);
	if (!dev->interrupt_in_buffer)
		goto error;
	dev->interrupt_in_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->interrupt_in_urb)
		goto error;
	dev->interrupt_out_endpoint_size = dev->interrupt_out_endpoint ? usb_endpoint_maxp(dev->interrupt_out_endpoint) :
									 udev->descriptor.bMaxPacketSize0;
	dev->interrupt_out_buffer =
		kmalloc_array(write_buffer_size,
			      dev->interrupt_out_endpoint_size, GFP_KERNEL);
	if (!dev->interrupt_out_buffer)
		goto error;
	dev->interrupt_out_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->interrupt_out_urb)
		goto error;
	dev->interrupt_in_interval = min_interrupt_in_interval > dev->interrupt_in_endpoint->bInterval ? min_interrupt_in_interval : dev->interrupt_in_endpoint->bInterval;
	if (dev->interrupt_out_endpoint)
		dev->interrupt_out_interval = min_interrupt_out_interval > dev->interrupt_out_endpoint->bInterval ? min_interrupt_out_interval : dev->interrupt_out_endpoint->bInterval;

	/* we can register the device now, as it is ready */
	usb_set_intfdata(intf, dev);

	retval = usb_register_dev(intf, &ld_usb_class);
	if (retval) {
		/* something prevented us from registering this driver */
		dev_err(&intf->dev, "Not able to get a minor for this device.\n");
		usb_set_intfdata(intf, NULL);
		goto error;
	}

	/* let the user know what node this device is now attached to */
	dev_info(&intf->dev, "LD USB Device #%d now attached to major %d minor %d\n",
		(intf->minor - USB_LD_MINOR_BASE), USB_MAJOR, intf->minor);

exit:
	return retval;

error:
	ld_usb_delete(dev);

	return retval;
}