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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct enic {int /*<<< orphan*/  devcmd_lock; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int enic_add_vlan (struct enic*,int /*<<< orphan*/ ) ; 
 struct enic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int enic_vlan_rx_add_vid(struct net_device *netdev, __be16 proto, u16 vid)
{
	struct enic *enic = netdev_priv(netdev);
	int err;

	spin_lock_bh(&enic->devcmd_lock);
	err = enic_add_vlan(enic, vid);
	spin_unlock_bh(&enic->devcmd_lock);

	return err;
}