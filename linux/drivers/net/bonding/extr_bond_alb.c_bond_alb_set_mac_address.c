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
struct sockaddr_storage {int /*<<< orphan*/  __data; } ;
struct slave {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  addr_len; } ;
struct TYPE_2__ {scalar_t__ rlb_enabled; } ;
struct bonding {TYPE_1__ alb_info; int /*<<< orphan*/  curr_active_slave; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  alb_fasten_mac_swap (struct bonding*,struct slave*,struct slave*) ; 
 int /*<<< orphan*/  alb_send_learning_packets (struct slave*,int /*<<< orphan*/ ,int) ; 
 int alb_set_mac_address (struct bonding*,void*) ; 
 int /*<<< orphan*/  alb_set_slave_mac_addr (struct slave*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alb_swap_mac_addr (struct slave*,struct slave*) ; 
 int /*<<< orphan*/  bond_hw_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct slave* bond_slave_has_mac (struct bonding*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 struct bonding* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rlb_req_update_slave_clients (struct bonding*,struct slave*) ; 
 struct slave* rtnl_dereference (int /*<<< orphan*/ ) ; 

int bond_alb_set_mac_address(struct net_device *bond_dev, void *addr)
{
	struct bonding *bond = netdev_priv(bond_dev);
	struct sockaddr_storage *ss = addr;
	struct slave *curr_active;
	struct slave *swap_slave;
	int res;

	if (!is_valid_ether_addr(ss->__data))
		return -EADDRNOTAVAIL;

	res = alb_set_mac_address(bond, addr);
	if (res)
		return res;

	bond_hw_addr_copy(bond_dev->dev_addr, ss->__data, bond_dev->addr_len);

	/* If there is no curr_active_slave there is nothing else to do.
	 * Otherwise we'll need to pass the new address to it and handle
	 * duplications.
	 */
	curr_active = rtnl_dereference(bond->curr_active_slave);
	if (!curr_active)
		return 0;

	swap_slave = bond_slave_has_mac(bond, bond_dev->dev_addr);

	if (swap_slave) {
		alb_swap_mac_addr(swap_slave, curr_active);
		alb_fasten_mac_swap(bond, swap_slave, curr_active);
	} else {
		alb_set_slave_mac_addr(curr_active, bond_dev->dev_addr,
				       bond_dev->addr_len);

		alb_send_learning_packets(curr_active,
					  bond_dev->dev_addr, false);
		if (bond->alb_info.rlb_enabled) {
			/* inform clients mac address has changed */
			rlb_req_update_slave_clients(bond, curr_active);
		}
	}

	return 0;
}