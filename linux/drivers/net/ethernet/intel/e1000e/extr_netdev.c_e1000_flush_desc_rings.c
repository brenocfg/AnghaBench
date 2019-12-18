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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct e1000_hw {int dummy; } ;
struct e1000_adapter {int /*<<< orphan*/  pdev; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_FEXTNVM11_DISABLE_MULR_FIX ; 
 int /*<<< orphan*/  FEXTNVM11 ; 
 int FLUSH_DESC_REQUIRED ; 
 int /*<<< orphan*/  PCICFG_DESC_RING_STATUS ; 
 int /*<<< orphan*/  TDLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_flush_rx_ring (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_flush_tx_ring (struct e1000_adapter*) ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void e1000_flush_desc_rings(struct e1000_adapter *adapter)
{
	u16 hang_state;
	u32 fext_nvm11, tdlen;
	struct e1000_hw *hw = &adapter->hw;

	/* First, disable MULR fix in FEXTNVM11 */
	fext_nvm11 = er32(FEXTNVM11);
	fext_nvm11 |= E1000_FEXTNVM11_DISABLE_MULR_FIX;
	ew32(FEXTNVM11, fext_nvm11);
	/* do nothing if we're not in faulty state, or if the queue is empty */
	tdlen = er32(TDLEN(0));
	pci_read_config_word(adapter->pdev, PCICFG_DESC_RING_STATUS,
			     &hang_state);
	if (!(hang_state & FLUSH_DESC_REQUIRED) || !tdlen)
		return;
	e1000_flush_tx_ring(adapter);
	/* recheck, maybe the fault is caused by the rx ring */
	pci_read_config_word(adapter->pdev, PCICFG_DESC_RING_STATUS,
			     &hang_state);
	if (hang_state & FLUSH_DESC_REQUIRED)
		e1000_flush_rx_ring(adapter);
}