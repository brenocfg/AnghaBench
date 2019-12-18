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
typedef  char u8 ;
struct usbnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const*) ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int kalmia_send_init_packet (struct usbnet*,char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int const,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static int
kalmia_init_and_get_ethernet_addr(struct usbnet *dev, u8 *ethernet_addr)
{
	static const char init_msg_1[] =
		{ 0x57, 0x50, 0x04, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00,
		0x00, 0x00 };
	static const char init_msg_2[] =
		{ 0x57, 0x50, 0x04, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0xf4,
		0x00, 0x00 };
	static const int buflen = 28;
	char *usb_buf;
	int status;

	usb_buf = kmalloc(buflen, GFP_DMA | GFP_KERNEL);
	if (!usb_buf)
		return -ENOMEM;

	memcpy(usb_buf, init_msg_1, 12);
	status = kalmia_send_init_packet(dev, usb_buf, ARRAY_SIZE(init_msg_1),
					 usb_buf, 24);
	if (status != 0)
		goto out;

	memcpy(usb_buf, init_msg_2, 12);
	status = kalmia_send_init_packet(dev, usb_buf, ARRAY_SIZE(init_msg_2),
					 usb_buf, 28);
	if (status != 0)
		goto out;

	memcpy(ethernet_addr, usb_buf + 10, ETH_ALEN);
out:
	kfree(usb_buf);
	return status;
}