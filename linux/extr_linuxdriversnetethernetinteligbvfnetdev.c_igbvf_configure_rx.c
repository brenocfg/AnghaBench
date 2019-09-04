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
typedef  union e1000_adv_rx_desc {int dummy; } e1000_adv_rx_desc ;
typedef  int u64 ;
typedef  int u32 ;
struct igbvf_ring {int dma; int count; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
struct e1000_hw {int dummy; } ;
struct igbvf_adapter {struct igbvf_ring* rx_ring; struct e1000_hw hw; } ;

/* Variables and functions */
 int DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  E1000_RDH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_RDT (int /*<<< orphan*/ ) ; 
 int E1000_RXDCTL_QUEUE_ENABLE ; 
 int IGBVF_RX_HTHRESH ; 
 int IGBVF_RX_PTHRESH ; 
 int IGBVF_RX_WTHRESH ; 
 int /*<<< orphan*/  RDBAH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDBAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RXDCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  igbvf_set_rlpml (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void igbvf_configure_rx(struct igbvf_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct igbvf_ring *rx_ring = adapter->rx_ring;
	u64 rdba;
	u32 rxdctl;

	/* disable receives */
	rxdctl = er32(RXDCTL(0));
	ew32(RXDCTL(0), rxdctl & ~E1000_RXDCTL_QUEUE_ENABLE);
	e1e_flush();
	msleep(10);

	/* Setup the HW Rx Head and Tail Descriptor Pointers and
	 * the Base and Length of the Rx Descriptor Ring
	 */
	rdba = rx_ring->dma;
	ew32(RDBAL(0), (rdba & DMA_BIT_MASK(32)));
	ew32(RDBAH(0), (rdba >> 32));
	ew32(RDLEN(0), rx_ring->count * sizeof(union e1000_adv_rx_desc));
	rx_ring->head = E1000_RDH(0);
	rx_ring->tail = E1000_RDT(0);
	ew32(RDH(0), 0);
	ew32(RDT(0), 0);

	rxdctl |= E1000_RXDCTL_QUEUE_ENABLE;
	rxdctl &= 0xFFF00000;
	rxdctl |= IGBVF_RX_PTHRESH;
	rxdctl |= IGBVF_RX_HTHRESH << 8;
	rxdctl |= IGBVF_RX_WTHRESH << 16;

	igbvf_set_rlpml(adapter);

	/* enable receives */
	ew32(RXDCTL(0), rxdctl);
}