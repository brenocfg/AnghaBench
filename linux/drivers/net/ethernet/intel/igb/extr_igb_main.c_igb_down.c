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
struct e1000_hw {int dummy; } ;
struct igb_adapter {int num_q_vectors; int /*<<< orphan*/  flags; int /*<<< orphan*/  pdev; scalar_t__ link_duplex; scalar_t__ link_speed; int /*<<< orphan*/  stats64_lock; int /*<<< orphan*/  phy_info_timer; int /*<<< orphan*/  watchdog_timer; TYPE_1__** q_vector; int /*<<< orphan*/  state; struct e1000_hw hw; struct net_device* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_RCTL ; 
 int E1000_RCTL_EN ; 
 int /*<<< orphan*/  E1000_TCTL ; 
 int E1000_TCTL_EN ; 
 int /*<<< orphan*/  IGB_FLAG_NEED_LINK_UPDATE ; 
 int /*<<< orphan*/  IGB_FLAG_VLAN_PROMISC ; 
 int /*<<< orphan*/  __IGB_DOWN ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igb_clean_all_rx_rings (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_clean_all_tx_rings (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_irq_disable (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_nfc_filter_exit (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_reset (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_setup_dca (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_update_stats (struct igb_adapter*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  pci_channel_offline (int /*<<< orphan*/ ) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrfl () ; 

void igb_down(struct igb_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct e1000_hw *hw = &adapter->hw;
	u32 tctl, rctl;
	int i;

	/* signal that we're down so the interrupt handler does not
	 * reschedule our watchdog timer
	 */
	set_bit(__IGB_DOWN, &adapter->state);

	/* disable receives in the hardware */
	rctl = rd32(E1000_RCTL);
	wr32(E1000_RCTL, rctl & ~E1000_RCTL_EN);
	/* flush and sleep below */

	igb_nfc_filter_exit(adapter);

	netif_carrier_off(netdev);
	netif_tx_stop_all_queues(netdev);

	/* disable transmits in the hardware */
	tctl = rd32(E1000_TCTL);
	tctl &= ~E1000_TCTL_EN;
	wr32(E1000_TCTL, tctl);
	/* flush both disables and wait for them to finish */
	wrfl();
	usleep_range(10000, 11000);

	igb_irq_disable(adapter);

	adapter->flags &= ~IGB_FLAG_NEED_LINK_UPDATE;

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
	igb_update_stats(adapter);
	spin_unlock(&adapter->stats64_lock);

	adapter->link_speed = 0;
	adapter->link_duplex = 0;

	if (!pci_channel_offline(adapter->pdev))
		igb_reset(adapter);

	/* clear VLAN promisc flag so VFTA will be updated if necessary */
	adapter->flags &= ~IGB_FLAG_VLAN_PROMISC;

	igb_clean_all_tx_rings(adapter);
	igb_clean_all_rx_rings(adapter);
#ifdef CONFIG_IGB_DCA

	/* since we reset the hardware DCA settings were cleared */
	igb_setup_dca(adapter);
#endif
}