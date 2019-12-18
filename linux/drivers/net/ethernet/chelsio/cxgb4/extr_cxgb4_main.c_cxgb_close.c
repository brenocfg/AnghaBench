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
struct port_info {struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct adapter {int /*<<< orphan*/  pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxgb4_dcb_reset (struct net_device*) ; 
 int /*<<< orphan*/  dcb_tx_queue_prio_enable (struct net_device*,int) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int t4_enable_pi_params (struct adapter*,int /*<<< orphan*/ ,struct port_info*,int,int,int) ; 

__attribute__((used)) static int cxgb_close(struct net_device *dev)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;
	int ret;

	netif_tx_stop_all_queues(dev);
	netif_carrier_off(dev);
	ret = t4_enable_pi_params(adapter, adapter->pf, pi,
				  false, false, false);
#ifdef CONFIG_CHELSIO_T4_DCB
	cxgb4_dcb_reset(dev);
	dcb_tx_queue_prio_enable(dev, false);
#endif
	return ret;
}