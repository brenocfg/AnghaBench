#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_serial_port {TYPE_2__* write_urb; int /*<<< orphan*/  bulk_out_endpointAddress; TYPE_1__* serial; } ;
struct urb {struct usb_serial_port* context; } ;
struct TYPE_5__ {char* transfer_buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IUU_SET_LED ; 
 int /*<<< orphan*/  get_random_bytes (char*,int) ; 
 int /*<<< orphan*/  iuu_rgbf_fill_buffer (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iuu_rxcmd ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ xmas ; 

__attribute__((used)) static void iuu_led_activity_on(struct urb *urb)
{
	struct usb_serial_port *port = urb->context;
	int result;
	char *buf_ptr = port->write_urb->transfer_buffer;
	*buf_ptr++ = IUU_SET_LED;
	if (xmas) {
		get_random_bytes(buf_ptr, 6);
		*(buf_ptr+7) = 1;
	} else {
		iuu_rgbf_fill_buffer(buf_ptr, 255, 255, 0, 0, 0, 0, 255);
	}

	usb_fill_bulk_urb(port->write_urb, port->serial->dev,
			  usb_sndbulkpipe(port->serial->dev,
					  port->bulk_out_endpointAddress),
			  port->write_urb->transfer_buffer, 8 ,
			  iuu_rxcmd, port);
	result = usb_submit_urb(port->write_urb, GFP_ATOMIC);
}