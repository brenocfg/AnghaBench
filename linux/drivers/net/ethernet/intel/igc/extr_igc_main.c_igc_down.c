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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct igc_hw {int dummy; } ;
struct igc_adapter {int num_q_vectors; int /*<<< orphan*/  flags; int /*<<< orphan*/  pdev; scalar_t__ link_duplex; scalar_t__ link_speed; int /*<<< orphan*/  stats64_lock; int /*<<< orphan*/  phy_info_timer; int /*<<< orphan*/  watchdog_timer; TYPE_1__** q_vector; int /*<<< orphan*/  state; struct igc_hw hw; struct net_device* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_FLAG_NEED_LINK_UPDATE ; 
 int /*<<< orphan*/  IGC_FLAG_VLAN_PROMISC ; 
 int /*<<< orphan*/  IGC_RCTL ; 
 int IGC_RCTL_EN ; 
 int /*<<< orphan*/  IGC_TCTL ; 
 int IGC_TCTL_EN ; 
 int /*<<< orphan*/  __IGC_DOWN ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igc_clean_all_rx_rings (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_clean_all_tx_rings (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_irq_disable (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_nfc_filter_exit (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_reset (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_update_stats (struct igc_adapter*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  pci_channel_offline (int /*<<< orphan*/ ) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrfl () ; 

void igc_down(struct igc_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct igc_hw *hw = &adapter->hw;
	u32 tctl, rctl;
	int i = 0;

	set_bit(__IGC_DOWN, &adapter->state);

	/* disable receives in the hardware */
	rctl = rd32(IGC_RCTL);
	wr32(IGC_RCTL, rctl & ~IGC_RCTL_EN);
	/* flush and sleep below */

	igc_nfc_filter_exit(adapter);

	/* set trans_start so we don't get spurious watchdogs during reset */
	netif_trans_update(netdev);

	netif_carrier_off(netdev);
	netif_tx_stop_all_queues(netdev);

	/* disable transmits in the hardware */
	tctl = rd32(IGC_TCTL);
	tctl &= ~IGC_TCTL_EN;
	wr32(IGC_TCTL, tctl);
	/* flush both disables and wait for them to finish */
	wrfl();
	usleep_range(10000, 20000);

	igc_irq_disable(adapter);

	adapter->flags &= ~IGC_FLAG_NEED_LINK_UPDATE;

	for (i = 0; i < adapter->num_q_vectors; i++) {
		if (adapter->q_vector[i]) {
			napi_synchronize(&adapter->q_vector[i]->napi);
			napi_disable(&adapter->q_vector[i]->napi);
		}
	}

	del_timer_sync(&adapter->watchdog_timer);
	del_timer_sync(&adapter->phy_info_timer);

	/* record the stats before reset*/
	spin_lock(&adapter->stats64_lock);
	igc_update_stats(adapter);
	spin_unlock(&adapter->stats64_lock);

	adapter->link_speed = 0;
	adapter->link_duplex = 0;

	if (!pci_channel_offline(adapter->pdev))
		igc_reset(adapter);

	/* clear VLAN promisc flag so VFTA will be updated if necessary */
	adapter->flags &= ~IGC_FLAG_VLAN_PROMISC;

	igc_clean_all_tx_rings(adapter);
	igc_clean_all_rx_rings(adapter);
}