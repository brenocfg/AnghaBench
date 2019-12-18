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
typedef  size_t u32 ;
struct bnxt_ring_struct {size_t map_idx; size_t handle; size_t grp_idx; int /*<<< orphan*/  fw_ring_id; } ;
struct bnxt_tx_ring_info {int /*<<< orphan*/  tx_db; struct bnxt_ring_struct tx_ring_struct; struct bnxt_napi* bnapi; } ;
struct bnxt_rx_ring_info {int /*<<< orphan*/  rx_prod; int /*<<< orphan*/  rx_db; int /*<<< orphan*/  rx_agg_prod; int /*<<< orphan*/  rx_agg_db; struct bnxt_ring_struct rx_agg_ring_struct; struct bnxt_napi* bnapi; struct bnxt_ring_struct rx_ring_struct; } ;
struct bnxt_cp_ring_info {int /*<<< orphan*/  cp_raw_cons; int /*<<< orphan*/  cp_db; struct bnxt_ring_struct cp_ring_struct; struct bnxt_cp_ring_info** cp_ring_arr; } ;
struct bnxt_napi {size_t index; struct bnxt_cp_ring_info cp_ring; } ;
struct bnxt {int flags; int cp_nr_rings; int tx_nr_rings; int rx_nr_rings; TYPE_2__* grp_info; struct bnxt_rx_ring_info* rx_ring; struct bnxt_tx_ring_info* tx_ring; int /*<<< orphan*/  dev; TYPE_1__* irq_tbl; struct bnxt_napi** bnapi; } ;
struct TYPE_4__ {int /*<<< orphan*/  agg_fw_ring_id; int /*<<< orphan*/  rx_fw_ring_id; int /*<<< orphan*/  cp_fw_ring_id; } ;
struct TYPE_3__ {unsigned int vector; } ;

/* Variables and functions */
 int BNXT_FLAG_AGG_RINGS ; 
 int BNXT_FLAG_CHIP_P5 ; 
 size_t BNXT_RX_HDL ; 
 size_t BNXT_TX_HDL ; 
 size_t HWRM_RING_ALLOC_AGG ; 
 size_t HWRM_RING_ALLOC_CMPL ; 
 size_t HWRM_RING_ALLOC_NQ ; 
 size_t HWRM_RING_ALLOC_RX ; 
 size_t HWRM_RING_ALLOC_TX ; 
 int /*<<< orphan*/  bnxt_db_cq (struct bnxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_db_nq (struct bnxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_db_write (struct bnxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bnxt_hwrm_set_async_event_cr (struct bnxt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_set_db (struct bnxt*,int /*<<< orphan*/ *,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_nosync (unsigned int) ; 
 int /*<<< orphan*/  enable_irq (unsigned int) ; 
 int hwrm_ring_alloc_send_msg (struct bnxt*,struct bnxt_ring_struct*,size_t,size_t) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int bnxt_hwrm_ring_alloc(struct bnxt *bp)
{
	bool agg_rings = !!(bp->flags & BNXT_FLAG_AGG_RINGS);
	int i, rc = 0;
	u32 type;

	if (bp->flags & BNXT_FLAG_CHIP_P5)
		type = HWRM_RING_ALLOC_NQ;
	else
		type = HWRM_RING_ALLOC_CMPL;
	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_napi *bnapi = bp->bnapi[i];
		struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
		struct bnxt_ring_struct *ring = &cpr->cp_ring_struct;
		u32 map_idx = ring->map_idx;
		unsigned int vector;

		vector = bp->irq_tbl[map_idx].vector;
		disable_irq_nosync(vector);
		rc = hwrm_ring_alloc_send_msg(bp, ring, type, map_idx);
		if (rc) {
			enable_irq(vector);
			goto err_out;
		}
		bnxt_set_db(bp, &cpr->cp_db, type, map_idx, ring->fw_ring_id);
		bnxt_db_nq(bp, &cpr->cp_db, cpr->cp_raw_cons);
		enable_irq(vector);
		bp->grp_info[i].cp_fw_ring_id = ring->fw_ring_id;

		if (!i) {
			rc = bnxt_hwrm_set_async_event_cr(bp, ring->fw_ring_id);
			if (rc)
				netdev_warn(bp->dev, "Failed to set async event completion ring.\n");
		}
	}

	type = HWRM_RING_ALLOC_TX;
	for (i = 0; i < bp->tx_nr_rings; i++) {
		struct bnxt_tx_ring_info *txr = &bp->tx_ring[i];
		struct bnxt_ring_struct *ring;
		u32 map_idx;

		if (bp->flags & BNXT_FLAG_CHIP_P5) {
			struct bnxt_napi *bnapi = txr->bnapi;
			struct bnxt_cp_ring_info *cpr, *cpr2;
			u32 type2 = HWRM_RING_ALLOC_CMPL;

			cpr = &bnapi->cp_ring;
			cpr2 = cpr->cp_ring_arr[BNXT_TX_HDL];
			ring = &cpr2->cp_ring_struct;
			ring->handle = BNXT_TX_HDL;
			map_idx = bnapi->index;
			rc = hwrm_ring_alloc_send_msg(bp, ring, type2, map_idx);
			if (rc)
				goto err_out;
			bnxt_set_db(bp, &cpr2->cp_db, type2, map_idx,
				    ring->fw_ring_id);
			bnxt_db_cq(bp, &cpr2->cp_db, cpr2->cp_raw_cons);
		}
		ring = &txr->tx_ring_struct;
		map_idx = i;
		rc = hwrm_ring_alloc_send_msg(bp, ring, type, map_idx);
		if (rc)
			goto err_out;
		bnxt_set_db(bp, &txr->tx_db, type, map_idx, ring->fw_ring_id);
	}

	type = HWRM_RING_ALLOC_RX;
	for (i = 0; i < bp->rx_nr_rings; i++) {
		struct bnxt_rx_ring_info *rxr = &bp->rx_ring[i];
		struct bnxt_ring_struct *ring = &rxr->rx_ring_struct;
		struct bnxt_napi *bnapi = rxr->bnapi;
		u32 map_idx = bnapi->index;

		rc = hwrm_ring_alloc_send_msg(bp, ring, type, map_idx);
		if (rc)
			goto err_out;
		bnxt_set_db(bp, &rxr->rx_db, type, map_idx, ring->fw_ring_id);
		/* If we have agg rings, post agg buffers first. */
		if (!agg_rings)
			bnxt_db_write(bp, &rxr->rx_db, rxr->rx_prod);
		bp->grp_info[map_idx].rx_fw_ring_id = ring->fw_ring_id;
		if (bp->flags & BNXT_FLAG_CHIP_P5) {
			struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
			u32 type2 = HWRM_RING_ALLOC_CMPL;
			struct bnxt_cp_ring_info *cpr2;

			cpr2 = cpr->cp_ring_arr[BNXT_RX_HDL];
			ring = &cpr2->cp_ring_struct;
			ring->handle = BNXT_RX_HDL;
			rc = hwrm_ring_alloc_send_msg(bp, ring, type2, map_idx);
			if (rc)
				goto err_out;
			bnxt_set_db(bp, &cpr2->cp_db, type2, map_idx,
				    ring->fw_ring_id);
			bnxt_db_cq(bp, &cpr2->cp_db, cpr2->cp_raw_cons);
		}
	}

	if (agg_rings) {
		type = HWRM_RING_ALLOC_AGG;
		for (i = 0; i < bp->rx_nr_rings; i++) {
			struct bnxt_rx_ring_info *rxr = &bp->rx_ring[i];
			struct bnxt_ring_struct *ring =
						&rxr->rx_agg_ring_struct;
			u32 grp_idx = ring->grp_idx;
			u32 map_idx = grp_idx + bp->rx_nr_rings;

			rc = hwrm_ring_alloc_send_msg(bp, ring, type, map_idx);
			if (rc)
				goto err_out;

			bnxt_set_db(bp, &rxr->rx_agg_db, type, map_idx,
				    ring->fw_ring_id);
			bnxt_db_write(bp, &rxr->rx_agg_db, rxr->rx_agg_prod);
			bnxt_db_write(bp, &rxr->rx_db, rxr->rx_prod);
			bp->grp_info[grp_idx].agg_fw_ring_id = ring->fw_ring_id;
		}
	}
err_out:
	return rc;
}