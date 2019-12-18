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
struct bnxt {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  __bnxt_close_nic (struct bnxt*,int,int) ; 
 int /*<<< orphan*/  bnxt_clear_int_mode (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_func_qcaps (struct bnxt*) ; 
 int bnxt_init_int_mode (struct bnxt*) ; 
 int bnxt_open_nic (struct bnxt*,int,int) ; 
 int /*<<< orphan*/  bnxt_ulp_irq_restart (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_ulp_irq_stop (struct bnxt*) ; 
 int /*<<< orphan*/  dev_close (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 

int bnxt_restore_pf_fw_resources(struct bnxt *bp)
{
	int rc;

	ASSERT_RTNL();
	bnxt_hwrm_func_qcaps(bp);

	if (netif_running(bp->dev))
		__bnxt_close_nic(bp, true, false);

	bnxt_ulp_irq_stop(bp);
	bnxt_clear_int_mode(bp);
	rc = bnxt_init_int_mode(bp);
	bnxt_ulp_irq_restart(bp, rc);

	if (netif_running(bp->dev)) {
		if (rc)
			dev_close(bp->dev);
		else
			rc = bnxt_open_nic(bp, true, false);
	}

	return rc;
}