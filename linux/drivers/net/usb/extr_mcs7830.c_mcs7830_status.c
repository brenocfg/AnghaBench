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
typedef  int u8 ;
struct usbnet {int /*<<< orphan*/  net; } ;
struct urb {int* transfer_buffer; int actual_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbnet_link_change (struct usbnet*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcs7830_status(struct usbnet *dev, struct urb *urb)
{
	u8 *buf = urb->transfer_buffer;
	bool link, link_changed;

	if (urb->actual_length < 16)
		return;

	link = !(buf[1] == 0x20);
	link_changed = netif_carrier_ok(dev->net) != link;
	if (link_changed) {
		usbnet_link_change(dev, link, 0);
		netdev_dbg(dev->net, "Link Status is: %d\n", link);
	}
}