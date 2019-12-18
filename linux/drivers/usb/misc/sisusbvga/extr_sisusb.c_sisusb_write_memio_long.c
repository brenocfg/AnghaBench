#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct sisusb_usb_data {int dummy; } ;
struct sisusb_packet {int address; int header; int data; } ;

/* Variables and functions */
 int sisusb_send_packet (struct sisusb_usb_data*,int,struct sisusb_packet*) ; 

__attribute__((used)) static int sisusb_write_memio_long(struct sisusb_usb_data *sisusb, int type,
		u32 addr, u32 data)
{
	struct sisusb_packet packet;
	int ret = 0;

	packet.address = addr & ~3;

	switch (addr & 3) {
	case 0:
		packet.header  = (type << 6) | 0x000f;
		packet.data    = data;
		ret = sisusb_send_packet(sisusb, 10, &packet);
		break;
	case 1:
		packet.header  = (type << 6) | 0x000e;
		packet.data    = data << 8;
		ret = sisusb_send_packet(sisusb, 10, &packet);
		packet.header  = (type << 6) | 0x0001;
		packet.address = (addr & ~3) + 4;
		packet.data    = data >> 24;
		ret |= sisusb_send_packet(sisusb, 10, &packet);
		break;
	case 2:
		packet.header  = (type << 6) | 0x000c;
		packet.data    = data << 16;
		ret = sisusb_send_packet(sisusb, 10, &packet);
		packet.header  = (type << 6) | 0x0003;
		packet.address = (addr & ~3) + 4;
		packet.data    = data >> 16;
		ret |= sisusb_send_packet(sisusb, 10, &packet);
		break;
	case 3:
		packet.header  = (type << 6) | 0x0008;
		packet.data    = data << 24;
		ret = sisusb_send_packet(sisusb, 10, &packet);
		packet.header  = (type << 6) | 0x0007;
		packet.address = (addr & ~3) + 4;
		packet.data    = data >> 8;
		ret |= sisusb_send_packet(sisusb, 10, &packet);
	}

	return ret;
}