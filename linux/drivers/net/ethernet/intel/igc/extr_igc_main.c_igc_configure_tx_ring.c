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
typedef  union igc_adv_tx_desc {int dummy; } igc_adv_tx_desc ;
typedef  int u64 ;
typedef  int u32 ;
struct igc_ring {int reg_idx; int dma; int count; scalar_t__ tail; } ;
struct igc_hw {int dummy; } ;
struct igc_adapter {scalar_t__ io_addr; struct igc_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_TDBAH (int) ; 
 int /*<<< orphan*/  IGC_TDBAL (int) ; 
 int /*<<< orphan*/  IGC_TDH (int) ; 
 int /*<<< orphan*/  IGC_TDLEN (int) ; 
 scalar_t__ IGC_TDT (int) ; 
 int /*<<< orphan*/  IGC_TXDCTL (int) ; 
 int IGC_TXDCTL_QUEUE_ENABLE ; 
 int IGC_TX_HTHRESH ; 
 int IGC_TX_PTHRESH ; 
 int IGC_TX_WTHRESH ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrfl () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void igc_configure_tx_ring(struct igc_adapter *adapter,
				  struct igc_ring *ring)
{
	struct igc_hw *hw = &adapter->hw;
	int reg_idx = ring->reg_idx;
	u64 tdba = ring->dma;
	u32 txdctl = 0;

	/* disable the queue */
	wr32(IGC_TXDCTL(reg_idx), 0);
	wrfl();
	mdelay(10);

	wr32(IGC_TDLEN(reg_idx),
	     ring->count * sizeof(union igc_adv_tx_desc));
	wr32(IGC_TDBAL(reg_idx),
	     tdba & 0x00000000ffffffffULL);
	wr32(IGC_TDBAH(reg_idx), tdba >> 32);

	ring->tail = adapter->io_addr + IGC_TDT(reg_idx);
	wr32(IGC_TDH(reg_idx), 0);
	writel(0, ring->tail);

	txdctl |= IGC_TX_PTHRESH;
	txdctl |= IGC_TX_HTHRESH << 8;
	txdctl |= IGC_TX_WTHRESH << 16;

	txdctl |= IGC_TXDCTL_QUEUE_ENABLE;
	wr32(IGC_TXDCTL(reg_idx), txdctl);
}