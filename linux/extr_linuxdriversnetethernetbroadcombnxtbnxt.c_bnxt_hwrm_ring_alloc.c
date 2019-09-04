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
typedef  int u32 ;
struct bnxt_ring_struct {int map_idx; int grp_idx; int /*<<< orphan*/  fw_ring_id; } ;
struct bnxt_tx_ring_info {scalar_t__ tx_doorbell; struct bnxt_ring_struct tx_ring_struct; } ;
struct bnxt_rx_ring_info {int rx_prod; int rx_agg_prod; scalar_t__ rx_agg_doorbell; struct bnxt_ring_struct rx_agg_ring_struct; scalar_t__ rx_doorbell; TYPE_1__* bnapi; struct bnxt_ring_struct rx_ring_struct; } ;
struct bnxt_cp_ring_info {int /*<<< orphan*/  cp_raw_cons; scalar_t__ cp_doorbell; struct bnxt_ring_struct cp_ring_struct; } ;
struct bnxt_napi {struct bnxt_cp_ring_info cp_ring; } ;
struct bnxt {int cp_nr_rings; int tx_nr_rings; int rx_nr_rings; int flags; TYPE_2__* grp_info; scalar_t__ bar1; struct bnxt_rx_ring_info* rx_ring; struct bnxt_tx_ring_info* tx_ring; int /*<<< orphan*/  dev; struct bnxt_napi** bnapi; } ;
struct TYPE_4__ {int /*<<< orphan*/  agg_fw_ring_id; int /*<<< orphan*/  rx_fw_ring_id; int /*<<< orphan*/  cp_fw_ring_id; } ;
struct TYPE_3__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_CP_DB (scalar_t__,int /*<<< orphan*/ ) ; 
 int BNXT_FLAG_AGG_RINGS ; 
 int DB_KEY_RX ; 
 int /*<<< orphan*/  HWRM_RING_ALLOC_AGG ; 
 int /*<<< orphan*/  HWRM_RING_ALLOC_CMPL ; 
 int /*<<< orphan*/  HWRM_RING_ALLOC_RX ; 
 int /*<<< orphan*/  HWRM_RING_ALLOC_TX ; 
 int bnxt_hwrm_set_async_event_cr (struct bnxt*,int /*<<< orphan*/ ) ; 
 int hwrm_ring_alloc_send_msg (struct bnxt*,struct bnxt_ring_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int bnxt_hwrm_ring_alloc(struct bnxt *bp)
{
	int i, rc = 0;

	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_napi *bnapi = bp->bnapi[i];
		struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
		struct bnxt_ring_struct *ring = &cpr->cp_ring_struct;
		u32 map_idx = ring->map_idx;

		cpr->cp_doorbell = bp->bar1 + map_idx * 0x80;
		rc = hwrm_ring_alloc_send_msg(bp, ring, HWRM_RING_ALLOC_CMPL,
					      map_idx);
		if (rc)
			goto err_out;
		BNXT_CP_DB(cpr->cp_doorbell, cpr->cp_raw_cons);
		bp->grp_info[i].cp_fw_ring_id = ring->fw_ring_id;

		if (!i) {
			rc = bnxt_hwrm_set_async_event_cr(bp, ring->fw_ring_id);
			if (rc)
				netdev_warn(bp->dev, "Failed to set async event completion ring.\n");
		}
	}

	for (i = 0; i < bp->tx_nr_rings; i++) {
		struct bnxt_tx_ring_info *txr = &bp->tx_ring[i];
		struct bnxt_ring_struct *ring = &txr->tx_ring_struct;
		u32 map_idx = i;

		rc = hwrm_ring_alloc_send_msg(bp, ring, HWRM_RING_ALLOC_TX,
					      map_idx);
		if (rc)
			goto err_out;
		txr->tx_doorbell = bp->bar1 + map_idx * 0x80;
	}

	for (i = 0; i < bp->rx_nr_rings; i++) {
		struct bnxt_rx_ring_info *rxr = &bp->rx_ring[i];
		struct bnxt_ring_struct *ring = &rxr->rx_ring_struct;
		u32 map_idx = rxr->bnapi->index;

		rc = hwrm_ring_alloc_send_msg(bp, ring, HWRM_RING_ALLOC_RX,
					      map_idx);
		if (rc)
			goto err_out;
		rxr->rx_doorbell = bp->bar1 + map_idx * 0x80;
		writel(DB_KEY_RX | rxr->rx_prod, rxr->rx_doorbell);
		bp->grp_info[map_idx].rx_fw_ring_id = ring->fw_ring_id;
	}

	if (bp->flags & BNXT_FLAG_AGG_RINGS) {
		for (i = 0; i < bp->rx_nr_rings; i++) {
			struct bnxt_rx_ring_info *rxr = &bp->rx_ring[i];
			struct bnxt_ring_struct *ring =
						&rxr->rx_agg_ring_struct;
			u32 grp_idx = ring->grp_idx;
			u32 map_idx = grp_idx + bp->rx_nr_rings;

			rc = hwrm_ring_alloc_send_msg(bp, ring,
						      HWRM_RING_ALLOC_AGG,
						      map_idx);
			if (rc)
				goto err_out;

			rxr->rx_agg_doorbell = bp->bar1 + map_idx * 0x80;
			writel(DB_KEY_RX | rxr->rx_agg_prod,
			       rxr->rx_agg_doorbell);
			bp->grp_info[grp_idx].agg_fw_ring_id = ring->fw_ring_id;
		}
	}
err_out:
	return rc;
}