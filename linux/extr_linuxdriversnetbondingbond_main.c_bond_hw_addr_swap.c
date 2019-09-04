#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct slave {int /*<<< orphan*/  dev; } ;
struct bonding {TYPE_1__* dev; } ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  bond_hw_addr_flush (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_mc_sync (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dev_set_allmulti (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_set_promiscuity (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_uc_sync (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  netif_addr_lock_bh (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_addr_unlock_bh (TYPE_1__*) ; 

__attribute__((used)) static void bond_hw_addr_swap(struct bonding *bond, struct slave *new_active,
			      struct slave *old_active)
{
	if (old_active) {
		if (bond->dev->flags & IFF_PROMISC)
			dev_set_promiscuity(old_active->dev, -1);

		if (bond->dev->flags & IFF_ALLMULTI)
			dev_set_allmulti(old_active->dev, -1);

		bond_hw_addr_flush(bond->dev, old_active->dev);
	}

	if (new_active) {
		/* FIXME: Signal errors upstream. */
		if (bond->dev->flags & IFF_PROMISC)
			dev_set_promiscuity(new_active->dev, 1);

		if (bond->dev->flags & IFF_ALLMULTI)
			dev_set_allmulti(new_active->dev, 1);

		netif_addr_lock_bh(bond->dev);
		dev_uc_sync(new_active->dev, bond->dev);
		dev_mc_sync(new_active->dev, bond->dev);
		netif_addr_unlock_bh(bond->dev);
	}
}