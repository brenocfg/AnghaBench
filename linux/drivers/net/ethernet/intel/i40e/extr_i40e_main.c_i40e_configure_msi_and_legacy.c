#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct i40e_vsi {int alloc_queue_pairs; TYPE_3__** tx_rings; TYPE_1__** rx_rings; struct i40e_pf* back; struct i40e_q_vector** q_vectors; } ;
struct TYPE_8__ {int target_itr; int current_itr; void* next_update; } ;
struct TYPE_6__ {int target_itr; int current_itr; void* next_update; } ;
struct i40e_q_vector {TYPE_4__ tx; TYPE_2__ rx; } ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {struct i40e_hw hw; } ;
struct TYPE_7__ {int /*<<< orphan*/  itr_setting; } ;
struct TYPE_5__ {int /*<<< orphan*/  itr_setting; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PFINT_ITR0 (int) ; 
 int /*<<< orphan*/  I40E_PFINT_LNKLST0 ; 
 int /*<<< orphan*/  I40E_QINT_RQCTL (int /*<<< orphan*/ ) ; 
 int I40E_QINT_RQCTL_CAUSE_ENA_MASK ; 
 int I40E_QINT_RQCTL_ITR_INDX_SHIFT ; 
 int I40E_QINT_RQCTL_NEXTQ_INDX_SHIFT ; 
 int /*<<< orphan*/  I40E_QINT_TQCTL (int) ; 
 int I40E_QINT_TQCTL_CAUSE_ENA_MASK ; 
 int I40E_QINT_TQCTL_ITR_INDX_SHIFT ; 
 int I40E_QINT_TQCTL_NEXTQ_INDX_SHIFT ; 
 int I40E_QINT_TQCTL_NEXTQ_TYPE_SHIFT ; 
 int I40E_QUEUE_END_OF_LIST ; 
 int I40E_QUEUE_TYPE_TX ; 
 int I40E_RX_ITR ; 
 int I40E_TX_ITR ; 
 void* ITR_TO_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_enable_misc_int_causes (struct i40e_pf*) ; 
 scalar_t__ i40e_enabled_xdp_vsi (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_flush (struct i40e_hw*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void i40e_configure_msi_and_legacy(struct i40e_vsi *vsi)
{
	u32 nextqp = i40e_enabled_xdp_vsi(vsi) ? vsi->alloc_queue_pairs : 0;
	struct i40e_q_vector *q_vector = vsi->q_vectors[0];
	struct i40e_pf *pf = vsi->back;
	struct i40e_hw *hw = &pf->hw;
	u32 val;

	/* set the ITR configuration */
	q_vector->rx.next_update = jiffies + 1;
	q_vector->rx.target_itr = ITR_TO_REG(vsi->rx_rings[0]->itr_setting);
	wr32(hw, I40E_PFINT_ITR0(I40E_RX_ITR), q_vector->rx.target_itr);
	q_vector->rx.current_itr = q_vector->rx.target_itr;
	q_vector->tx.next_update = jiffies + 1;
	q_vector->tx.target_itr = ITR_TO_REG(vsi->tx_rings[0]->itr_setting);
	wr32(hw, I40E_PFINT_ITR0(I40E_TX_ITR), q_vector->tx.target_itr);
	q_vector->tx.current_itr = q_vector->tx.target_itr;

	i40e_enable_misc_int_causes(pf);

	/* FIRSTQ_INDX = 0, FIRSTQ_TYPE = 0 (rx) */
	wr32(hw, I40E_PFINT_LNKLST0, 0);

	/* Associate the queue pair to the vector and enable the queue int */
	val = I40E_QINT_RQCTL_CAUSE_ENA_MASK		       |
	      (I40E_RX_ITR << I40E_QINT_RQCTL_ITR_INDX_SHIFT)  |
	      (nextqp	   << I40E_QINT_RQCTL_NEXTQ_INDX_SHIFT)|
	      (I40E_QUEUE_TYPE_TX << I40E_QINT_TQCTL_NEXTQ_TYPE_SHIFT);

	wr32(hw, I40E_QINT_RQCTL(0), val);

	if (i40e_enabled_xdp_vsi(vsi)) {
		val = I40E_QINT_TQCTL_CAUSE_ENA_MASK		     |
		      (I40E_TX_ITR << I40E_QINT_TQCTL_ITR_INDX_SHIFT)|
		      (I40E_QUEUE_TYPE_TX
		       << I40E_QINT_TQCTL_NEXTQ_TYPE_SHIFT);

		wr32(hw, I40E_QINT_TQCTL(nextqp), val);
	}

	val = I40E_QINT_TQCTL_CAUSE_ENA_MASK		      |
	      (I40E_TX_ITR << I40E_QINT_TQCTL_ITR_INDX_SHIFT) |
	      (I40E_QUEUE_END_OF_LIST << I40E_QINT_TQCTL_NEXTQ_INDX_SHIFT);

	wr32(hw, I40E_QINT_TQCTL(0), val);
	i40e_flush(hw);
}