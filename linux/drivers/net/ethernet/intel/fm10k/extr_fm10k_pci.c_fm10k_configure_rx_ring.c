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
typedef  union fm10k_rx_desc {int dummy; } fm10k_rx_desc ;
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct fm10k_ring {int dma; int count; int reg_idx; TYPE_2__* q_vector; int /*<<< orphan*/  vid; int /*<<< orphan*/  qos_pc; scalar_t__ next_to_alloc; scalar_t__ next_to_use; scalar_t__ next_to_clean; int /*<<< orphan*/ * tail; } ;
struct TYPE_3__ {int /*<<< orphan*/  default_vid; } ;
struct fm10k_hw {TYPE_1__ mac; } ;
struct fm10k_intfc {int rx_pause; int pfc_en; int /*<<< orphan*/  active_vlans; int /*<<< orphan*/ * uc_addr; struct fm10k_hw hw; } ;
struct TYPE_4__ {int v_idx; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int DMA_BIT_MASK (int) ; 
 int FM10K_INT_MAP_DISABLE ; 
 int FM10K_INT_MAP_TIMER1 ; 
 size_t FM10K_RDBAH (int) ; 
 size_t FM10K_RDBAL (int) ; 
 size_t FM10K_RDH (int) ; 
 size_t FM10K_RDLEN (int) ; 
 size_t FM10K_RDT (int) ; 
 size_t FM10K_RXDCTL (int) ; 
 int FM10K_RXDCTL_DROP_ON_EMPTY ; 
 int FM10K_RXDCTL_WRITE_BACK_MIN_DELAY ; 
 size_t FM10K_RXINT (int) ; 
 size_t FM10K_RXQCTL (int) ; 
 int FM10K_RXQCTL_ENABLE ; 
 int FM10K_RX_BUFSZ ; 
 size_t FM10K_SRRCTL (int) ; 
 int FM10K_SRRCTL_BSIZEPKT_SHIFT ; 
 int FM10K_SRRCTL_BUFFER_CHAINING_EN ; 
 int FM10K_SRRCTL_LOOPBACK_SUPPRESS ; 
 int /*<<< orphan*/  FM10K_VLAN_CLEAR ; 
 int NON_Q_VECTORS ; 
 int /*<<< orphan*/  fm10k_alloc_rx_buffers (struct fm10k_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_desc_unused (struct fm10k_ring*) ; 
 int fm10k_read_reg (struct fm10k_hw*,size_t) ; 
 int /*<<< orphan*/  fm10k_write_flush (struct fm10k_hw*) ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,size_t,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_configure_rx_ring(struct fm10k_intfc *interface,
				    struct fm10k_ring *ring)
{
	u64 rdba = ring->dma;
	struct fm10k_hw *hw = &interface->hw;
	u32 size = ring->count * sizeof(union fm10k_rx_desc);
	u32 rxqctl, rxdctl = FM10K_RXDCTL_WRITE_BACK_MIN_DELAY;
	u32 srrctl = FM10K_SRRCTL_BUFFER_CHAINING_EN;
	u32 rxint = FM10K_INT_MAP_DISABLE;
	u8 rx_pause = interface->rx_pause;
	u8 reg_idx = ring->reg_idx;

	/* disable queue to avoid issues while updating state */
	rxqctl = fm10k_read_reg(hw, FM10K_RXQCTL(reg_idx));
	rxqctl &= ~FM10K_RXQCTL_ENABLE;
	fm10k_write_reg(hw, FM10K_RXQCTL(reg_idx), rxqctl);
	fm10k_write_flush(hw);

	/* possible poll here to verify ring resources have been cleaned */

	/* set location and size for descriptor ring */
	fm10k_write_reg(hw, FM10K_RDBAL(reg_idx), rdba & DMA_BIT_MASK(32));
	fm10k_write_reg(hw, FM10K_RDBAH(reg_idx), rdba >> 32);
	fm10k_write_reg(hw, FM10K_RDLEN(reg_idx), size);

	/* reset head and tail pointers */
	fm10k_write_reg(hw, FM10K_RDH(reg_idx), 0);
	fm10k_write_reg(hw, FM10K_RDT(reg_idx), 0);

	/* store tail pointer */
	ring->tail = &interface->uc_addr[FM10K_RDT(reg_idx)];

	/* reset ntu and ntc to place SW in sync with hardware */
	ring->next_to_clean = 0;
	ring->next_to_use = 0;
	ring->next_to_alloc = 0;

	/* Configure the Rx buffer size for one buff without split */
	srrctl |= FM10K_RX_BUFSZ >> FM10K_SRRCTL_BSIZEPKT_SHIFT;

	/* Configure the Rx ring to suppress loopback packets */
	srrctl |= FM10K_SRRCTL_LOOPBACK_SUPPRESS;
	fm10k_write_reg(hw, FM10K_SRRCTL(reg_idx), srrctl);

	/* Enable drop on empty */
#ifdef CONFIG_DCB
	if (interface->pfc_en)
		rx_pause = interface->pfc_en;
#endif
	if (!(rx_pause & BIT(ring->qos_pc)))
		rxdctl |= FM10K_RXDCTL_DROP_ON_EMPTY;

	fm10k_write_reg(hw, FM10K_RXDCTL(reg_idx), rxdctl);

	/* assign default VLAN to queue */
	ring->vid = hw->mac.default_vid;

	/* if we have an active VLAN, disable default VLAN ID */
	if (test_bit(hw->mac.default_vid, interface->active_vlans))
		ring->vid |= FM10K_VLAN_CLEAR;

	/* Map interrupt */
	if (ring->q_vector) {
		rxint = ring->q_vector->v_idx + NON_Q_VECTORS;
		rxint |= FM10K_INT_MAP_TIMER1;
	}

	fm10k_write_reg(hw, FM10K_RXINT(reg_idx), rxint);

	/* enable queue */
	rxqctl = fm10k_read_reg(hw, FM10K_RXQCTL(reg_idx));
	rxqctl |= FM10K_RXQCTL_ENABLE;
	fm10k_write_reg(hw, FM10K_RXQCTL(reg_idx), rxqctl);

	/* place buffers on ring for receive data */
	fm10k_alloc_rx_buffers(ring, fm10k_desc_unused(ring));
}