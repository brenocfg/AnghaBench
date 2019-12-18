#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usb_host_interface {TYPE_2__* endpoint; } ;
struct sd {TYPE_3__* sensor; } ;
struct gspca_dev {size_t curr_mode; TYPE_6__* dev; } ;
struct TYPE_12__ {TYPE_5__* actconfig; } ;
struct TYPE_11__ {TYPE_4__** intf_cache; } ;
struct TYPE_10__ {struct usb_host_interface* altsetting; } ;
struct TYPE_9__ {int /*<<< orphan*/ * max_packet_size; } ;
struct TYPE_7__ {int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_8__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv06xx_isoc_init(struct gspca_dev *gspca_dev)
{
	struct usb_host_interface *alt;
	struct sd *sd = (struct sd *) gspca_dev;

	/* Start isoc bandwidth "negotiation" at max isoc bandwidth */
	alt = &gspca_dev->dev->actconfig->intf_cache[0]->altsetting[1];
	alt->endpoint[0].desc.wMaxPacketSize =
		cpu_to_le16(sd->sensor->max_packet_size[gspca_dev->curr_mode]);

	return 0;
}