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
typedef  int /*<<< orphan*/  u16 ;
struct hwrm_ring_cmpl_ring_cfg_aggint_params_input {void* ring_id; int /*<<< orphan*/  member_0; } ;
struct bnxt_napi {scalar_t__ rx_ring; scalar_t__ tx_ring; } ;
struct bnxt_coal {int dummy; } ;
struct bnxt {int cp_nr_rings; int flags; int /*<<< orphan*/  hwrm_cmd_lock; struct bnxt_coal tx_coal; struct bnxt_coal rx_coal; struct bnxt_napi** bnapi; } ;

/* Variables and functions */
 int BNXT_FLAG_CHIP_P5 ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_RING_CMPL_RING_CFG_AGGINT_PARAMS ; 
 int /*<<< orphan*/  __bnxt_hwrm_set_coal_nq (struct bnxt*,struct bnxt_napi*,struct bnxt_coal*) ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_ring_cmpl_ring_cfg_aggint_params_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_cp_ring_for_rx (struct bnxt*,scalar_t__) ; 
 int /*<<< orphan*/  bnxt_cp_ring_for_tx (struct bnxt*,scalar_t__) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_ring_cmpl_ring_cfg_aggint_params_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bnxt_hwrm_set_coal_params (struct bnxt*,struct bnxt_coal*,struct hwrm_ring_cmpl_ring_cfg_aggint_params_input*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
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

	bnxt_hwrm_set_coal_params(bp, &bp->rx_coal, &req_rx);
	bnxt_hwrm_set_coal_params(bp, &bp->tx_coal, &req_tx);

	mutex_lock(&bp->hwrm_cmd_lock);
	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_napi *bnapi = bp->bnapi[i];
		struct bnxt_coal *hw_coal;
		u16 ring_id;

		req = &req_rx;
		if (!bnapi->rx_ring) {
			ring_id = bnxt_cp_ring_for_tx(bp, bnapi->tx_ring);
			req = &req_tx;
		} else {
			ring_id = bnxt_cp_ring_for_rx(bp, bnapi->rx_ring);
		}
		req->ring_id = cpu_to_le16(ring_id);

		rc = _hwrm_send_message(bp, req, sizeof(*req),
					HWRM_CMD_TIMEOUT);
		if (rc)
			break;

		if (!(bp->flags & BNXT_FLAG_CHIP_P5))
			continue;

		if (bnapi->rx_ring && bnapi->tx_ring) {
			req = &req_tx;
			ring_id = bnxt_cp_ring_for_tx(bp, bnapi->tx_ring);
			req->ring_id = cpu_to_le16(ring_id);
			rc = _hwrm_send_message(bp, req, sizeof(*req),
						HWRM_CMD_TIMEOUT);
			if (rc)
				break;
		}
		if (bnapi->rx_ring)
			hw_coal = &bp->rx_coal;
		else
			hw_coal = &bp->tx_coal;
		__bnxt_hwrm_set_coal_nq(bp, bnapi, hw_coal);
	}
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}