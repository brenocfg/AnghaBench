#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_serial_port {int /*<<< orphan*/  dev; TYPE_4__* serial; } ;
struct usb_interface {TYPE_3__* cur_altsetting; } ;
struct usb_endpoint_descriptor {scalar_t__ wMaxPacketSize; } ;
struct ftdi_private {int /*<<< orphan*/  max_packet_size; } ;
struct TYPE_8__ {struct usb_interface* interface; } ;
struct TYPE_5__ {unsigned int bNumEndpoints; } ;
struct TYPE_7__ {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct TYPE_6__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 scalar_t__ cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_endpoint_maxp (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_endpoint_num (struct usb_endpoint_descriptor*) ; 
 struct ftdi_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void ftdi_set_max_packet_size(struct usb_serial_port *port)
{
	struct ftdi_private *priv = usb_get_serial_port_data(port);
	struct usb_interface *interface = port->serial->interface;
	struct usb_endpoint_descriptor *ep_desc;
	unsigned num_endpoints;
	unsigned i;

	num_endpoints = interface->cur_altsetting->desc.bNumEndpoints;
	if (!num_endpoints)
		return;

	/*
	 * NOTE: Some customers have programmed FT232R/FT245R devices
	 * with an endpoint size of 0 - not good. In this case, we
	 * want to override the endpoint descriptor setting and use a
	 * value of 64 for wMaxPacketSize.
	 */
	for (i = 0; i < num_endpoints; i++) {
		ep_desc = &interface->cur_altsetting->endpoint[i].desc;
		if (!ep_desc->wMaxPacketSize) {
			ep_desc->wMaxPacketSize = cpu_to_le16(0x40);
			dev_warn(&port->dev, "Overriding wMaxPacketSize on endpoint %d\n",
					usb_endpoint_num(ep_desc));
		}
	}

	/* Set max packet size based on last descriptor. */
	priv->max_packet_size = usb_endpoint_maxp(ep_desc);
}