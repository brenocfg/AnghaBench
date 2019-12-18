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
struct TYPE_2__ {int registered_vfs; } ;
struct bnxt {scalar_t__ sriov_cfg; TYPE_1__ pf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_PF (struct bnxt*) ; 
 int bnxt_hwrm_func_qcfg (struct bnxt*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int bnxt_get_registered_vfs(struct bnxt *bp)
{
#ifdef CONFIG_BNXT_SRIOV
	int rc;

	if (!BNXT_PF(bp))
		return 0;

	rc = bnxt_hwrm_func_qcfg(bp);
	if (rc) {
		netdev_err(bp->dev, "func_qcfg cmd failed, rc = %d\n", rc);
		return rc;
	}
	if (bp->pf.registered_vfs)
		return bp->pf.registered_vfs;
	if (bp->sriov_cfg)
		return 1;
#endif
	return 0;
}