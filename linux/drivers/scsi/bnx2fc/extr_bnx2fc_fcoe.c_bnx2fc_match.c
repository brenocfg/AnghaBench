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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2fc_dev_lock ; 
 scalar_t__ bnx2fc_hba_lookup (struct net_device*) ; 
 scalar_t__ is_vlan_dev (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct net_device* vlan_dev_real_dev (struct net_device*) ; 

__attribute__((used)) static bool bnx2fc_match(struct net_device *netdev)
{
	struct net_device *phys_dev = netdev;

	mutex_lock(&bnx2fc_dev_lock);
	if (is_vlan_dev(netdev))
		phys_dev = vlan_dev_real_dev(netdev);

	if (bnx2fc_hba_lookup(phys_dev)) {
		mutex_unlock(&bnx2fc_dev_lock);
		return true;
	}

	mutex_unlock(&bnx2fc_dev_lock);
	return false;
}