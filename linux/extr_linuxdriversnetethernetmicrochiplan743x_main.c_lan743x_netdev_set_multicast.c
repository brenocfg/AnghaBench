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
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lan743x_rfe_set_multicast (struct lan743x_adapter*) ; 
 struct lan743x_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void lan743x_netdev_set_multicast(struct net_device *netdev)
{
	struct lan743x_adapter *adapter = netdev_priv(netdev);

	lan743x_rfe_set_multicast(adapter);
}