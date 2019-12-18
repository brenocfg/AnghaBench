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
struct usbnet {int /*<<< orphan*/  net; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 struct usbnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int smsc75xx_set_rx_max_frame_length (struct usbnet*,scalar_t__) ; 
 int usbnet_change_mtu (struct net_device*,int) ; 

__attribute__((used)) static int smsc75xx_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct usbnet *dev = netdev_priv(netdev);
	int ret;

	ret = smsc75xx_set_rx_max_frame_length(dev, new_mtu + ETH_HLEN);
	if (ret < 0) {
		netdev_warn(dev->net, "Failed to set mac rx frame length\n");
		return ret;
	}

	return usbnet_change_mtu(netdev, new_mtu);
}