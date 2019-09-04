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
struct port_info {int /*<<< orphan*/  port_id; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct adapter {scalar_t__ open_device_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  adapter_down (struct adapter*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  t4vf_enable_pi (struct adapter*,struct port_info*,int,int) ; 

__attribute__((used)) static int cxgb4vf_stop(struct net_device *dev)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;

	netif_tx_stop_all_queues(dev);
	netif_carrier_off(dev);
	t4vf_enable_pi(adapter, pi, false, false);

	clear_bit(pi->port_id, &adapter->open_device_map);
	if (adapter->open_device_map == 0)
		adapter_down(adapter);
	return 0;
}