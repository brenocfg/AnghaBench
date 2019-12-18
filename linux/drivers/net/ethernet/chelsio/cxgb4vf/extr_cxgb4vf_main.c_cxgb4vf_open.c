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
struct port_info {int /*<<< orphan*/  port_id; int /*<<< orphan*/  vlan_id; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct adapter {int flags; scalar_t__ open_device_map; } ;

/* Variables and functions */
 int CXGB4VF_FW_OK ; 
 int ENXIO ; 
 int /*<<< orphan*/  adapter_down (struct adapter*) ; 
 int adapter_up (struct adapter*) ; 
 int link_start (struct net_device*) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  t4vf_get_vf_vlan_acl (struct adapter*) ; 
 int t4vf_update_port_info (struct port_info*) ; 

__attribute__((used)) static int cxgb4vf_open(struct net_device *dev)
{
	int err;
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;

	/*
	 * If we don't have a connection to the firmware there's nothing we
	 * can do.
	 */
	if (!(adapter->flags & CXGB4VF_FW_OK))
		return -ENXIO;

	/*
	 * If this is the first interface that we're opening on the "adapter",
	 * bring the "adapter" up now.
	 */
	if (adapter->open_device_map == 0) {
		err = adapter_up(adapter);
		if (err)
			return err;
	}

	/* It's possible that the basic port information could have
	 * changed since we first read it.
	 */
	err = t4vf_update_port_info(pi);
	if (err < 0)
		return err;

	/*
	 * Note that this interface is up and start everything up ...
	 */
	err = link_start(dev);
	if (err)
		goto err_unwind;

	pi->vlan_id = t4vf_get_vf_vlan_acl(adapter);

	netif_tx_start_all_queues(dev);
	set_bit(pi->port_id, &adapter->open_device_map);
	return 0;

err_unwind:
	if (adapter->open_device_map == 0)
		adapter_down(adapter);
	return err;
}