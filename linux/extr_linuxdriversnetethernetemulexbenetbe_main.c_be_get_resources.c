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
struct device {int dummy; } ;
struct be_resources {scalar_t__ max_rss_qs; scalar_t__ max_rx_qs; int if_cap_flags; int max_nic_evt_qs; int max_evt_qs; int /*<<< orphan*/  member_0; } ;
struct be_adapter {int need_def_rxq; int /*<<< orphan*/  cfg_num_rx_irqs; int /*<<< orphan*/  cfg_num_tx_irqs; struct be_resources res; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int BE_IF_FLAGS_DEFQ_RSS ; 
 scalar_t__ BEx_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  BEx_get_resources (struct be_adapter*,struct be_resources*) ; 
 int be_cmd_get_func_config (struct be_adapter*,struct be_resources*) ; 
 int be_if_cap_flags (struct be_adapter*) ; 
 int /*<<< orphan*/  be_max_mc (struct be_adapter*) ; 
 int /*<<< orphan*/  be_max_nic_eqs (struct be_adapter*) ; 
 int /*<<< orphan*/  be_max_qp_irqs (struct be_adapter*) ; 
 int /*<<< orphan*/  be_max_rss (struct be_adapter*) ; 
 int /*<<< orphan*/  be_max_rxqs (struct be_adapter*) ; 
 int /*<<< orphan*/  be_max_txqs (struct be_adapter*) ; 
 int /*<<< orphan*/  be_max_uc (struct be_adapter*) ; 
 int /*<<< orphan*/  be_max_vfs (struct be_adapter*) ; 
 int /*<<< orphan*/  be_max_vlans (struct be_adapter*) ; 
 scalar_t__ be_roce_supported (struct be_adapter*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_get_num_default_rss_queues () ; 
 int /*<<< orphan*/  u16 ; 

__attribute__((used)) static int be_get_resources(struct be_adapter *adapter)
{
	struct device *dev = &adapter->pdev->dev;
	struct be_resources res = {0};
	int status;

	/* For Lancer, SH etc read per-function resource limits from FW.
	 * GET_FUNC_CONFIG returns per function guaranteed limits.
	 * GET_PROFILE_CONFIG returns PCI-E related limits PF-pool limits
	 */
	if (BEx_chip(adapter)) {
		BEx_get_resources(adapter, &res);
	} else {
		status = be_cmd_get_func_config(adapter, &res);
		if (status)
			return status;

		/* If a deafault RXQ must be created, we'll use up one RSSQ*/
		if (res.max_rss_qs && res.max_rss_qs == res.max_rx_qs &&
		    !(res.if_cap_flags & BE_IF_FLAGS_DEFQ_RSS))
			res.max_rss_qs -= 1;
	}

	/* If RoCE is supported stash away half the EQs for RoCE */
	res.max_nic_evt_qs = be_roce_supported(adapter) ?
				res.max_evt_qs / 2 : res.max_evt_qs;
	adapter->res = res;

	/* If FW supports RSS default queue, then skip creating non-RSS
	 * queue for non-IP traffic.
	 */
	adapter->need_def_rxq = (be_if_cap_flags(adapter) &
				 BE_IF_FLAGS_DEFQ_RSS) ? 0 : 1;

	dev_info(dev, "Max: txqs %d, rxqs %d, rss %d, eqs %d, vfs %d\n",
		 be_max_txqs(adapter), be_max_rxqs(adapter),
		 be_max_rss(adapter), be_max_nic_eqs(adapter),
		 be_max_vfs(adapter));
	dev_info(dev, "Max: uc-macs %d, mc-macs %d, vlans %d\n",
		 be_max_uc(adapter), be_max_mc(adapter),
		 be_max_vlans(adapter));

	/* Ensure RX and TX queues are created in pairs at init time */
	adapter->cfg_num_rx_irqs =
				min_t(u16, netif_get_num_default_rss_queues(),
				      be_max_qp_irqs(adapter));
	adapter->cfg_num_tx_irqs = adapter->cfg_num_rx_irqs;
	return 0;
}