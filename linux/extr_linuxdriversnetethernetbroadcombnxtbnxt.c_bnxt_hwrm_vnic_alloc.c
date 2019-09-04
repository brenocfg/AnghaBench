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
typedef  size_t u16 ;
struct hwrm_vnic_alloc_output {int /*<<< orphan*/  vnic_id; } ;
struct hwrm_vnic_alloc_input {int /*<<< orphan*/  flags; int /*<<< orphan*/  member_0; } ;
struct bnxt {int /*<<< orphan*/  hwrm_cmd_lock; TYPE_4__* vnic_info; TYPE_3__* grp_info; int /*<<< orphan*/  dev; TYPE_2__* rx_ring; struct hwrm_vnic_alloc_output* hwrm_cmd_resp_addr; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_8__ {scalar_t__* fw_grp_ids; int /*<<< orphan*/  fw_vnic_id; scalar_t__* fw_rss_cos_lb_ctx; } ;
struct TYPE_7__ {scalar_t__ fw_grp_id; } ;
struct TYPE_6__ {TYPE_1__* bnapi; } ;
struct TYPE_5__ {unsigned int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_VNIC_ALLOC ; 
 scalar_t__ INVALID_HW_RING_ID ; 
 int /*<<< orphan*/  VNIC_ALLOC_REQ_FLAGS_DEFAULT ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_vnic_alloc_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_vnic_alloc_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int bnxt_hwrm_vnic_alloc(struct bnxt *bp, u16 vnic_id,
				unsigned int start_rx_ring_idx,
				unsigned int nr_rings)
{
	int rc = 0;
	unsigned int i, j, grp_idx, end_idx = start_rx_ring_idx + nr_rings;
	struct hwrm_vnic_alloc_input req = {0};
	struct hwrm_vnic_alloc_output *resp = bp->hwrm_cmd_resp_addr;

	/* map ring groups to this vnic */
	for (i = start_rx_ring_idx, j = 0; i < end_idx; i++, j++) {
		grp_idx = bp->rx_ring[i].bnapi->index;
		if (bp->grp_info[grp_idx].fw_grp_id == INVALID_HW_RING_ID) {
			netdev_err(bp->dev, "Not enough ring groups avail:%x req:%x\n",
				   j, nr_rings);
			break;
		}
		bp->vnic_info[vnic_id].fw_grp_ids[j] =
					bp->grp_info[grp_idx].fw_grp_id;
	}

	bp->vnic_info[vnic_id].fw_rss_cos_lb_ctx[0] = INVALID_HW_RING_ID;
	bp->vnic_info[vnic_id].fw_rss_cos_lb_ctx[1] = INVALID_HW_RING_ID;
	if (vnic_id == 0)
		req.flags = cpu_to_le32(VNIC_ALLOC_REQ_FLAGS_DEFAULT);

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_ALLOC, -1, -1);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (!rc)
		bp->vnic_info[vnic_id].fw_vnic_id = le32_to_cpu(resp->vnic_id);
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}