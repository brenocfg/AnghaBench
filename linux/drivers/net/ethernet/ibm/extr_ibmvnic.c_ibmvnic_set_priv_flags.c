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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ibmvnic_adapter {int priv_flags; } ;

/* Variables and functions */
 int IBMVNIC_USE_SERVER_MAXES ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ibmvnic_set_priv_flags(struct net_device *netdev, u32 flags)
{
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);
	bool which_maxes = !!(flags & IBMVNIC_USE_SERVER_MAXES);

	if (which_maxes)
		adapter->priv_flags |= IBMVNIC_USE_SERVER_MAXES;
	else
		adapter->priv_flags &= ~IBMVNIC_USE_SERVER_MAXES;

	return 0;
}