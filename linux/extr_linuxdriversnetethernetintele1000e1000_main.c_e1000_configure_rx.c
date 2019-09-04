#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct e1000_rx_desc {int dummy; } ;
struct e1000_hw {scalar_t__ mac_type; } ;
struct e1000_adapter {int rx_int_delay; int rx_abs_int_delay; scalar_t__ itr_setting; int itr; int num_rx_queues; scalar_t__ rx_csum; TYPE_2__* rx_ring; int /*<<< orphan*/  alloc_rx_buf; int /*<<< orphan*/  clean_rx; TYPE_1__* netdev; struct e1000_hw hw; } ;
struct TYPE_4__ {int count; int dma; int /*<<< orphan*/  rdt; int /*<<< orphan*/  rdh; } ;
struct TYPE_3__ {scalar_t__ mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_82542_RDH ; 
 int /*<<< orphan*/  E1000_82542_RDT ; 
 int E1000_RCTL_EN ; 
 int /*<<< orphan*/  E1000_RDH ; 
 int /*<<< orphan*/  E1000_RDT ; 
 int E1000_RXCSUM_TUOFL ; 
 scalar_t__ ETH_DATA_LEN ; 
 int /*<<< orphan*/  ITR ; 
 int /*<<< orphan*/  RADV ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  RDBAH ; 
 int /*<<< orphan*/  RDBAL ; 
 int /*<<< orphan*/  RDH ; 
 int /*<<< orphan*/  RDLEN ; 
 int /*<<< orphan*/  RDT ; 
 int /*<<< orphan*/  RDTR ; 
 int /*<<< orphan*/  RXCSUM ; 
 scalar_t__ e1000_82540 ; 
 scalar_t__ e1000_82543 ; 
 int /*<<< orphan*/  e1000_alloc_jumbo_rx_buffers ; 
 int /*<<< orphan*/  e1000_alloc_rx_buffers ; 
 int /*<<< orphan*/  e1000_clean_jumbo_rx_irq ; 
 int /*<<< orphan*/  e1000_clean_rx_irq ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void e1000_configure_rx(struct e1000_adapter *adapter)
{
	u64 rdba;
	struct e1000_hw *hw = &adapter->hw;
	u32 rdlen, rctl, rxcsum;

	if (adapter->netdev->mtu > ETH_DATA_LEN) {
		rdlen = adapter->rx_ring[0].count *
			sizeof(struct e1000_rx_desc);
		adapter->clean_rx = e1000_clean_jumbo_rx_irq;
		adapter->alloc_rx_buf = e1000_alloc_jumbo_rx_buffers;
	} else {
		rdlen = adapter->rx_ring[0].count *
			sizeof(struct e1000_rx_desc);
		adapter->clean_rx = e1000_clean_rx_irq;
		adapter->alloc_rx_buf = e1000_alloc_rx_buffers;
	}

	/* disable receives while setting up the descriptors */
	rctl = er32(RCTL);
	ew32(RCTL, rctl & ~E1000_RCTL_EN);

	/* set the Receive Delay Timer Register */
	ew32(RDTR, adapter->rx_int_delay);

	if (hw->mac_type >= e1000_82540) {
		ew32(RADV, adapter->rx_abs_int_delay);
		if (adapter->itr_setting != 0)
			ew32(ITR, 1000000000 / (adapter->itr * 256));
	}

	/* Setup the HW Rx Head and Tail Descriptor Pointers and
	 * the Base and Length of the Rx Descriptor Ring
	 */
	switch (adapter->num_rx_queues) {
	case 1:
	default:
		rdba = adapter->rx_ring[0].dma;
		ew32(RDLEN, rdlen);
		ew32(RDBAH, (rdba >> 32));
		ew32(RDBAL, (rdba & 0x00000000ffffffffULL));
		ew32(RDT, 0);
		ew32(RDH, 0);
		adapter->rx_ring[0].rdh = ((hw->mac_type >= e1000_82543) ?
					   E1000_RDH : E1000_82542_RDH);
		adapter->rx_ring[0].rdt = ((hw->mac_type >= e1000_82543) ?
					   E1000_RDT : E1000_82542_RDT);
		break;
	}

	/* Enable 82543 Receive Checksum Offload for TCP and UDP */
	if (hw->mac_type >= e1000_82543) {
		rxcsum = er32(RXCSUM);
		if (adapter->rx_csum)
			rxcsum |= E1000_RXCSUM_TUOFL;
		else
			/* don't need to clear IPPCSE as it defaults to 0 */
			rxcsum &= ~E1000_RXCSUM_TUOFL;
		ew32(RXCSUM, rxcsum);
	}

	/* Enable Receives */
	ew32(RCTL, rctl | E1000_RCTL_EN);
}