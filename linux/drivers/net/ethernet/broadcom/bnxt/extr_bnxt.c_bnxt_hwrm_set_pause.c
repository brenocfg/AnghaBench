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
struct hwrm_port_phy_cfg_input {int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int autoneg; int force_link_chng; scalar_t__ auto_pause_setting; int /*<<< orphan*/  req_flow_ctrl; int /*<<< orphan*/  force_pause_setting; int /*<<< orphan*/  pause; } ;
struct bnxt {int /*<<< orphan*/  hwrm_cmd_lock; TYPE_1__ link_info; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int BNXT_AUTONEG_FLOW_CTRL ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_port_phy_cfg_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_port_phy_cfg_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bnxt_hwrm_set_link_common (struct bnxt*,struct hwrm_port_phy_cfg_input*) ; 
 int /*<<< orphan*/  bnxt_hwrm_set_pause_common (struct bnxt*,struct hwrm_port_phy_cfg_input*) ; 
 int /*<<< orphan*/  bnxt_report_link (struct bnxt*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int bnxt_hwrm_set_pause(struct bnxt *bp)
{
	struct hwrm_port_phy_cfg_input req = {0};
	int rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_PHY_CFG, -1, -1);
	bnxt_hwrm_set_pause_common(bp, &req);

	if ((bp->link_info.autoneg & BNXT_AUTONEG_FLOW_CTRL) ||
	    bp->link_info.force_link_chng)
		bnxt_hwrm_set_link_common(bp, &req);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (!rc && !(bp->link_info.autoneg & BNXT_AUTONEG_FLOW_CTRL)) {
		/* since changing of pause setting doesn't trigger any link
		 * change event, the driver needs to update the current pause
		 * result upon successfully return of the phy_cfg command
		 */
		bp->link_info.pause =
		bp->link_info.force_pause_setting = bp->link_info.req_flow_ctrl;
		bp->link_info.auto_pause_setting = 0;
		if (!bp->link_info.force_link_chng)
			bnxt_report_link(bp);
	}
	bp->link_info.force_link_chng = false;
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}