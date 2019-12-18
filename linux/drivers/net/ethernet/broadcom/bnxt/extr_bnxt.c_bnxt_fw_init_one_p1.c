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
struct bnxt {int fw_cap; scalar_t__ hwrm_max_ext_req_len; } ;

/* Variables and functions */
 int BNXT_FW_CAP_KONG_MB_CHNL ; 
 int BNXT_FW_CAP_SHORT_CMD ; 
 scalar_t__ BNXT_HWRM_MAX_REQ_LEN ; 
 int ENODEV ; 
 int bnxt_alloc_hwrm_short_cmd_req (struct bnxt*) ; 
 int bnxt_alloc_kong_hwrm_resources (struct bnxt*) ; 
 int bnxt_hwrm_func_reset (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_fw_set_time (struct bnxt*) ; 
 int bnxt_hwrm_ver_get (struct bnxt*) ; 

__attribute__((used)) static int bnxt_fw_init_one_p1(struct bnxt *bp)
{
	int rc;

	bp->fw_cap = 0;
	rc = bnxt_hwrm_ver_get(bp);
	if (rc)
		return rc;

	if (bp->fw_cap & BNXT_FW_CAP_KONG_MB_CHNL) {
		rc = bnxt_alloc_kong_hwrm_resources(bp);
		if (rc)
			bp->fw_cap &= ~BNXT_FW_CAP_KONG_MB_CHNL;
	}

	if ((bp->fw_cap & BNXT_FW_CAP_SHORT_CMD) ||
	    bp->hwrm_max_ext_req_len > BNXT_HWRM_MAX_REQ_LEN) {
		rc = bnxt_alloc_hwrm_short_cmd_req(bp);
		if (rc)
			return rc;
	}
	rc = bnxt_hwrm_func_reset(bp);
	if (rc)
		return -ENODEV;

	bnxt_hwrm_fw_set_time(bp);
	return 0;
}