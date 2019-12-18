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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ice_vsi {int num_q_vectors; struct ice_q_vector** q_vectors; struct ice_pf* back; } ;
struct TYPE_4__ {int /*<<< orphan*/  itr_idx; } ;
struct TYPE_3__ {int /*<<< orphan*/  itr_idx; } ;
struct ice_q_vector {int num_ring_tx; int num_ring_rx; TYPE_2__ rx; TYPE_1__ tx; int /*<<< orphan*/  intrl; int /*<<< orphan*/  reg_idx; } ;
struct ice_hw {int /*<<< orphan*/  intrl_gran; } ;
struct ice_pf {struct ice_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLINT_RATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_cfg_itr (struct ice_hw*,struct ice_q_vector*) ; 
 int /*<<< orphan*/  ice_cfg_rxq_interrupt (struct ice_vsi*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_cfg_txq_interrupt (struct ice_vsi*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_intrl_usec_to_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct ice_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ice_vsi_cfg_msix(struct ice_vsi *vsi)
{
	struct ice_pf *pf = vsi->back;
	struct ice_hw *hw = &pf->hw;
	u32 txq = 0, rxq = 0;
	int i, q;

	for (i = 0; i < vsi->num_q_vectors; i++) {
		struct ice_q_vector *q_vector = vsi->q_vectors[i];
		u16 reg_idx = q_vector->reg_idx;

		ice_cfg_itr(hw, q_vector);

		wr32(hw, GLINT_RATE(reg_idx),
		     ice_intrl_usec_to_reg(q_vector->intrl, hw->intrl_gran));

		/* Both Transmit Queue Interrupt Cause Control register
		 * and Receive Queue Interrupt Cause control register
		 * expects MSIX_INDX field to be the vector index
		 * within the function space and not the absolute
		 * vector index across PF or across device.
		 * For SR-IOV VF VSIs queue vector index always starts
		 * with 1 since first vector index(0) is used for OICR
		 * in VF space. Since VMDq and other PF VSIs are within
		 * the PF function space, use the vector index that is
		 * tracked for this PF.
		 */
		for (q = 0; q < q_vector->num_ring_tx; q++) {
			ice_cfg_txq_interrupt(vsi, txq, reg_idx,
					      q_vector->tx.itr_idx);
			txq++;
		}

		for (q = 0; q < q_vector->num_ring_rx; q++) {
			ice_cfg_rxq_interrupt(vsi, rxq, reg_idx,
					      q_vector->rx.itr_idx);
			rxq++;
		}
	}
}