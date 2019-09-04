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
struct i40e_hw {int dummy; } ;
struct i40evf_adapter {int /*<<< orphan*/  vsi; struct i40e_hw hw; struct i40e_ring* tx_rings; struct i40e_q_vector* q_vectors; } ;
struct i40e_ring {int /*<<< orphan*/  itr_setting; int /*<<< orphan*/ * vsi; struct i40e_ring* next; struct i40e_q_vector* q_vector; } ;
struct TYPE_2__ {int /*<<< orphan*/  target_itr; int /*<<< orphan*/  current_itr; scalar_t__ next_update; int /*<<< orphan*/  count; struct i40e_ring* ring; } ;
struct i40e_q_vector {TYPE_1__ tx; int /*<<< orphan*/  reg_idx; int /*<<< orphan*/  num_ringpairs; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_TX_ITR ; 
 int /*<<< orphan*/  I40E_VFINT_ITRN1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITR_TO_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
i40evf_map_vector_to_txq(struct i40evf_adapter *adapter, int v_idx, int t_idx)
{
	struct i40e_q_vector *q_vector = &adapter->q_vectors[v_idx];
	struct i40e_ring *tx_ring = &adapter->tx_rings[t_idx];
	struct i40e_hw *hw = &adapter->hw;

	tx_ring->q_vector = q_vector;
	tx_ring->next = q_vector->tx.ring;
	tx_ring->vsi = &adapter->vsi;
	q_vector->tx.ring = tx_ring;
	q_vector->tx.count++;
	q_vector->tx.next_update = jiffies + 1;
	q_vector->tx.target_itr = ITR_TO_REG(tx_ring->itr_setting);
	q_vector->num_ringpairs++;
	wr32(hw, I40E_VFINT_ITRN1(I40E_TX_ITR, q_vector->reg_idx),
	     q_vector->tx.target_itr);
	q_vector->tx.current_itr = q_vector->tx.target_itr;
}