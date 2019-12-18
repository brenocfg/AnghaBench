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
 int ENODEV ; 
 int /*<<< orphan*/  bnxt_dcb_init (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_ethtool_init (struct bnxt*) ; 
 int bnxt_hwrm_cfa_adv_flow_mgnt_qcaps (struct bnxt*) ; 
 int bnxt_hwrm_error_recovery_qcfg (struct bnxt*) ; 
 int bnxt_hwrm_func_drv_rgtr (struct bnxt*) ; 
 int bnxt_hwrm_func_qcaps (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_func_qcfg (struct bnxt*) ; 
 int bnxt_hwrm_func_rgtr_async_events (struct bnxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_port_led_qcaps (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_vnic_qcaps (struct bnxt*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int bnxt_fw_init_one_p2(struct bnxt *bp)
{
	int rc;

	/* Get the MAX capabilities for this function */
	rc = bnxt_hwrm_func_qcaps(bp);
	if (rc) {
		netdev_err(bp->dev, "hwrm query capability failure rc: %x\n",
			   rc);
		return -ENODEV;
	}

	rc = bnxt_hwrm_cfa_adv_flow_mgnt_qcaps(bp);
	if (rc)
		netdev_warn(bp->dev, "hwrm query adv flow mgnt failure rc: %d\n",
			    rc);

	rc = bnxt_hwrm_error_recovery_qcfg(bp);
	if (rc)
		netdev_warn(bp->dev, "hwrm query error recovery failure rc: %d\n",
			    rc);

	rc = bnxt_hwrm_func_drv_rgtr(bp);
	if (rc)
		return -ENODEV;

	rc = bnxt_hwrm_func_rgtr_async_events(bp, NULL, 0);
	if (rc)
		return -ENODEV;

	bnxt_hwrm_func_qcfg(bp);
	bnxt_hwrm_vnic_qcaps(bp);
	bnxt_hwrm_port_led_qcaps(bp);
	bnxt_ethtool_init(bp);
	bnxt_dcb_init(bp);
	return 0;
}