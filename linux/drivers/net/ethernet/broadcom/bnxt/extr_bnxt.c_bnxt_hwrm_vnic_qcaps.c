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
struct hwrm_vnic_qcaps_output {int /*<<< orphan*/  max_aggs_supported; int /*<<< orphan*/  flags; } ;
struct hwrm_vnic_qcaps_input {int /*<<< orphan*/  member_0; } ;
struct ctx_hw_stats_ext {int dummy; } ;
struct ctx_hw_stats {int dummy; } ;
struct bnxt {int hw_ring_stats_size; int flags; int hwrm_spec_code; int /*<<< orphan*/  hwrm_cmd_lock; int /*<<< orphan*/  max_tpa_v2; struct hwrm_vnic_qcaps_output* hwrm_cmd_resp_addr; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int BNXT_FLAG_CHIP_P5 ; 
 int BNXT_FLAG_NEW_RSS_CAP ; 
 int BNXT_FLAG_ROCE_MIRROR_CAP ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_VNIC_QCAPS ; 
 int VNIC_QCAPS_RESP_FLAGS_ROCE_MIRRORING_CAPABLE_VNIC_CAP ; 
 int VNIC_QCAPS_RESP_FLAGS_RSS_DFLT_CR_CAP ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_vnic_qcaps_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_vnic_qcaps_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_hwrm_vnic_qcaps(struct bnxt *bp)
{
	struct hwrm_vnic_qcaps_output *resp = bp->hwrm_cmd_resp_addr;
	struct hwrm_vnic_qcaps_input req = {0};
	int rc;

	bp->hw_ring_stats_size = sizeof(struct ctx_hw_stats);
	bp->flags &= ~(BNXT_FLAG_NEW_RSS_CAP | BNXT_FLAG_ROCE_MIRROR_CAP);
	if (bp->hwrm_spec_code < 0x10600)
		return 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_QCAPS, -1, -1);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (!rc) {
		u32 flags = le32_to_cpu(resp->flags);

		if (!(bp->flags & BNXT_FLAG_CHIP_P5) &&
		    (flags & VNIC_QCAPS_RESP_FLAGS_RSS_DFLT_CR_CAP))
			bp->flags |= BNXT_FLAG_NEW_RSS_CAP;
		if (flags &
		    VNIC_QCAPS_RESP_FLAGS_ROCE_MIRRORING_CAPABLE_VNIC_CAP)
			bp->flags |= BNXT_FLAG_ROCE_MIRROR_CAP;
		bp->max_tpa_v2 = le16_to_cpu(resp->max_aggs_supported);
		if (bp->max_tpa_v2)
			bp->hw_ring_stats_size =
				sizeof(struct ctx_hw_stats_ext);
	}
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}