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
struct usbnet {int hard_mtu; int rx_urb_size; int maxpacket; } ;
struct net_device {int hard_header_len; int mtu; } ;

/* Variables and functions */
 int EDOM ; 
 struct usbnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  usbnet_pause_rx (struct usbnet*) ; 
 int /*<<< orphan*/  usbnet_resume_rx (struct usbnet*) ; 
 int /*<<< orphan*/  usbnet_unlink_rx_urbs (struct usbnet*) ; 
 int /*<<< orphan*/  usbnet_update_max_qlen (struct usbnet*) ; 

int usbnet_change_mtu (struct net_device *net, int new_mtu)
{
	struct usbnet	*dev = netdev_priv(net);
	int		ll_mtu = new_mtu + net->hard_header_len;
	int		old_hard_mtu = dev->hard_mtu;
	int		old_rx_urb_size = dev->rx_urb_size;

	// no second zero-length packet read wanted after mtu-sized packets
	if ((ll_mtu % dev->maxpacket) == 0)
		return -EDOM;
	net->mtu = new_mtu;

	dev->hard_mtu = net->mtu + net->hard_header_len;
	if (dev->rx_urb_size == old_hard_mtu) {
		dev->rx_urb_size = dev->hard_mtu;
		if (dev->rx_urb_size > old_rx_urb_size) {
			usbnet_pause_rx(dev);
			usbnet_unlink_rx_urbs(dev);
			usbnet_resume_rx(dev);
		}
	}

	/* max qlen depend on hard_mtu and rx_urb_size */
	usbnet_update_max_qlen(dev);

	return 0;
}