#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct fm10k_tx_desc {int dummy; } ;
struct fm10k_ring {int dma; int count; int /*<<< orphan*/  queue_index; TYPE_1__* q_vector; int /*<<< orphan*/  netdev; int /*<<< orphan*/  state; scalar_t__ next_to_use; scalar_t__ next_to_clean; int /*<<< orphan*/ * tail; int /*<<< orphan*/  reg_idx; } ;
struct fm10k_hw {int dummy; } ;
struct fm10k_intfc {int /*<<< orphan*/ * uc_addr; struct fm10k_hw hw; } ;
struct TYPE_2__ {int v_idx; int /*<<< orphan*/  affinity_mask; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int DMA_BIT_MASK (int) ; 
 int FM10K_INT_MAP_DISABLE ; 
 int FM10K_INT_MAP_TIMER0 ; 
 size_t FM10K_PFVTCTL (int /*<<< orphan*/ ) ; 
 int FM10K_PFVTCTL_FTAG_DESC_ENABLE ; 
 size_t FM10K_TDBAH (int /*<<< orphan*/ ) ; 
 size_t FM10K_TDBAL (int /*<<< orphan*/ ) ; 
 size_t FM10K_TDH (int /*<<< orphan*/ ) ; 
 size_t FM10K_TDLEN (int /*<<< orphan*/ ) ; 
 size_t FM10K_TDT (int /*<<< orphan*/ ) ; 
 size_t FM10K_TXDCTL (int /*<<< orphan*/ ) ; 
 int FM10K_TXDCTL_ENABLE ; 
 int /*<<< orphan*/  FM10K_TXDCTL_MAX_TIME_SHIFT ; 
 size_t FM10K_TXINT (int /*<<< orphan*/ ) ; 
 int NON_Q_VECTORS ; 
 int /*<<< orphan*/  __FM10K_TX_XPS_INIT_DONE ; 
 int /*<<< orphan*/  fm10k_write_flush (struct fm10k_hw*) ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,size_t,int) ; 
 int /*<<< orphan*/  netif_set_xps_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_configure_tx_ring(struct fm10k_intfc *interface,
				    struct fm10k_ring *ring)
{
	struct fm10k_hw *hw = &interface->hw;
	u64 tdba = ring->dma;
	u32 size = ring->count * sizeof(struct fm10k_tx_desc);
	u32 txint = FM10K_INT_MAP_DISABLE;
	u32 txdctl = BIT(FM10K_TXDCTL_MAX_TIME_SHIFT) | FM10K_TXDCTL_ENABLE;
	u8 reg_idx = ring->reg_idx;

	/* disable queue to avoid issues while updating state */
	fm10k_write_reg(hw, FM10K_TXDCTL(reg_idx), 0);
	fm10k_write_flush(hw);

	/* possible poll here to verify ring resources have been cleaned */

	/* set location and size for descriptor ring */
	fm10k_write_reg(hw, FM10K_TDBAL(reg_idx), tdba & DMA_BIT_MASK(32));
	fm10k_write_reg(hw, FM10K_TDBAH(reg_idx), tdba >> 32);
	fm10k_write_reg(hw, FM10K_TDLEN(reg_idx), size);

	/* reset head and tail pointers */
	fm10k_write_reg(hw, FM10K_TDH(reg_idx), 0);
	fm10k_write_reg(hw, FM10K_TDT(reg_idx), 0);

	/* store tail pointer */
	ring->tail = &interface->uc_addr[FM10K_TDT(reg_idx)];

	/* reset ntu and ntc to place SW in sync with hardware */
	ring->next_to_clean = 0;
	ring->next_to_use = 0;

	/* Map interrupt */
	if (ring->q_vector) {
		txint = ring->q_vector->v_idx + NON_Q_VECTORS;
		txint |= FM10K_INT_MAP_TIMER0;
	}

	fm10k_write_reg(hw, FM10K_TXINT(reg_idx), txint);

	/* enable use of FTAG bit in Tx descriptor, register is RO for VF */
	fm10k_write_reg(hw, FM10K_PFVTCTL(reg_idx),
			FM10K_PFVTCTL_FTAG_DESC_ENABLE);

	/* Initialize XPS */
	if (!test_and_set_bit(__FM10K_TX_XPS_INIT_DONE, ring->state) &&
	    ring->q_vector)
		netif_set_xps_queue(ring->netdev,
				    &ring->q_vector->affinity_mask,
				    ring->queue_index);

	/* enable queue */
	fm10k_write_reg(hw, FM10K_TXDCTL(reg_idx), txdctl);
}