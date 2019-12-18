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
struct port_info {int eth_flags; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct adapter {int eth_flags; } ;

/* Variables and functions */
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 cxgb4_get_priv_flags(struct net_device *netdev)
{
	struct port_info *pi = netdev_priv(netdev);
	struct adapter *adapter = pi->adapter;

	return (adapter->eth_flags | pi->eth_flags);
}