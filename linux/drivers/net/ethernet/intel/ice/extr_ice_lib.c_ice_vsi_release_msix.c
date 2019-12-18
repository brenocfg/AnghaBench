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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ice_vsi {int num_q_vectors; int /*<<< orphan*/ * rxq_map; int /*<<< orphan*/ * txq_map; struct ice_q_vector** q_vectors; struct ice_pf* back; } ;
struct ice_q_vector {int num_ring_tx; int num_ring_rx; int /*<<< orphan*/  reg_idx; } ;
struct ice_hw {int dummy; } ;
struct ice_pf {struct ice_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLINT_ITR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICE_IDX_ITR0 ; 
 int /*<<< orphan*/  ICE_IDX_ITR1 ; 
 int /*<<< orphan*/  QINT_RQCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QINT_TQCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_flush (struct ice_hw*) ; 
 int /*<<< orphan*/  wr32 (struct ice_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_vsi_release_msix(struct ice_vsi *vsi)
{
	struct ice_pf *pf = vsi->back;
	struct ice_hw *hw = &pf->hw;
	u32 txq = 0;
	u32 rxq = 0;
	int i, q;

	for (i = 0; i < vsi->num_q_vectors; i++) {
		struct ice_q_vector *q_vector = vsi->q_vectors[i];
		u16 reg_idx = q_vector->reg_idx;

		wr32(hw, GLINT_ITR(ICE_IDX_ITR0, reg_idx), 0);
		wr32(hw, GLINT_ITR(ICE_IDX_ITR1, reg_idx), 0);
		for (q = 0; q < q_vector->num_ring_tx; q++) {
			wr32(hw, QINT_TQCTL(vsi->txq_map[txq]), 0);
			txq++;
		}

		for (q = 0; q < q_vector->num_ring_rx; q++) {
			wr32(hw, QINT_RQCTL(vsi->rxq_map[rxq]), 0);
			rxq++;
		}
	}

	ice_flush(hw);
}