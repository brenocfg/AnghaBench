#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ length; } ;
struct TYPE_8__ {TYPE_2__ upper; } ;
union ixgbe_adv_rx_desc {TYPE_3__ wb; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct ixgbe_rx_buffer {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  free; } ;
struct ixgbe_ring {int dma; int count; int rx_buf_len; TYPE_5__* xsk_umem; int /*<<< orphan*/  rx_buffer_info; int /*<<< orphan*/  state; scalar_t__ tail; int /*<<< orphan*/  xdp_rxq; TYPE_4__ zca; int /*<<< orphan*/  reg_idx; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {scalar_t__ io_addr; struct ixgbe_hw hw; } ;
struct TYPE_10__ {int chunk_size_nohr; } ;

/* Variables and functions */
 int DMA_BIT_MASK (int) ; 
 int IXGBE_MAX_2K_FRAME_BUILD_SKB ; 
 scalar_t__ IXGBE_RDBAH (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_RDBAL (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_RDH (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_RDLEN (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_RDT (int /*<<< orphan*/ ) ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,scalar_t__) ; 
 scalar_t__ IXGBE_RXDCTL (int /*<<< orphan*/ ) ; 
 int IXGBE_RXDCTL_ENABLE ; 
 int IXGBE_RXDCTL_RLPMLMASK ; 
 int IXGBE_RXDCTL_RLPML_EN ; 
 union ixgbe_adv_rx_desc* IXGBE_RX_DESC (struct ixgbe_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,scalar_t__,int) ; 
 int /*<<< orphan*/  MEM_TYPE_PAGE_SHARED ; 
 int /*<<< orphan*/  MEM_TYPE_ZERO_COPY ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int XDP_PACKET_HEADROOM ; 
 int /*<<< orphan*/  __IXGBE_RX_3K_BUFFER ; 
 int /*<<< orphan*/  ixgbe_alloc_rx_buffers (struct ixgbe_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_alloc_rx_buffers_zc (struct ixgbe_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_configure_rscctl (struct ixgbe_adapter*,struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_configure_srrctl (struct ixgbe_adapter*,struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_desc_unused (struct ixgbe_ring*) ; 
 scalar_t__ ixgbe_mac_82598EB ; 
 scalar_t__ ixgbe_mac_82599EB ; 
 int /*<<< orphan*/  ixgbe_rx_desc_queue_enable (struct ixgbe_adapter*,struct ixgbe_ring*) ; 
 TYPE_5__* ixgbe_xsk_umem (struct ixgbe_adapter*,struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_zca_free ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ring_uses_build_skb (struct ixgbe_ring*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdp_rxq_info_reg_mem_model (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg_mem_model (int /*<<< orphan*/ *) ; 

void ixgbe_configure_rx_ring(struct ixgbe_adapter *adapter,
			     struct ixgbe_ring *ring)
{
	struct ixgbe_hw *hw = &adapter->hw;
	union ixgbe_adv_rx_desc *rx_desc;
	u64 rdba = ring->dma;
	u32 rxdctl;
	u8 reg_idx = ring->reg_idx;

	xdp_rxq_info_unreg_mem_model(&ring->xdp_rxq);
	ring->xsk_umem = ixgbe_xsk_umem(adapter, ring);
	if (ring->xsk_umem) {
		ring->zca.free = ixgbe_zca_free;
		WARN_ON(xdp_rxq_info_reg_mem_model(&ring->xdp_rxq,
						   MEM_TYPE_ZERO_COPY,
						   &ring->zca));

	} else {
		WARN_ON(xdp_rxq_info_reg_mem_model(&ring->xdp_rxq,
						   MEM_TYPE_PAGE_SHARED, NULL));
	}

	/* disable queue to avoid use of these values while updating state */
	rxdctl = IXGBE_READ_REG(hw, IXGBE_RXDCTL(reg_idx));
	rxdctl &= ~IXGBE_RXDCTL_ENABLE;

	/* write value back with RXDCTL.ENABLE bit cleared */
	IXGBE_WRITE_REG(hw, IXGBE_RXDCTL(reg_idx), rxdctl);
	IXGBE_WRITE_FLUSH(hw);

	IXGBE_WRITE_REG(hw, IXGBE_RDBAL(reg_idx), (rdba & DMA_BIT_MASK(32)));
	IXGBE_WRITE_REG(hw, IXGBE_RDBAH(reg_idx), (rdba >> 32));
	IXGBE_WRITE_REG(hw, IXGBE_RDLEN(reg_idx),
			ring->count * sizeof(union ixgbe_adv_rx_desc));
	/* Force flushing of IXGBE_RDLEN to prevent MDD */
	IXGBE_WRITE_FLUSH(hw);

	IXGBE_WRITE_REG(hw, IXGBE_RDH(reg_idx), 0);
	IXGBE_WRITE_REG(hw, IXGBE_RDT(reg_idx), 0);
	ring->tail = adapter->io_addr + IXGBE_RDT(reg_idx);

	ixgbe_configure_srrctl(adapter, ring);
	ixgbe_configure_rscctl(adapter, ring);

	if (hw->mac.type == ixgbe_mac_82598EB) {
		/*
		 * enable cache line friendly hardware writes:
		 * PTHRESH=32 descriptors (half the internal cache),
		 * this also removes ugly rx_no_buffer_count increment
		 * HTHRESH=4 descriptors (to minimize latency on fetch)
		 * WTHRESH=8 burst writeback up to two cache lines
		 */
		rxdctl &= ~0x3FFFFF;
		rxdctl |=  0x080420;
#if (PAGE_SIZE < 8192)
	/* RXDCTL.RLPML does not work on 82599 */
	} else if (hw->mac.type != ixgbe_mac_82599EB) {
		rxdctl &= ~(IXGBE_RXDCTL_RLPMLMASK |
			    IXGBE_RXDCTL_RLPML_EN);

		/* Limit the maximum frame size so we don't overrun the skb.
		 * This can happen in SRIOV mode when the MTU of the VF is
		 * higher than the MTU of the PF.
		 */
		if (ring_uses_build_skb(ring) &&
		    !test_bit(__IXGBE_RX_3K_BUFFER, &ring->state))
			rxdctl |= IXGBE_MAX_2K_FRAME_BUILD_SKB |
				  IXGBE_RXDCTL_RLPML_EN;
#endif
	}

	if (ring->xsk_umem && hw->mac.type != ixgbe_mac_82599EB) {
		u32 xsk_buf_len = ring->xsk_umem->chunk_size_nohr -
				  XDP_PACKET_HEADROOM;

		rxdctl &= ~(IXGBE_RXDCTL_RLPMLMASK |
			    IXGBE_RXDCTL_RLPML_EN);
		rxdctl |= xsk_buf_len | IXGBE_RXDCTL_RLPML_EN;

		ring->rx_buf_len = xsk_buf_len;
	}

	/* initialize rx_buffer_info */
	memset(ring->rx_buffer_info, 0,
	       sizeof(struct ixgbe_rx_buffer) * ring->count);

	/* initialize Rx descriptor 0 */
	rx_desc = IXGBE_RX_DESC(ring, 0);
	rx_desc->wb.upper.length = 0;

	/* enable receive descriptor ring */
	rxdctl |= IXGBE_RXDCTL_ENABLE;
	IXGBE_WRITE_REG(hw, IXGBE_RXDCTL(reg_idx), rxdctl);

	ixgbe_rx_desc_queue_enable(adapter, ring);
	if (ring->xsk_umem)
		ixgbe_alloc_rx_buffers_zc(ring, ixgbe_desc_unused(ring));
	else
		ixgbe_alloc_rx_buffers(ring, ixgbe_desc_unused(ring));
}