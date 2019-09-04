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
struct port_info {int /*<<< orphan*/  viid; struct adapter* adapter; } ;
struct net_device {int flags; } ;
struct adapter {int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  __dev_mc_sync (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dev_uc_sync (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb4_mac_sync ; 
 int /*<<< orphan*/  cxgb4_mac_unsync ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int t4_set_rxmode (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 

__attribute__((used)) static int set_rxmode(struct net_device *dev, int mtu, bool sleep_ok)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;

	__dev_uc_sync(dev, cxgb4_mac_sync, cxgb4_mac_unsync);
	__dev_mc_sync(dev, cxgb4_mac_sync, cxgb4_mac_unsync);

	return t4_set_rxmode(adapter, adapter->mbox, pi->viid, mtu,
			     (dev->flags & IFF_PROMISC) ? 1 : 0,
			     (dev->flags & IFF_ALLMULTI) ? 1 : 0, 1, -1,
			     sleep_ok);
}