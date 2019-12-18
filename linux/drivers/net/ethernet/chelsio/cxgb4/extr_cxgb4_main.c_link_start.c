#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct port_info {TYPE_1__* adapter; int /*<<< orphan*/  link_cfg; int /*<<< orphan*/  tx_chan; int /*<<< orphan*/  smt_idx; int /*<<< orphan*/  xact_addr_filt; int /*<<< orphan*/  viid; } ;
struct net_device {int features; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  mtu; } ;
struct TYPE_4__ {unsigned int pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXGB4_DCB_ENABLED ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int cxgb4_update_mac_filt (struct port_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int t4_enable_pi_params (TYPE_1__*,unsigned int,struct port_info*,int,int,int /*<<< orphan*/ ) ; 
 int t4_link_l1cfg (TYPE_1__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int t4_set_rxmode (TYPE_1__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ; 

__attribute__((used)) static int link_start(struct net_device *dev)
{
	int ret;
	struct port_info *pi = netdev_priv(dev);
	unsigned int mb = pi->adapter->pf;

	/*
	 * We do not set address filters and promiscuity here, the stack does
	 * that step explicitly.
	 */
	ret = t4_set_rxmode(pi->adapter, mb, pi->viid, dev->mtu, -1, -1, -1,
			    !!(dev->features & NETIF_F_HW_VLAN_CTAG_RX), true);
	if (ret == 0)
		ret = cxgb4_update_mac_filt(pi, pi->viid, &pi->xact_addr_filt,
					    dev->dev_addr, true, &pi->smt_idx);
	if (ret == 0)
		ret = t4_link_l1cfg(pi->adapter, mb, pi->tx_chan,
				    &pi->link_cfg);
	if (ret == 0) {
		local_bh_disable();
		ret = t4_enable_pi_params(pi->adapter, mb, pi, true,
					  true, CXGB4_DCB_ENABLED);
		local_bh_enable();
	}

	return ret;
}