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
struct hwrm_vnic_qcaps_output {int /*<<< orphan*/  flags; } ;
struct hwrm_vnic_qcaps_input {int /*<<< orphan*/  member_0; } ;
struct bnxt {int hwrm_spec_code; int /*<<< orphan*/  hwrm_cmd_lock; int /*<<< orphan*/  flags; struct hwrm_vnic_qcaps_output* hwrm_cmd_resp_addr; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_FLAG_NEW_RSS_CAP ; 
 int /*<<< orphan*/  BNXT_FLAG_ROCE_MIRROR_CAP ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_VNIC_QCAPS ; 
 int VNIC_QCAPS_RESP_FLAGS_ROCE_MIRRORING_CAPABLE_VNIC_CAP ; 
 int VNIC_QCAPS_RESP_FLAGS_RSS_DFLT_CR_CAP ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_vnic_qcaps_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_vnic_qcaps_input*,int /*<<< orphan*/ ,int,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_hwrm_vnic_qcaps(struct bnxt *bp)
{
	struct hwrm_vnic_qcaps_output *resp = bp->hwrm_cmd_resp_addr;
	struct hwrm_vnic_qcaps_input req = {0};
	int rc;

	if (bp->hwrm_spec_code < 0x10600)
		return 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_QCAPS, -1, -1);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (!rc) {
		u32 flags = le32_to_cpu(resp->flags);

		if (flags & VNIC_QCAPS_RESP_FLAGS_RSS_DFLT_CR_CAP)
			bp->flags |= BNXT_FLAG_NEW_RSS_CAP;
		if (flags &
		    VNIC_QCAPS_RESP_FLAGS_ROCE_MIRRORING_CAPABLE_VNIC_CAP)
			bp->flags |= BNXT_FLAG_ROCE_MIRROR_CAP;
	}
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}