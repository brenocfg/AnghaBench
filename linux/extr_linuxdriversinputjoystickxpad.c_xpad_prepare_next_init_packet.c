#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xboxone_init_packet {scalar_t__ idVendor; scalar_t__ idProduct; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct usb_xpad {scalar_t__ xtype; scalar_t__ init_seq; int /*<<< orphan*/  odata_serial; scalar_t__* odata; TYPE_3__* irq_out; TYPE_2__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  transfer_buffer_length; } ;
struct TYPE_4__ {scalar_t__ vendor; scalar_t__ product; } ;
struct TYPE_5__ {TYPE_1__ id; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (struct xboxone_init_packet*) ; 
 scalar_t__ XTYPE_XBOXONE ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xboxone_init_packet* xboxone_init_packets ; 

__attribute__((used)) static bool xpad_prepare_next_init_packet(struct usb_xpad *xpad)
{
	const struct xboxone_init_packet *init_packet;

	if (xpad->xtype != XTYPE_XBOXONE)
		return false;

	/* Perform initialization sequence for Xbox One pads that require it */
	while (xpad->init_seq < ARRAY_SIZE(xboxone_init_packets)) {
		init_packet = &xboxone_init_packets[xpad->init_seq++];

		if (init_packet->idVendor != 0 &&
		    init_packet->idVendor != xpad->dev->id.vendor)
			continue;

		if (init_packet->idProduct != 0 &&
		    init_packet->idProduct != xpad->dev->id.product)
			continue;

		/* This packet applies to our device, so prepare to send it */
		memcpy(xpad->odata, init_packet->data, init_packet->len);
		xpad->irq_out->transfer_buffer_length = init_packet->len;

		/* Update packet with current sequence number */
		xpad->odata[2] = xpad->odata_serial++;
		return true;
	}

	return false;
}