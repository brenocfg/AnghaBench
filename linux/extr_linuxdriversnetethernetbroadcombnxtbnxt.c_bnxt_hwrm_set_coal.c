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
struct hwrm_ring_cmpl_ring_cfg_aggint_params_input {int /*<<< orphan*/  ring_id; int /*<<< orphan*/  member_0; } ;
struct bnxt_napi {int /*<<< orphan*/  rx_ring; } ;
struct bnxt {int cp_nr_rings; int /*<<< orphan*/  hwrm_cmd_lock; TYPE_1__* grp_info; struct bnxt_napi** bnapi; int /*<<< orphan*/  tx_coal; int /*<<< orphan*/  rx_coal; } ;
struct TYPE_2__ {int /*<<< orphan*/  cp_fw_ring_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_RING_CMPL_RING_CFG_AGGINT_PARAMS ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_ring_cmpl_ring_cfg_aggint_params_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_ring_cmpl_ring_cfg_aggint_params_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bnxt_hwrm_set_coal_params (int /*<<< orphan*/ *,struct hwrm_ring_cmpl_ring_cfg_aggint_params_input*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int bnxt_hwrm_set_coal(struct bnxt *bp)
{
	int i, rc = 0;
	struct hwrm_ring_cmpl_ring_cfg_aggint_params_input req_rx = {0},
							   req_tx = {0}, *req;

	bnxt_hwrm_cmd_hdr_init(bp, &req_rx,
			       HWRM_RING_CMPL_RING_CFG_AGGINT_PARAMS, -1, -1);
	bnxt_hwrm_cmd_hdr_init(bp, &req_tx,
			       HWRM_RING_CMPL_RING_CFG_AGGINT_PARAMS, -1, -1);

	bnxt_hwrm_set_coal_params(&bp->rx_coal, &req_rx);
	bnxt_hwrm_set_coal_params(&bp->tx_coal, &req_tx);

	mutex_lock(&bp->hwrm_cmd_lock);
	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_napi *bnapi = bp->bnapi[i];

		req = &req_rx;
		if (!bnapi->rx_ring)
			req = &req_tx;
		req->ring_id = cpu_to_le16(bp->grp_info[i].cp_fw_ring_id);

		rc = _hwrm_send_message(bp, req, sizeof(*req),
					HWRM_CMD_TIMEOUT);
		if (rc)
			break;
	}
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}