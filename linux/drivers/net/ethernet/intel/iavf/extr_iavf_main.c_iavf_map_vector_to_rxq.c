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
struct iavf_ring {int /*<<< orphan*/  itr_setting; int /*<<< orphan*/ * vsi; struct iavf_ring* next; struct iavf_q_vector* q_vector; } ;
struct TYPE_2__ {int target_itr; int current_itr; scalar_t__ next_update; int /*<<< orphan*/  count; struct iavf_ring* ring; } ;
struct iavf_q_vector {TYPE_1__ rx; int /*<<< orphan*/  reg_idx; int /*<<< orphan*/  ring_mask; } ;
struct iavf_hw {int dummy; } ;
struct iavf_adapter {int /*<<< orphan*/  vsi; struct iavf_hw hw; struct iavf_ring* rx_rings; struct iavf_q_vector* q_vectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  IAVF_RX_ITR ; 
 int /*<<< orphan*/  IAVF_VFINT_ITRN1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ITR_TO_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  wr32 (struct iavf_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
iavf_map_vector_to_rxq(struct iavf_adapter *adapter, int v_idx, int r_idx)
{
	struct iavf_q_vector *q_vector = &adapter->q_vectors[v_idx];
	struct iavf_ring *rx_ring = &adapter->rx_rings[r_idx];
	struct iavf_hw *hw = &adapter->hw;

	rx_ring->q_vector = q_vector;
	rx_ring->next = q_vector->rx.ring;
	rx_ring->vsi = &adapter->vsi;
	q_vector->rx.ring = rx_ring;
	q_vector->rx.count++;
	q_vector->rx.next_update = jiffies + 1;
	q_vector->rx.target_itr = ITR_TO_REG(rx_ring->itr_setting);
	q_vector->ring_mask |= BIT(r_idx);
	wr32(hw, IAVF_VFINT_ITRN1(IAVF_RX_ITR, q_vector->reg_idx),
	     q_vector->rx.current_itr >> 1);
	q_vector->rx.current_itr = q_vector->rx.target_itr;
}