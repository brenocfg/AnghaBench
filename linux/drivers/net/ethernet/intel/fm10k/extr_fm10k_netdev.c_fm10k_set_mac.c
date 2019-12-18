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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int flags; int /*<<< orphan*/  addr_assign_type; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct fm10k_hw {TYPE_1__ mac; } ;
struct fm10k_intfc {struct fm10k_hw hw; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EAGAIN ; 
 int IFF_UP ; 
 int /*<<< orphan*/  NET_ADDR_RANDOM ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_mbx_lock (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_mbx_unlock (struct fm10k_intfc*) ; 
 scalar_t__ fm10k_uc_sync (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_uc_unsync (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int fm10k_set_mac(struct net_device *dev, void *p)
{
	struct fm10k_intfc *interface = netdev_priv(dev);
	struct fm10k_hw *hw = &interface->hw;
	struct sockaddr *addr = p;
	s32 err = 0;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	if (dev->flags & IFF_UP) {
		/* setting MAC address requires mailbox */
		fm10k_mbx_lock(interface);

		err = fm10k_uc_sync(dev, addr->sa_data);
		if (!err)
			fm10k_uc_unsync(dev, hw->mac.addr);

		fm10k_mbx_unlock(interface);
	}

	if (!err) {
		ether_addr_copy(dev->dev_addr, addr->sa_data);
		ether_addr_copy(hw->mac.addr, addr->sa_data);
		dev->addr_assign_type &= ~NET_ADDR_RANDOM;
	}

	/* if we had a mailbox error suggest trying again */
	return err ? -EAGAIN : 0;
}