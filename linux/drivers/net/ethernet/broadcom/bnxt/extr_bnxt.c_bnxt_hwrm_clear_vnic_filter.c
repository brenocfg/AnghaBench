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
typedef  size_t u16 ;
struct hwrm_cfa_l2_filter_free_input {int /*<<< orphan*/  l2_filter_id; int /*<<< orphan*/  member_0; } ;
struct bnxt_vnic_info {size_t uc_filter_count; int /*<<< orphan*/ * fw_l2_filter_id; } ;
struct bnxt {int /*<<< orphan*/  hwrm_cmd_lock; struct bnxt_vnic_info* vnic_info; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_CFA_L2_FILTER_FREE ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_cfa_l2_filter_free_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_cfa_l2_filter_free_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_hwrm_clear_vnic_filter(struct bnxt *bp)
{
	u16 i, j, num_of_vnics = 1; /* only vnic 0 supported */
	int rc = 0;

	/* Any associated ntuple filters will also be cleared by firmware. */
	mutex_lock(&bp->hwrm_cmd_lock);
	for (i = 0; i < num_of_vnics; i++) {
		struct bnxt_vnic_info *vnic = &bp->vnic_info[i];

		for (j = 0; j < vnic->uc_filter_count; j++) {
			struct hwrm_cfa_l2_filter_free_input req = {0};

			bnxt_hwrm_cmd_hdr_init(bp, &req,
					       HWRM_CFA_L2_FILTER_FREE, -1, -1);

			req.l2_filter_id = vnic->fw_l2_filter_id[j];

			rc = _hwrm_send_message(bp, &req, sizeof(req),
						HWRM_CMD_TIMEOUT);
		}
		vnic->uc_filter_count = 0;
	}
	mutex_unlock(&bp->hwrm_cmd_lock);

	return rc;
}