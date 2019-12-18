#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_gadget {int /*<<< orphan*/  dev; } ;
struct sockaddr {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {int /*<<< orphan*/  type; TYPE_1__ dev; } ;
struct eth_dev {int /*<<< orphan*/  dev_mac; int /*<<< orphan*/  host_mac; struct usb_gadget* gadget; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  INFO (struct eth_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int dev_set_mac_address (struct net_device*,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct eth_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int gether_register_netdev(struct net_device *net)
{
	struct eth_dev *dev;
	struct usb_gadget *g;
	struct sockaddr sa;
	int status;

	if (!net->dev.parent)
		return -EINVAL;
	dev = netdev_priv(net);
	g = dev->gadget;
	status = register_netdev(net);
	if (status < 0) {
		dev_dbg(&g->dev, "register_netdev failed, %d\n", status);
		return status;
	} else {
		INFO(dev, "HOST MAC %pM\n", dev->host_mac);

		/* two kinds of host-initiated state changes:
		 *  - iff DATA transfer is active, carrier is "on"
		 *  - tx queueing enabled if open *and* carrier is "on"
		 */
		netif_carrier_off(net);
	}
	sa.sa_family = net->type;
	memcpy(sa.sa_data, dev->dev_mac, ETH_ALEN);
	rtnl_lock();
	status = dev_set_mac_address(net, &sa, NULL);
	rtnl_unlock();
	if (status)
		pr_warn("cannot set self ethernet address: %d\n", status);
	else
		INFO(dev, "MAC %pM\n", dev->dev_mac);

	return status;
}