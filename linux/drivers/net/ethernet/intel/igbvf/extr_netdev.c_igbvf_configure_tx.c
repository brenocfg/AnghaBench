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
struct igbvf_ring {int count; int dma; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
struct e1000_hw {int dummy; } ;
struct igbvf_adapter {int txd_cmd; struct igbvf_ring* tx_ring; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCA_TXCTRL (int /*<<< orphan*/ ) ; 
 int DMA_BIT_MASK (int) ; 
 int E1000_ADVTXD_DCMD_EOP ; 
 int E1000_ADVTXD_DCMD_IFCS ; 
 int E1000_ADVTXD_DCMD_RS ; 
 int E1000_DCA_TXCTRL_TX_WB_RO_EN ; 
 int /*<<< orphan*/  E1000_TDH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_TDT (int /*<<< orphan*/ ) ; 
 int E1000_TXDCTL_QUEUE_ENABLE ; 
 int /*<<< orphan*/  TDBAH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDBAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXDCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void igbvf_configure_tx(struct igbvf_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct igbvf_ring *tx_ring = adapter->tx_ring;
	u64 tdba;
	u32 txdctl, dca_txctrl;

	/* disable transmits */
	txdctl = er32(TXDCTL(0));
	ew32(TXDCTL(0), txdctl & ~E1000_TXDCTL_QUEUE_ENABLE);
	e1e_flush();
	msleep(10);

	/* Setup the HW Tx Head and Tail descriptor pointers */
	ew32(TDLEN(0), tx_ring->count * sizeof(union e1000_adv_tx_desc));
	tdba = tx_ring->dma;
	ew32(TDBAL(0), (tdba & DMA_BIT_MASK(32)));
	ew32(TDBAH(0), (tdba >> 32));
	ew32(TDH(0), 0);
	ew32(TDT(0), 0);
	tx_ring->head = E1000_TDH(0);
	tx_ring->tail = E1000_TDT(0);

	/* Turn off Relaxed Ordering on head write-backs.  The writebacks
	 * MUST be delivered in order or it will completely screw up
	 * our bookkeeping.
	 */
	dca_txctrl = er32(DCA_TXCTRL(0));
	dca_txctrl &= ~E1000_DCA_TXCTRL_TX_WB_RO_EN;
	ew32(DCA_TXCTRL(0), dca_txctrl);

	/* enable transmits */
	txdctl |= E1000_TXDCTL_QUEUE_ENABLE;
	ew32(TXDCTL(0), txdctl);

	/* Setup Transmit Descriptor Settings for eop descriptor */
	adapter->txd_cmd = E1000_ADVTXD_DCMD_EOP | E1000_ADVTXD_DCMD_IFCS;

	/* enable Report Status bit */
	adapter->txd_cmd |= E1000_ADVTXD_DCMD_RS;
}