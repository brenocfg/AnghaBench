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
typedef  size_t u16 ;
struct hwrm_vnic_rss_cos_lb_ctx_free_input {int /*<<< orphan*/  rss_cos_lb_ctx_id; int /*<<< orphan*/  member_0; } ;
struct bnxt {TYPE_1__* vnic_info; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_2__ {int /*<<< orphan*/ * fw_rss_cos_lb_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_VNIC_RSS_COS_LB_CTX_FREE ; 
 int /*<<< orphan*/  INVALID_HW_RING_ID ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_vnic_rss_cos_lb_ctx_free_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwrm_send_message (struct bnxt*,struct hwrm_vnic_rss_cos_lb_ctx_free_input*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_hwrm_vnic_ctx_free_one(struct bnxt *bp, u16 vnic_id,
					u16 ctx_idx)
{
	struct hwrm_vnic_rss_cos_lb_ctx_free_input req = {0};

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_RSS_COS_LB_CTX_FREE, -1, -1);
	req.rss_cos_lb_ctx_id =
		cpu_to_le16(bp->vnic_info[vnic_id].fw_rss_cos_lb_ctx[ctx_idx]);

	hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	bp->vnic_info[vnic_id].fw_rss_cos_lb_ctx[ctx_idx] = INVALID_HW_RING_ID;
}