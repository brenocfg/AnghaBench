#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sockaddr_storage {int /*<<< orphan*/  ss_family; int /*<<< orphan*/ * __data; } ;
struct sockaddr {int dummy; } ;
struct slave {TYPE_3__* dev; } ;
struct TYPE_5__ {scalar_t__ rlb_promisc_timeout_counter; scalar_t__ primary_is_promisc; } ;
struct bonding {TYPE_2__* dev; int /*<<< orphan*/  curr_active_slave; TYPE_1__ alb_info; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr_len; int /*<<< orphan*/ * dev_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/ * dev_addr; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ BOND_MODE (struct bonding*) ; 
 scalar_t__ BOND_MODE_TLB ; 
 int MAX_ADDR_LEN ; 
 int /*<<< orphan*/  alb_fasten_mac_swap (struct bonding*,struct slave*,struct slave*) ; 
 int /*<<< orphan*/  alb_send_learning_packets (struct slave*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  alb_set_slave_mac_addr (struct slave*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alb_swap_mac_addr (struct slave*,struct slave*) ; 
 int /*<<< orphan*/  bond_has_slaves (struct bonding*) ; 
 int /*<<< orphan*/  bond_hw_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct slave* bond_slave_has_mac (struct bonding*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_mac_address (TYPE_3__*,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_promiscuity (TYPE_3__*,int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct slave*) ; 
 struct slave* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlb_clear_slave (struct bonding*,struct slave*,int) ; 

void bond_alb_handle_active_change(struct bonding *bond, struct slave *new_slave)
{
	struct slave *swap_slave;
	struct slave *curr_active;

	curr_active = rtnl_dereference(bond->curr_active_slave);
	if (curr_active == new_slave)
		return;

	if (curr_active && bond->alb_info.primary_is_promisc) {
		dev_set_promiscuity(curr_active->dev, -1);
		bond->alb_info.primary_is_promisc = 0;
		bond->alb_info.rlb_promisc_timeout_counter = 0;
	}

	swap_slave = curr_active;
	rcu_assign_pointer(bond->curr_active_slave, new_slave);

	if (!new_slave || !bond_has_slaves(bond))
		return;

	/* set the new curr_active_slave to the bonds mac address
	 * i.e. swap mac addresses of old curr_active_slave and new curr_active_slave
	 */
	if (!swap_slave)
		swap_slave = bond_slave_has_mac(bond, bond->dev->dev_addr);

	/* Arrange for swap_slave and new_slave to temporarily be
	 * ignored so we can mess with their MAC addresses without
	 * fear of interference from transmit activity.
	 */
	if (swap_slave)
		tlb_clear_slave(bond, swap_slave, 1);
	tlb_clear_slave(bond, new_slave, 1);

	/* in TLB mode, the slave might flip down/up with the old dev_addr,
	 * and thus filter bond->dev_addr's packets, so force bond's mac
	 */
	if (BOND_MODE(bond) == BOND_MODE_TLB) {
		struct sockaddr_storage ss;
		u8 tmp_addr[MAX_ADDR_LEN];

		bond_hw_addr_copy(tmp_addr, new_slave->dev->dev_addr,
				  new_slave->dev->addr_len);

		bond_hw_addr_copy(ss.__data, bond->dev->dev_addr,
				  bond->dev->addr_len);
		ss.ss_family = bond->dev->type;
		/* we don't care if it can't change its mac, best effort */
		dev_set_mac_address(new_slave->dev, (struct sockaddr *)&ss,
				    NULL);

		bond_hw_addr_copy(new_slave->dev->dev_addr, tmp_addr,
				  new_slave->dev->addr_len);
	}

	/* curr_active_slave must be set before calling alb_swap_mac_addr */
	if (swap_slave) {
		/* swap mac address */
		alb_swap_mac_addr(swap_slave, new_slave);
		alb_fasten_mac_swap(bond, swap_slave, new_slave);
	} else {
		/* set the new_slave to the bond mac address */
		alb_set_slave_mac_addr(new_slave, bond->dev->dev_addr,
				       bond->dev->addr_len);
		alb_send_learning_packets(new_slave, bond->dev->dev_addr,
					  false);
	}
}