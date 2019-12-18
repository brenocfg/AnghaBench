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
struct be_adapter {int update_mc_list; } ;

/* Variables and functions */
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int be_mc_list_update(struct net_device *netdev,
			     const unsigned char *addr)
{
	struct be_adapter *adapter = netdev_priv(netdev);

	adapter->update_mc_list = true;
	return 0;
}