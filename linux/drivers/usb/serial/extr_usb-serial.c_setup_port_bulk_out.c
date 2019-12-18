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
struct usb_serial_port {int bulk_out_size; int /*<<< orphan*/ * bulk_out_buffers; int /*<<< orphan*/  bulk_out_buffer; int /*<<< orphan*/ * write_urbs; int /*<<< orphan*/  write_urb; int /*<<< orphan*/  write_urbs_free; int /*<<< orphan*/  bulk_out_endpointAddress; int /*<<< orphan*/  write_fifo; TYPE_1__* serial; } ;
struct usb_serial_driver {int bulk_out_size; int /*<<< orphan*/  write_bulk_callback; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {struct usb_device* dev; struct usb_serial_driver* type; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ kfifo_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_endpoint_maxp (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_port_bulk_out(struct usb_serial_port *port,
					struct usb_endpoint_descriptor *epd)
{
	struct usb_serial_driver *type = port->serial->type;
	struct usb_device *udev = port->serial->dev;
	int buffer_size;
	int i;

	if (kfifo_alloc(&port->write_fifo, PAGE_SIZE, GFP_KERNEL))
		return -ENOMEM;
	if (type->bulk_out_size)
		buffer_size = type->bulk_out_size;
	else
		buffer_size = usb_endpoint_maxp(epd);
	port->bulk_out_size = buffer_size;
	port->bulk_out_endpointAddress = epd->bEndpointAddress;

	for (i = 0; i < ARRAY_SIZE(port->write_urbs); ++i) {
		set_bit(i, &port->write_urbs_free);
		port->write_urbs[i] = usb_alloc_urb(0, GFP_KERNEL);
		if (!port->write_urbs[i])
			return -ENOMEM;
		port->bulk_out_buffers[i] = kmalloc(buffer_size, GFP_KERNEL);
		if (!port->bulk_out_buffers[i])
			return -ENOMEM;
		usb_fill_bulk_urb(port->write_urbs[i], udev,
				usb_sndbulkpipe(udev, epd->bEndpointAddress),
				port->bulk_out_buffers[i], buffer_size,
				type->write_bulk_callback, port);
	}

	port->write_urb = port->write_urbs[0];
	port->bulk_out_buffer = port->bulk_out_buffers[0];

	return 0;
}