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
struct net_device {int dummy; } ;
struct bnxt_pf_info {int active_vfs; } ;
struct bnxt {struct bnxt_pf_info pf; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BNXT_PF (struct bnxt*) ; 
 int /*<<< orphan*/  BNXT_STATE_ABORT_ERR ; 
 int /*<<< orphan*/  BNXT_STATE_FW_RESET_DET ; 
 int ENODEV ; 
 int __bnxt_open_nic (struct bnxt*,int,int) ; 
 int /*<<< orphan*/  bnxt_cfg_hw_sriov (struct bnxt*,int*,int) ; 
 int /*<<< orphan*/  bnxt_hwmon_open (struct bnxt*) ; 
 int bnxt_hwrm_if_change (struct bnxt*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_open(struct net_device *dev)
{
	struct bnxt *bp = netdev_priv(dev);
	int rc;

	if (test_bit(BNXT_STATE_ABORT_ERR, &bp->state)) {
		netdev_err(bp->dev, "A previous firmware reset did not complete, aborting\n");
		return -ENODEV;
	}

	rc = bnxt_hwrm_if_change(bp, true);
	if (rc)
		return rc;
	rc = __bnxt_open_nic(bp, true, true);
	if (rc) {
		bnxt_hwrm_if_change(bp, false);
	} else {
		if (test_and_clear_bit(BNXT_STATE_FW_RESET_DET, &bp->state) &&
		    BNXT_PF(bp)) {
			struct bnxt_pf_info *pf = &bp->pf;
			int n = pf->active_vfs;

			if (n)
				bnxt_cfg_hw_sriov(bp, &n, true);
		}
		bnxt_hwmon_open(bp);
	}

	return rc;
}