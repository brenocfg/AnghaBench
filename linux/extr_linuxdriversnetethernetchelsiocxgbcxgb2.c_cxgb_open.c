#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {size_t if_port; int /*<<< orphan*/  features; struct adapter* ml_priv; } ;
struct TYPE_2__ {scalar_t__ stats_update_period; } ;
struct adapter {int open_device_map; TYPE_1__ params; int /*<<< orphan*/ * port; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int PORT_MASK ; 
 int /*<<< orphan*/  __set_bit (size_t,int*) ; 
 int cxgb_up (struct adapter*) ; 
 int /*<<< orphan*/  link_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  schedule_mac_stats_update (struct adapter*,scalar_t__) ; 
 int /*<<< orphan*/  t1_vlan_mode (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxgb_open(struct net_device *dev)
{
	int err;
	struct adapter *adapter = dev->ml_priv;
	int other_ports = adapter->open_device_map & PORT_MASK;

	napi_enable(&adapter->napi);
	if (!adapter->open_device_map && (err = cxgb_up(adapter)) < 0) {
		napi_disable(&adapter->napi);
		return err;
	}

	__set_bit(dev->if_port, &adapter->open_device_map);
	link_start(&adapter->port[dev->if_port]);
	netif_start_queue(dev);
	if (!other_ports && adapter->params.stats_update_period)
		schedule_mac_stats_update(adapter,
					  adapter->params.stats_update_period);

	t1_vlan_mode(adapter, dev->features);
	return 0;
}