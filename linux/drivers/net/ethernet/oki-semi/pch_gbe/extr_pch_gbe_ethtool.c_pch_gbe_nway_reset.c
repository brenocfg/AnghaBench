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
struct pch_gbe_adapter {int /*<<< orphan*/  mii; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int mii_nway_restart (int /*<<< orphan*/ *) ; 
 struct pch_gbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int pch_gbe_nway_reset(struct net_device *netdev)
{
	struct pch_gbe_adapter *adapter = netdev_priv(netdev);

	return mii_nway_restart(&adapter->mii);
}