#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ length; } ;
struct TYPE_5__ {TYPE_1__ upper; } ;
union ixgbe_adv_rx_desc {TYPE_2__ wb; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct ixgbevf_rx_buffer {int dummy; } ;
struct ixgbevf_ring {int dma; int count; scalar_t__ next_to_alloc; scalar_t__ next_to_use; scalar_t__ next_to_clean; int /*<<< orphan*/  rx_buffer_info; scalar_t__ tail; int /*<<< orphan*/  reg_idx; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_3__ mac; } ;
struct ixgbevf_adapter {struct ixgbe_hw hw; scalar_t__ io_addr; } ;

/* Variables and functions */
 int DMA_BIT_MASK (int) ; 
 int IXGBEVF_MAX_FRAME_BUILD_SKB ; 
 union ixgbe_adv_rx_desc* IXGBEVF_RX_DESC (struct ixgbevf_ring*,int /*<<< orphan*/ ) ; 
 int IXGBE_DCA_RXCTRL_DATA_WRO_EN ; 
 int IXGBE_DCA_RXCTRL_DESC_RRO_EN ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,scalar_t__) ; 
 int IXGBE_RXDCTL_ENABLE ; 
 int IXGBE_RXDCTL_RLPMLMASK ; 
 int IXGBE_RXDCTL_RLPML_EN ; 
 int IXGBE_RXDCTL_VME ; 
 scalar_t__ IXGBE_VFDCA_RXCTRL (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_VFRDBAH (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_VFRDBAL (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_VFRDH (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_VFRDLEN (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_VFRDT (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_VFRXDCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,scalar_t__,int) ; 
 scalar_t__ ixgbe_mac_82599_vf ; 
 int /*<<< orphan*/  ixgbevf_alloc_rx_buffers (struct ixgbevf_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbevf_configure_srrctl (struct ixgbevf_adapter*,struct ixgbevf_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbevf_desc_unused (struct ixgbevf_ring*) ; 
 int /*<<< orphan*/  ixgbevf_disable_rx_queue (struct ixgbevf_adapter*,struct ixgbevf_ring*) ; 
 int /*<<< orphan*/  ixgbevf_rx_desc_queue_enable (struct ixgbevf_adapter*,struct ixgbevf_ring*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ring_uses_build_skb (struct ixgbevf_ring*) ; 
 int /*<<< orphan*/  ring_uses_large_buffer (struct ixgbevf_ring*) ; 

__attribute__((used)) static void ixgbevf_configure_rx_ring(struct ixgbevf_adapter *adapter,
				      struct ixgbevf_ring *ring)
{
	struct ixgbe_hw *hw = &adapter->hw;
	union ixgbe_adv_rx_desc *rx_desc;
	u64 rdba = ring->dma;
	u32 rxdctl;
	u8 reg_idx = ring->reg_idx;

	/* disable queue to avoid issues while updating state */
	rxdctl = IXGBE_READ_REG(hw, IXGBE_VFRXDCTL(reg_idx));
	ixgbevf_disable_rx_queue(adapter, ring);

	IXGBE_WRITE_REG(hw, IXGBE_VFRDBAL(reg_idx), rdba & DMA_BIT_MASK(32));
	IXGBE_WRITE_REG(hw, IXGBE_VFRDBAH(reg_idx), rdba >> 32);
	IXGBE_WRITE_REG(hw, IXGBE_VFRDLEN(reg_idx),
			ring->count * sizeof(union ixgbe_adv_rx_desc));

#ifndef CONFIG_SPARC
	/* enable relaxed ordering */
	IXGBE_WRITE_REG(hw, IXGBE_VFDCA_RXCTRL(reg_idx),
			IXGBE_DCA_RXCTRL_DESC_RRO_EN);
#else
	IXGBE_WRITE_REG(hw, IXGBE_VFDCA_RXCTRL(reg_idx),
			IXGBE_DCA_RXCTRL_DESC_RRO_EN |
			IXGBE_DCA_RXCTRL_DATA_WRO_EN);
#endif

	/* reset head and tail pointers */
	IXGBE_WRITE_REG(hw, IXGBE_VFRDH(reg_idx), 0);
	IXGBE_WRITE_REG(hw, IXGBE_VFRDT(reg_idx), 0);
	ring->tail = adapter->io_addr + IXGBE_VFRDT(reg_idx);

	/* initialize rx_buffer_info */
	memset(ring->rx_buffer_info, 0,
	       sizeof(struct ixgbevf_rx_buffer) * ring->count);

	/* initialize Rx descriptor 0 */
	rx_desc = IXGBEVF_RX_DESC(ring, 0);
	rx_desc->wb.upper.length = 0;

	/* reset ntu and ntc to place SW in sync with hardwdare */
	ring->next_to_clean = 0;
	ring->next_to_use = 0;
	ring->next_to_alloc = 0;

	ixgbevf_configure_srrctl(adapter, ring, reg_idx);

	/* RXDCTL.RLPML does not work on 82599 */
	if (adapter->hw.mac.type != ixgbe_mac_82599_vf) {
		rxdctl &= ~(IXGBE_RXDCTL_RLPMLMASK |
			    IXGBE_RXDCTL_RLPML_EN);

#if (PAGE_SIZE < 8192)
		/* Limit the maximum frame size so we don't overrun the skb */
		if (ring_uses_build_skb(ring) &&
		    !ring_uses_large_buffer(ring))
			rxdctl |= IXGBEVF_MAX_FRAME_BUILD_SKB |
				  IXGBE_RXDCTL_RLPML_EN;
#endif
	}

	rxdctl |= IXGBE_RXDCTL_ENABLE | IXGBE_RXDCTL_VME;
	IXGBE_WRITE_REG(hw, IXGBE_VFRXDCTL(reg_idx), rxdctl);

	ixgbevf_rx_desc_queue_enable(adapter, ring);
	ixgbevf_alloc_rx_buffers(ring, ixgbevf_desc_unused(ring));
}