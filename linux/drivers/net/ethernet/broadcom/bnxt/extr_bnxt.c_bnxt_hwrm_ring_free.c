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
struct bnxt_ring_struct {scalar_t__ fw_ring_id; } ;
struct bnxt_tx_ring_info {struct bnxt_ring_struct tx_ring_struct; } ;
struct bnxt_rx_ring_info {TYPE_1__* bnapi; struct bnxt_ring_struct rx_agg_ring_struct; struct bnxt_ring_struct rx_ring_struct; } ;
struct bnxt_cp_ring_info {struct bnxt_ring_struct cp_ring_struct; struct bnxt_cp_ring_info** cp_ring_arr; } ;
struct bnxt_napi {struct bnxt_cp_ring_info cp_ring; } ;
struct bnxt {int tx_nr_rings; int rx_nr_rings; int flags; int cp_nr_rings; TYPE_2__* grp_info; struct bnxt_napi** bnapi; struct bnxt_rx_ring_info* rx_ring; struct bnxt_tx_ring_info* tx_ring; } ;
struct TYPE_4__ {scalar_t__ cp_fw_ring_id; scalar_t__ agg_fw_ring_id; scalar_t__ rx_fw_ring_id; } ;
struct TYPE_3__ {scalar_t__ index; } ;

/* Variables and functions */
 int BNXT_FLAG_CHIP_P5 ; 
 scalar_t__ INVALID_HW_RING_ID ; 
 scalar_t__ RING_FREE_REQ_RING_TYPE_L2_CMPL ; 
 scalar_t__ RING_FREE_REQ_RING_TYPE_NQ ; 
 scalar_t__ RING_FREE_REQ_RING_TYPE_RX ; 
 scalar_t__ RING_FREE_REQ_RING_TYPE_RX_AGG ; 
 scalar_t__ RING_FREE_REQ_RING_TYPE_TX ; 
 scalar_t__ bnxt_cp_ring_for_rx (struct bnxt*,struct bnxt_rx_ring_info*) ; 
 scalar_t__ bnxt_cp_ring_for_tx (struct bnxt*,struct bnxt_tx_ring_info*) ; 
 int /*<<< orphan*/  bnxt_disable_int_sync (struct bnxt*) ; 
 int /*<<< orphan*/  hwrm_ring_free_send_msg (struct bnxt*,struct bnxt_ring_struct*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void bnxt_hwrm_ring_free(struct bnxt *bp, bool close_path)
{
	u32 type;
	int i;

	if (!bp->bnapi)
		return;

	for (i = 0; i < bp->tx_nr_rings; i++) {
		struct bnxt_tx_ring_info *txr = &bp->tx_ring[i];
		struct bnxt_ring_struct *ring = &txr->tx_ring_struct;

		if (ring->fw_ring_id != INVALID_HW_RING_ID) {
			u32 cmpl_ring_id = bnxt_cp_ring_for_tx(bp, txr);

			hwrm_ring_free_send_msg(bp, ring,
						RING_FREE_REQ_RING_TYPE_TX,
						close_path ? cmpl_ring_id :
						INVALID_HW_RING_ID);
			ring->fw_ring_id = INVALID_HW_RING_ID;
		}
	}

	for (i = 0; i < bp->rx_nr_rings; i++) {
		struct bnxt_rx_ring_info *rxr = &bp->rx_ring[i];
		struct bnxt_ring_struct *ring = &rxr->rx_ring_struct;
		u32 grp_idx = rxr->bnapi->index;

		if (ring->fw_ring_id != INVALID_HW_RING_ID) {
			u32 cmpl_ring_id = bnxt_cp_ring_for_rx(bp, rxr);

			hwrm_ring_free_send_msg(bp, ring,
						RING_FREE_REQ_RING_TYPE_RX,
						close_path ? cmpl_ring_id :
						INVALID_HW_RING_ID);
			ring->fw_ring_id = INVALID_HW_RING_ID;
			bp->grp_info[grp_idx].rx_fw_ring_id =
				INVALID_HW_RING_ID;
		}
	}

	if (bp->flags & BNXT_FLAG_CHIP_P5)
		type = RING_FREE_REQ_RING_TYPE_RX_AGG;
	else
		type = RING_FREE_REQ_RING_TYPE_RX;
	for (i = 0; i < bp->rx_nr_rings; i++) {
		struct bnxt_rx_ring_info *rxr = &bp->rx_ring[i];
		struct bnxt_ring_struct *ring = &rxr->rx_agg_ring_struct;
		u32 grp_idx = rxr->bnapi->index;

		if (ring->fw_ring_id != INVALID_HW_RING_ID) {
			u32 cmpl_ring_id = bnxt_cp_ring_for_rx(bp, rxr);

			hwrm_ring_free_send_msg(bp, ring, type,
						close_path ? cmpl_ring_id :
						INVALID_HW_RING_ID);
			ring->fw_ring_id = INVALID_HW_RING_ID;
			bp->grp_info[grp_idx].agg_fw_ring_id =
				INVALID_HW_RING_ID;
		}
	}

	/* The completion rings are about to be freed.  After that the
	 * IRQ doorbell will not work anymore.  So we need to disable
	 * IRQ here.
	 */
	bnxt_disable_int_sync(bp);

	if (bp->flags & BNXT_FLAG_CHIP_P5)
		type = RING_FREE_REQ_RING_TYPE_NQ;
	else
		type = RING_FREE_REQ_RING_TYPE_L2_CMPL;
	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_napi *bnapi = bp->bnapi[i];
		struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
		struct bnxt_ring_struct *ring;
		int j;

		for (j = 0; j < 2; j++) {
			struct bnxt_cp_ring_info *cpr2 = cpr->cp_ring_arr[j];

			if (cpr2) {
				ring = &cpr2->cp_ring_struct;
				if (ring->fw_ring_id == INVALID_HW_RING_ID)
					continue;
				hwrm_ring_free_send_msg(bp, ring,
					RING_FREE_REQ_RING_TYPE_L2_CMPL,
					INVALID_HW_RING_ID);
				ring->fw_ring_id = INVALID_HW_RING_ID;
			}
		}
		ring = &cpr->cp_ring_struct;
		if (ring->fw_ring_id != INVALID_HW_RING_ID) {
			hwrm_ring_free_send_msg(bp, ring, type,
						INVALID_HW_RING_ID);
			ring->fw_ring_id = INVALID_HW_RING_ID;
			bp->grp_info[i].cp_fw_ring_id = INVALID_HW_RING_ID;
		}
	}
}