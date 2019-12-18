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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct hinic_dev {int /*<<< orphan*/  mgmt_lock; int /*<<< orphan*/  vlan_bitmap; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 scalar_t__ VLAN_N_VID ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv ; 
 scalar_t__ find_next_bit (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int hinic_port_del_mac (struct hinic_dev*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/  const*) ; 
 struct hinic_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct hinic_dev*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_info (struct hinic_dev*,int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int remove_mac_addr(struct net_device *netdev, const u8 *addr)
{
	struct hinic_dev *nic_dev = netdev_priv(netdev);
	u16 vid = 0;
	int err;

	if (!is_valid_ether_addr(addr))
		return -EADDRNOTAVAIL;

	netif_info(nic_dev, drv, netdev, "remove mac addr = %02x %02x %02x %02x %02x %02x\n",
		   addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

	down(&nic_dev->mgmt_lock);

	do {
		err = hinic_port_del_mac(nic_dev, addr, vid);
		if (err) {
			netif_err(nic_dev, drv, netdev,
				  "Failed to delete mac\n");
			break;
		}

		vid = find_next_bit(nic_dev->vlan_bitmap, VLAN_N_VID, vid + 1);
	} while (vid != VLAN_N_VID);

	up(&nic_dev->mgmt_lock);
	return err;
}