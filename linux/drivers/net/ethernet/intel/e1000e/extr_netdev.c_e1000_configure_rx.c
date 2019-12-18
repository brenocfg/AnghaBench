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
typedef  union e1000_rx_desc_packet_split {int dummy; } e1000_rx_desc_packet_split ;
typedef  union e1000_rx_desc_extended {int dummy; } e1000_rx_desc_extended ;
typedef  int u64 ;
typedef  int u32 ;
struct e1000_ring {int count; int dma; scalar_t__ tail; scalar_t__ head; } ;
struct e1000_hw {scalar_t__ hw_addr; } ;
struct e1000_adapter {int flags2; int rx_int_delay; int rx_abs_int_delay; scalar_t__ itr_setting; scalar_t__ itr; int max_frame_size; int flags; int /*<<< orphan*/  pm_qos_req; TYPE_2__* pdev; TYPE_1__* netdev; struct e1000_hw hw; int /*<<< orphan*/  alloc_rx_buf; int /*<<< orphan*/  clean_rx; scalar_t__ rx_ps_pages; struct e1000_ring* rx_ring; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ mtu; int features; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CTRL_EXT ; 
 int DMA_BIT_MASK (int) ; 
 int E1000_CTRL_EXT_IAME ; 
 int E1000_PBA_RXA_MASK ; 
 int E1000_RCTL_EN ; 
 scalar_t__ E1000_RDH (int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_RDT (int /*<<< orphan*/ ) ; 
 int E1000_RXCSUM_TUOFL ; 
 int E1000_RXDCTL_DMA_BURST_ENABLE ; 
 scalar_t__ ETH_DATA_LEN ; 
 scalar_t__ ETH_FCS_LEN ; 
 scalar_t__ ETH_FRAME_LEN ; 
 int FLAG2_DMA_BURST ; 
 int FLAG2_NO_DISABLE_RX ; 
 int FLAG2_PCIM2PCI_ARBITER_WA ; 
 int FLAG_IS_ICH ; 
 int /*<<< orphan*/  IAM ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  PBA ; 
 int PM_QOS_DEFAULT_VALUE ; 
 int /*<<< orphan*/  RADV ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  RDBAH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDBAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDTR ; 
 int /*<<< orphan*/  RXCSUM ; 
 int /*<<< orphan*/  RXDCTL (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  e1000_alloc_jumbo_rx_buffers ; 
 int /*<<< orphan*/  e1000_alloc_rx_buffers ; 
 int /*<<< orphan*/  e1000_alloc_rx_buffers_ps ; 
 int /*<<< orphan*/  e1000_clean_jumbo_rx_irq ; 
 int /*<<< orphan*/  e1000_clean_rx_irq ; 
 int /*<<< orphan*/  e1000_clean_rx_irq_ps ; 
 int /*<<< orphan*/  e1000e_update_rdt_wa (struct e1000_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000e_write_itr (struct e1000_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_qos_update_request (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void e1000_configure_rx(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct e1000_ring *rx_ring = adapter->rx_ring;
	u64 rdba;
	u32 rdlen, rctl, rxcsum, ctrl_ext;

	if (adapter->rx_ps_pages) {
		/* this is a 32 byte descriptor */
		rdlen = rx_ring->count *
		    sizeof(union e1000_rx_desc_packet_split);
		adapter->clean_rx = e1000_clean_rx_irq_ps;
		adapter->alloc_rx_buf = e1000_alloc_rx_buffers_ps;
	} else if (adapter->netdev->mtu > ETH_FRAME_LEN + ETH_FCS_LEN) {
		rdlen = rx_ring->count * sizeof(union e1000_rx_desc_extended);
		adapter->clean_rx = e1000_clean_jumbo_rx_irq;
		adapter->alloc_rx_buf = e1000_alloc_jumbo_rx_buffers;
	} else {
		rdlen = rx_ring->count * sizeof(union e1000_rx_desc_extended);
		adapter->clean_rx = e1000_clean_rx_irq;
		adapter->alloc_rx_buf = e1000_alloc_rx_buffers;
	}

	/* disable receives while setting up the descriptors */
	rctl = er32(RCTL);
	if (!(adapter->flags2 & FLAG2_NO_DISABLE_RX))
		ew32(RCTL, rctl & ~E1000_RCTL_EN);
	e1e_flush();
	usleep_range(10000, 11000);

	if (adapter->flags2 & FLAG2_DMA_BURST) {
		/* set the writeback threshold (only takes effect if the RDTR
		 * is set). set GRAN=1 and write back up to 0x4 worth, and
		 * enable prefetching of 0x20 Rx descriptors
		 * granularity = 01
		 * wthresh = 04,
		 * hthresh = 04,
		 * pthresh = 0x20
		 */
		ew32(RXDCTL(0), E1000_RXDCTL_DMA_BURST_ENABLE);
		ew32(RXDCTL(1), E1000_RXDCTL_DMA_BURST_ENABLE);
	}

	/* set the Receive Delay Timer Register */
	ew32(RDTR, adapter->rx_int_delay);

	/* irq moderation */
	ew32(RADV, adapter->rx_abs_int_delay);
	if ((adapter->itr_setting != 0) && (adapter->itr != 0))
		e1000e_write_itr(adapter, adapter->itr);

	ctrl_ext = er32(CTRL_EXT);
	/* Auto-Mask interrupts upon ICR access */
	ctrl_ext |= E1000_CTRL_EXT_IAME;
	ew32(IAM, 0xffffffff);
	ew32(CTRL_EXT, ctrl_ext);
	e1e_flush();

	/* Setup the HW Rx Head and Tail Descriptor Pointers and
	 * the Base and Length of the Rx Descriptor Ring
	 */
	rdba = rx_ring->dma;
	ew32(RDBAL(0), (rdba & DMA_BIT_MASK(32)));
	ew32(RDBAH(0), (rdba >> 32));
	ew32(RDLEN(0), rdlen);
	ew32(RDH(0), 0);
	ew32(RDT(0), 0);
	rx_ring->head = adapter->hw.hw_addr + E1000_RDH(0);
	rx_ring->tail = adapter->hw.hw_addr + E1000_RDT(0);

	writel(0, rx_ring->head);
	if (adapter->flags2 & FLAG2_PCIM2PCI_ARBITER_WA)
		e1000e_update_rdt_wa(rx_ring, 0);
	else
		writel(0, rx_ring->tail);

	/* Enable Receive Checksum Offload for TCP and UDP */
	rxcsum = er32(RXCSUM);
	if (adapter->netdev->features & NETIF_F_RXCSUM)
		rxcsum |= E1000_RXCSUM_TUOFL;
	else
		rxcsum &= ~E1000_RXCSUM_TUOFL;
	ew32(RXCSUM, rxcsum);

	/* With jumbo frames, excessive C-state transition latencies result
	 * in dropped transactions.
	 */
	if (adapter->netdev->mtu > ETH_DATA_LEN) {
		u32 lat =
		    ((er32(PBA) & E1000_PBA_RXA_MASK) * 1024 -
		     adapter->max_frame_size) * 8 / 1000;

		if (adapter->flags & FLAG_IS_ICH) {
			u32 rxdctl = er32(RXDCTL(0));

			ew32(RXDCTL(0), rxdctl | 0x3 | BIT(8));
		}

		dev_info(&adapter->pdev->dev,
			 "Some CPU C-states have been disabled in order to enable jumbo frames\n");
		pm_qos_update_request(&adapter->pm_qos_req, lat);
	} else {
		pm_qos_update_request(&adapter->pm_qos_req,
				      PM_QOS_DEFAULT_VALUE);
	}

	/* Enable Receives */
	ew32(RCTL, rctl);
}