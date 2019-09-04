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
struct usb_host_interface {TYPE_5__* endpoint; } ;
struct TYPE_7__ {int width; } ;
struct gspca_dev {int /*<<< orphan*/  iface; TYPE_6__* dev; TYPE_1__ pixfmt; } ;
struct TYPE_12__ {TYPE_3__* actconfig; } ;
struct TYPE_10__ {int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_11__ {TYPE_4__ desc; } ;
struct TYPE_9__ {TYPE_2__** intf_cache; } ;
struct TYPE_8__ {struct usb_host_interface* altsetting; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int usb_set_interface (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sd_isoc_nego(struct gspca_dev *gspca_dev)
{
	int ret, packet_size, min_packet_size;
	struct usb_host_interface *alt;

	switch (gspca_dev->pixfmt.width) {
	case 160:
		min_packet_size = 200;
		break;
	case 176:
		min_packet_size = 266;
		break;
	default:
		min_packet_size = 400;
		break;
	}

	alt = &gspca_dev->dev->actconfig->intf_cache[0]->altsetting[1];
	packet_size = le16_to_cpu(alt->endpoint[0].desc.wMaxPacketSize);
	if (packet_size <= min_packet_size)
		return -EIO;

	packet_size -= 100;
	if (packet_size < min_packet_size)
		packet_size = min_packet_size;
	alt->endpoint[0].desc.wMaxPacketSize = cpu_to_le16(packet_size);

	ret = usb_set_interface(gspca_dev->dev, gspca_dev->iface, 1);
	if (ret < 0)
		pr_err("set alt 1 err %d\n", ret);

	return ret;
}