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
struct bnxt {int hwrm_spec_code; int /*<<< orphan*/  fw_cap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_FW_CAP_NEW_RM ; 
 int __bnxt_hwrm_func_qcaps (struct bnxt*) ; 
 int bnxt_alloc_ctx_mem (struct bnxt*) ; 
 int bnxt_hwrm_func_resc_qcaps (struct bnxt*,int) ; 
 int bnxt_hwrm_queue_qportcfg (struct bnxt*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int bnxt_hwrm_func_qcaps(struct bnxt *bp)
{
	int rc;

	rc = __bnxt_hwrm_func_qcaps(bp);
	if (rc)
		return rc;
	rc = bnxt_hwrm_queue_qportcfg(bp);
	if (rc) {
		netdev_err(bp->dev, "hwrm query qportcfg failure rc: %d\n", rc);
		return rc;
	}
	if (bp->hwrm_spec_code >= 0x10803) {
		rc = bnxt_alloc_ctx_mem(bp);
		if (rc)
			return rc;
		rc = bnxt_hwrm_func_resc_qcaps(bp, true);
		if (!rc)
			bp->fw_cap |= BNXT_FW_CAP_NEW_RM;
	}
	return 0;
}