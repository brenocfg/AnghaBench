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
typedef  scalar_t__ u8 ;
struct phy_dev {struct net_device** dev; } ;
struct nic {int /*<<< orphan*/  dest_mac_addr; int /*<<< orphan*/  src_mac_addr; scalar_t__ nic_id; struct phy_dev* phy_dev; struct net_device* netdev; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  mtu; int /*<<< orphan*/  flags; int /*<<< orphan*/ * netdev_ops; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_MTU_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IFF_MULTICAST ; 
 scalar_t__ MAX_NIC_TYPE ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEVTYPE (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_setup ; 
 int /*<<< orphan*/  form_mac_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  gdm_netdev_ops ; 
 int /*<<< orphan*/  memset (struct nic*,int /*<<< orphan*/ ,int) ; 
 struct nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  unregister_lte_device (struct phy_dev*) ; 
 int /*<<< orphan*/  validate_mac_address (scalar_t__*) ; 
 int /*<<< orphan*/  wwan_type ; 

int register_lte_device(struct phy_dev *phy_dev,
			struct device *dev, u8 *mac_address)
{
	struct nic *nic;
	struct net_device *net;
	char pdn_dev_name[16];
	int ret = 0;
	u8 index;

	validate_mac_address(mac_address);

	for (index = 0; index < MAX_NIC_TYPE; index++) {
		/* Create device name lteXpdnX */
		sprintf(pdn_dev_name, "lte%%dpdn%d", index);

		/* Allocate netdev */
		net = alloc_netdev(sizeof(struct nic), pdn_dev_name,
				   NET_NAME_UNKNOWN, ether_setup);
		if (!net) {
			ret = -ENOMEM;
			goto err;
		}
		net->netdev_ops = &gdm_netdev_ops;
		net->flags &= ~IFF_MULTICAST;
		net->mtu = DEFAULT_MTU_SIZE;

		nic = netdev_priv(net);
		memset(nic, 0, sizeof(struct nic));
		nic->netdev = net;
		nic->phy_dev = phy_dev;
		nic->nic_id = index;

		form_mac_address(net->dev_addr,
				 nic->src_mac_addr,
				 nic->dest_mac_addr,
				 mac_address,
				 index);

		SET_NETDEV_DEV(net, dev);
		SET_NETDEV_DEVTYPE(net, &wwan_type);

		ret = register_netdev(net);
		if (ret)
			goto err;

		netif_carrier_on(net);

		phy_dev->dev[index] = net;
	}

	return 0;

err:
	unregister_lte_device(phy_dev);

	return ret;
}