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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct ice_vsi {int /*<<< orphan*/  idx; int /*<<< orphan*/  port_info; struct ice_pf* back; } ;
struct ice_tlan_ctx {int /*<<< orphan*/  member_0; } ;
struct ice_ring {scalar_t__ reg_idx; int /*<<< orphan*/  txq_teid; scalar_t__ q_handle; scalar_t__ tail; } ;
struct TYPE_3__ {scalar_t__ hw_addr; } ;
struct ice_pf {TYPE_2__* pdev; TYPE_1__ hw; } ;
struct ice_aqc_add_txqs_perq {int /*<<< orphan*/  q_teid; int /*<<< orphan*/  txq_id; int /*<<< orphan*/  txq_ctx; } ;
struct ice_aqc_add_tx_qgrp {struct ice_aqc_add_txqs_perq* txqs; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ QTX_COMM_DBELL (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int ice_ena_vsi_txq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int,struct ice_aqc_add_tx_qgrp*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_set_ctx (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_setup_tx_ctx (struct ice_ring*,struct ice_tlan_ctx*,scalar_t__) ; 
 int /*<<< orphan*/  ice_tlan_ctx_info ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ice_vsi_cfg_txq(struct ice_vsi *vsi, struct ice_ring *ring, u16 tc_q_idx,
		struct ice_aqc_add_tx_qgrp *qg_buf, u8 tc)
{
	struct ice_tlan_ctx tlan_ctx = { 0 };
	struct ice_aqc_add_txqs_perq *txq;
	struct ice_pf *pf = vsi->back;
	u8 buf_len = sizeof(*qg_buf);
	enum ice_status status;
	u16 pf_q;

	pf_q = ring->reg_idx;
	ice_setup_tx_ctx(ring, &tlan_ctx, pf_q);
	/* copy context contents into the qg_buf */
	qg_buf->txqs[0].txq_id = cpu_to_le16(pf_q);
	ice_set_ctx((u8 *)&tlan_ctx, qg_buf->txqs[0].txq_ctx,
		    ice_tlan_ctx_info);

	/* init queue specific tail reg. It is referred as
	 * transmit comm scheduler queue doorbell.
	 */
	ring->tail = pf->hw.hw_addr + QTX_COMM_DBELL(pf_q);

	/* Add unique software queue handle of the Tx queue per
	 * TC into the VSI Tx ring
	 */
	ring->q_handle = tc_q_idx;

	status = ice_ena_vsi_txq(vsi->port_info, vsi->idx, tc, ring->q_handle,
				 1, qg_buf, buf_len, NULL);
	if (status) {
		dev_err(&pf->pdev->dev,
			"Failed to set LAN Tx queue context, error: %d\n",
			status);
		return -ENODEV;
	}

	/* Add Tx Queue TEID into the VSI Tx ring from the
	 * response. This will complete configuring and
	 * enabling the queue.
	 */
	txq = &qg_buf->txqs[0];
	if (pf_q == le16_to_cpu(txq->txq_id))
		ring->txq_teid = le32_to_cpu(txq->q_teid);

	return 0;
}