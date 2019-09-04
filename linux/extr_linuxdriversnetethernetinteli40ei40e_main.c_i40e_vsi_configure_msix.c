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
typedef  int u16 ;
struct i40e_vsi {int base_queue; int base_vector; int num_q_vectors; int alloc_queue_pairs; int /*<<< orphan*/  int_rate_limit; TYPE_3__** tx_rings; TYPE_1__** rx_rings; struct i40e_q_vector** q_vectors; struct i40e_pf* back; } ;
struct TYPE_8__ {int target_itr; int current_itr; void* next_update; } ;
struct TYPE_6__ {int target_itr; int current_itr; void* next_update; } ;
struct i40e_q_vector {int num_ringpairs; TYPE_4__ tx; TYPE_2__ rx; } ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {struct i40e_hw hw; } ;
struct TYPE_7__ {int /*<<< orphan*/  itr_setting; } ;
struct TYPE_5__ {int /*<<< orphan*/  itr_setting; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PFINT_ITRN (int,int) ; 
 int /*<<< orphan*/  I40E_PFINT_LNKLSTN (int) ; 
 int /*<<< orphan*/  I40E_PFINT_RATEN (int) ; 
 int /*<<< orphan*/  I40E_QINT_RQCTL (int) ; 
 int I40E_QINT_RQCTL_CAUSE_ENA_MASK ; 
 int I40E_QINT_RQCTL_ITR_INDX_SHIFT ; 
 int I40E_QINT_RQCTL_MSIX_INDX_SHIFT ; 
 int I40E_QINT_RQCTL_NEXTQ_INDX_SHIFT ; 
 int I40E_QINT_RQCTL_NEXTQ_TYPE_SHIFT ; 
 int /*<<< orphan*/  I40E_QINT_TQCTL (int) ; 
 int I40E_QINT_TQCTL_CAUSE_ENA_MASK ; 
 int I40E_QINT_TQCTL_ITR_INDX_SHIFT ; 
 int I40E_QINT_TQCTL_MSIX_INDX_SHIFT ; 
 int I40E_QINT_TQCTL_NEXTQ_INDX_SHIFT ; 
 int I40E_QINT_TQCTL_NEXTQ_TYPE_SHIFT ; 
 int I40E_QUEUE_END_OF_LIST ; 
 int I40E_QUEUE_TYPE_RX ; 
 int I40E_QUEUE_TYPE_TX ; 
 int I40E_RX_ITR ; 
 int I40E_TX_ITR ; 
 void* ITR_TO_REG (int /*<<< orphan*/ ) ; 
 int i40e_enabled_xdp_vsi (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_flush (struct i40e_hw*) ; 
 int i40e_intrl_usec_to_reg (int /*<<< orphan*/ ) ; 
 void* jiffies ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void i40e_vsi_configure_msix(struct i40e_vsi *vsi)
{
	bool has_xdp = i40e_enabled_xdp_vsi(vsi);
	struct i40e_pf *pf = vsi->back;
	struct i40e_hw *hw = &pf->hw;
	u16 vector;
	int i, q;
	u32 qp;

	/* The interrupt indexing is offset by 1 in the PFINT_ITRn
	 * and PFINT_LNKLSTn registers, e.g.:
	 *   PFINT_ITRn[0..n-1] gets msix-1..msix-n  (qpair interrupts)
	 */
	qp = vsi->base_queue;
	vector = vsi->base_vector;
	for (i = 0; i < vsi->num_q_vectors; i++, vector++) {
		struct i40e_q_vector *q_vector = vsi->q_vectors[i];

		q_vector->rx.next_update = jiffies + 1;
		q_vector->rx.target_itr =
			ITR_TO_REG(vsi->rx_rings[i]->itr_setting);
		wr32(hw, I40E_PFINT_ITRN(I40E_RX_ITR, vector - 1),
		     q_vector->rx.target_itr);
		q_vector->rx.current_itr = q_vector->rx.target_itr;

		q_vector->tx.next_update = jiffies + 1;
		q_vector->tx.target_itr =
			ITR_TO_REG(vsi->tx_rings[i]->itr_setting);
		wr32(hw, I40E_PFINT_ITRN(I40E_TX_ITR, vector - 1),
		     q_vector->tx.target_itr);
		q_vector->tx.current_itr = q_vector->tx.target_itr;

		wr32(hw, I40E_PFINT_RATEN(vector - 1),
		     i40e_intrl_usec_to_reg(vsi->int_rate_limit));

		/* Linked list for the queuepairs assigned to this vector */
		wr32(hw, I40E_PFINT_LNKLSTN(vector - 1), qp);
		for (q = 0; q < q_vector->num_ringpairs; q++) {
			u32 nextqp = has_xdp ? qp + vsi->alloc_queue_pairs : qp;
			u32 val;

			val = I40E_QINT_RQCTL_CAUSE_ENA_MASK |
			      (I40E_RX_ITR << I40E_QINT_RQCTL_ITR_INDX_SHIFT) |
			      (vector << I40E_QINT_RQCTL_MSIX_INDX_SHIFT) |
			      (nextqp << I40E_QINT_RQCTL_NEXTQ_INDX_SHIFT) |
			      (I40E_QUEUE_TYPE_TX <<
			       I40E_QINT_RQCTL_NEXTQ_TYPE_SHIFT);

			wr32(hw, I40E_QINT_RQCTL(qp), val);

			if (has_xdp) {
				val = I40E_QINT_TQCTL_CAUSE_ENA_MASK |
				      (I40E_TX_ITR << I40E_QINT_TQCTL_ITR_INDX_SHIFT) |
				      (vector << I40E_QINT_TQCTL_MSIX_INDX_SHIFT) |
				      (qp << I40E_QINT_TQCTL_NEXTQ_INDX_SHIFT) |
				      (I40E_QUEUE_TYPE_TX <<
				       I40E_QINT_TQCTL_NEXTQ_TYPE_SHIFT);

				wr32(hw, I40E_QINT_TQCTL(nextqp), val);
			}

			val = I40E_QINT_TQCTL_CAUSE_ENA_MASK |
			      (I40E_TX_ITR << I40E_QINT_TQCTL_ITR_INDX_SHIFT) |
			      (vector << I40E_QINT_TQCTL_MSIX_INDX_SHIFT) |
			      ((qp + 1) << I40E_QINT_TQCTL_NEXTQ_INDX_SHIFT) |
			      (I40E_QUEUE_TYPE_RX <<
			       I40E_QINT_TQCTL_NEXTQ_TYPE_SHIFT);

			/* Terminate the linked list */
			if (q == (q_vector->num_ringpairs - 1))
				val |= (I40E_QUEUE_END_OF_LIST <<
					I40E_QINT_TQCTL_NEXTQ_INDX_SHIFT);

			wr32(hw, I40E_QINT_TQCTL(qp), val);
			qp++;
		}
	}

	i40e_flush(hw);
}