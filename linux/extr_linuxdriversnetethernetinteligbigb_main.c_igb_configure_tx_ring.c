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
typedef  union e1000_adv_tx_desc {int dummy; } e1000_adv_tx_desc ;
typedef  int u64 ;
typedef  int u32 ;
struct igb_tx_buffer {int dummy; } ;
struct igb_ring {int dma; int reg_idx; int count; int /*<<< orphan*/  tx_buffer_info; scalar_t__ tail; } ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {scalar_t__ io_addr; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_TDBAH (int) ; 
 int /*<<< orphan*/  E1000_TDBAL (int) ; 
 int /*<<< orphan*/  E1000_TDH (int) ; 
 int /*<<< orphan*/  E1000_TDLEN (int) ; 
 scalar_t__ E1000_TDT (int) ; 
 int /*<<< orphan*/  E1000_TXDCTL (int) ; 
 int E1000_TXDCTL_QUEUE_ENABLE ; 
 int IGB_TX_HTHRESH ; 
 int IGB_TX_PTHRESH ; 
 int IGB_TX_WTHRESH ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void igb_configure_tx_ring(struct igb_adapter *adapter,
			   struct igb_ring *ring)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 txdctl = 0;
	u64 tdba = ring->dma;
	int reg_idx = ring->reg_idx;

	wr32(E1000_TDLEN(reg_idx),
	     ring->count * sizeof(union e1000_adv_tx_desc));
	wr32(E1000_TDBAL(reg_idx),
	     tdba & 0x00000000ffffffffULL);
	wr32(E1000_TDBAH(reg_idx), tdba >> 32);

	ring->tail = adapter->io_addr + E1000_TDT(reg_idx);
	wr32(E1000_TDH(reg_idx), 0);
	writel(0, ring->tail);

	txdctl |= IGB_TX_PTHRESH;
	txdctl |= IGB_TX_HTHRESH << 8;
	txdctl |= IGB_TX_WTHRESH << 16;

	/* reinitialize tx_buffer_info */
	memset(ring->tx_buffer_info, 0,
	       sizeof(struct igb_tx_buffer) * ring->count);

	txdctl |= E1000_TXDCTL_QUEUE_ENABLE;
	wr32(E1000_TXDCTL(reg_idx), txdctl);
}