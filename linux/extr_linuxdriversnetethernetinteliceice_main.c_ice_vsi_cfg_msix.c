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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct ice_vsi {int base_vector; int num_q_vectors; int /*<<< orphan*/ * rxq_map; int /*<<< orphan*/ * txq_map; TYPE_2__** tx_rings; TYPE_1__** rx_rings; struct ice_q_vector** q_vectors; struct ice_pf* back; } ;
struct TYPE_8__ {size_t itr; void* latency_range; } ;
struct TYPE_7__ {size_t itr; void* latency_range; } ;
struct ice_q_vector {int num_ring_rx; int num_ring_tx; TYPE_4__ tx; TYPE_3__ rx; } ;
struct ice_hw {int /*<<< orphan*/  itr_gran_200; } ;
struct ice_pf {struct ice_hw hw; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_itr_setting; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_itr_setting; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLINT_ITR (int,int) ; 
 void* ICE_LOW_LATENCY ; 
 int ICE_RX_ITR ; 
 int ICE_TX_ITR ; 
 void* ITR_TO_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QINT_RQCTL (int /*<<< orphan*/ ) ; 
 int QINT_RQCTL_CAUSE_ENA_M ; 
 int QINT_RQCTL_ITR_INDX_S ; 
 int QINT_RQCTL_MSIX_INDX_S ; 
 int /*<<< orphan*/  QINT_TQCTL (int /*<<< orphan*/ ) ; 
 int QINT_TQCTL_CAUSE_ENA_M ; 
 int QINT_TQCTL_ITR_INDX_S ; 
 int QINT_TQCTL_MSIX_INDX_S ; 
 int /*<<< orphan*/  ice_flush (struct ice_hw*) ; 
 int /*<<< orphan*/  wr32 (struct ice_hw*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void ice_vsi_cfg_msix(struct ice_vsi *vsi)
{
	struct ice_pf *pf = vsi->back;
	u16 vector = vsi->base_vector;
	struct ice_hw *hw = &pf->hw;
	u32 txq = 0, rxq = 0;
	int i, q, itr;
	u8 itr_gran;

	for (i = 0; i < vsi->num_q_vectors; i++, vector++) {
		struct ice_q_vector *q_vector = vsi->q_vectors[i];

		itr_gran = hw->itr_gran_200;

		if (q_vector->num_ring_rx) {
			q_vector->rx.itr =
				ITR_TO_REG(vsi->rx_rings[rxq]->rx_itr_setting,
					   itr_gran);
			q_vector->rx.latency_range = ICE_LOW_LATENCY;
		}

		if (q_vector->num_ring_tx) {
			q_vector->tx.itr =
				ITR_TO_REG(vsi->tx_rings[txq]->tx_itr_setting,
					   itr_gran);
			q_vector->tx.latency_range = ICE_LOW_LATENCY;
		}
		wr32(hw, GLINT_ITR(ICE_RX_ITR, vector), q_vector->rx.itr);
		wr32(hw, GLINT_ITR(ICE_TX_ITR, vector), q_vector->tx.itr);

		/* Both Transmit Queue Interrupt Cause Control register
		 * and Receive Queue Interrupt Cause control register
		 * expects MSIX_INDX field to be the vector index
		 * within the function space and not the absolute
		 * vector index across PF or across device.
		 * For SR-IOV VF VSIs queue vector index always starts
		 * with 1 since first vector index(0) is used for OICR
		 * in VF space. Since VMDq and other PF VSIs are withtin
		 * the PF function space, use the vector index thats
		 * tracked for this PF.
		 */
		for (q = 0; q < q_vector->num_ring_tx; q++) {
			u32 val;

			itr = ICE_TX_ITR;
			val = QINT_TQCTL_CAUSE_ENA_M |
			      (itr << QINT_TQCTL_ITR_INDX_S)  |
			      (vector << QINT_TQCTL_MSIX_INDX_S);
			wr32(hw, QINT_TQCTL(vsi->txq_map[txq]), val);
			txq++;
		}

		for (q = 0; q < q_vector->num_ring_rx; q++) {
			u32 val;

			itr = ICE_RX_ITR;
			val = QINT_RQCTL_CAUSE_ENA_M |
			      (itr << QINT_RQCTL_ITR_INDX_S)  |
			      (vector << QINT_RQCTL_MSIX_INDX_S);
			wr32(hw, QINT_RQCTL(vsi->rxq_map[rxq]), val);
			rxq++;
		}
	}

	ice_flush(hw);
}