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
typedef  int u32 ;
typedef  void* u16 ;
struct hwrm_ring_alloc_output {int /*<<< orphan*/  ring_id; int /*<<< orphan*/  error_code; } ;
struct hwrm_ring_alloc_input {int page_tbl_depth; int /*<<< orphan*/  int_mode; void* length; void* ring_type; void* queue_id; void* stat_ctx_id; void* cmpl_ring_id; void* logical_id; scalar_t__ fbo; void* page_tbl_addr; int /*<<< orphan*/  page_size; scalar_t__ enables; int /*<<< orphan*/  member_0; } ;
struct bnxt_ring_struct {int nr_pages; size_t grp_idx; int queue_id; void* fw_ring_id; int /*<<< orphan*/ * dma_arr; int /*<<< orphan*/  pg_tbl_map; } ;
struct bnxt_ring_grp_info {int cp_fw_ring_id; int /*<<< orphan*/  fw_stats_ctx; } ;
struct bnxt {int flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  hwrm_cmd_lock; int /*<<< orphan*/  cp_ring_mask; int /*<<< orphan*/  rx_agg_ring_mask; int /*<<< orphan*/  rx_ring_mask; int /*<<< orphan*/  tx_ring_mask; struct bnxt_ring_grp_info* grp_info; struct hwrm_ring_alloc_output* hwrm_cmd_resp_addr; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int BNXT_FLAG_USING_MSIX ; 
 int /*<<< orphan*/  BNXT_PAGE_SHIFT ; 
 int EIO ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_RING_ALLOC ; 
#define  HWRM_RING_ALLOC_AGG 131 
#define  HWRM_RING_ALLOC_CMPL 130 
#define  HWRM_RING_ALLOC_RX 129 
#define  HWRM_RING_ALLOC_TX 128 
 int /*<<< orphan*/  RING_ALLOC_REQ_INT_MODE_MSIX ; 
 void* RING_ALLOC_REQ_RING_TYPE_L2_CMPL ; 
 void* RING_ALLOC_REQ_RING_TYPE_RX ; 
 void* RING_ALLOC_REQ_RING_TYPE_TX ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_ring_alloc_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_ring_alloc_input*,int /*<<< orphan*/ ,int,int) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int hwrm_ring_alloc_send_msg(struct bnxt *bp,
				    struct bnxt_ring_struct *ring,
				    u32 ring_type, u32 map_index)
{
	int rc = 0, err = 0;
	struct hwrm_ring_alloc_input req = {0};
	struct hwrm_ring_alloc_output *resp = bp->hwrm_cmd_resp_addr;
	struct bnxt_ring_grp_info *grp_info;
	u16 ring_id;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_RING_ALLOC, -1, -1);

	req.enables = 0;
	if (ring->nr_pages > 1) {
		req.page_tbl_addr = cpu_to_le64(ring->pg_tbl_map);
		/* Page size is in log2 units */
		req.page_size = BNXT_PAGE_SHIFT;
		req.page_tbl_depth = 1;
	} else {
		req.page_tbl_addr =  cpu_to_le64(ring->dma_arr[0]);
	}
	req.fbo = 0;
	/* Association of ring index with doorbell index and MSIX number */
	req.logical_id = cpu_to_le16(map_index);

	switch (ring_type) {
	case HWRM_RING_ALLOC_TX:
		req.ring_type = RING_ALLOC_REQ_RING_TYPE_TX;
		/* Association of transmit ring with completion ring */
		grp_info = &bp->grp_info[ring->grp_idx];
		req.cmpl_ring_id = cpu_to_le16(grp_info->cp_fw_ring_id);
		req.length = cpu_to_le32(bp->tx_ring_mask + 1);
		req.stat_ctx_id = cpu_to_le32(grp_info->fw_stats_ctx);
		req.queue_id = cpu_to_le16(ring->queue_id);
		break;
	case HWRM_RING_ALLOC_RX:
		req.ring_type = RING_ALLOC_REQ_RING_TYPE_RX;
		req.length = cpu_to_le32(bp->rx_ring_mask + 1);
		break;
	case HWRM_RING_ALLOC_AGG:
		req.ring_type = RING_ALLOC_REQ_RING_TYPE_RX;
		req.length = cpu_to_le32(bp->rx_agg_ring_mask + 1);
		break;
	case HWRM_RING_ALLOC_CMPL:
		req.ring_type = RING_ALLOC_REQ_RING_TYPE_L2_CMPL;
		req.length = cpu_to_le32(bp->cp_ring_mask + 1);
		if (bp->flags & BNXT_FLAG_USING_MSIX)
			req.int_mode = RING_ALLOC_REQ_INT_MODE_MSIX;
		break;
	default:
		netdev_err(bp->dev, "hwrm alloc invalid ring type %d\n",
			   ring_type);
		return -1;
	}

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	err = le16_to_cpu(resp->error_code);
	ring_id = le16_to_cpu(resp->ring_id);
	mutex_unlock(&bp->hwrm_cmd_lock);

	if (rc || err) {
		netdev_err(bp->dev, "hwrm_ring_alloc type %d failed. rc:%x err:%x\n",
			   ring_type, rc, err);
		return -EIO;
	}
	ring->fw_ring_id = ring_id;
	return rc;
}