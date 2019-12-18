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
typedef  scalar_t__ u32 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ RTL_PCI_MAX_RX_QUEUE ; 
 scalar_t__ RTL_PCI_MAX_TX_QUEUE_COUNT ; 
 int /*<<< orphan*/  _rtl_pci_free_rx_ring (struct ieee80211_hw*,scalar_t__) ; 
 int /*<<< orphan*/  _rtl_pci_free_tx_ring (struct ieee80211_hw*,scalar_t__) ; 

__attribute__((used)) static int _rtl_pci_deinit_trx_ring(struct ieee80211_hw *hw)
{
	u32 i, rxring_idx;

	/*free rx rings */
	for (rxring_idx = 0; rxring_idx < RTL_PCI_MAX_RX_QUEUE; rxring_idx++)
		_rtl_pci_free_rx_ring(hw, rxring_idx);

	/*free tx rings */
	for (i = 0; i < RTL_PCI_MAX_TX_QUEUE_COUNT; i++)
		_rtl_pci_free_tx_ring(hw, i);

	return 0;
}