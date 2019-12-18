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
struct bnxt_link_info {int autoneg; int auto_pause_setting; int req_flow_ctrl; int force_pause_setting; scalar_t__ auto_mode; scalar_t__ req_link_speed; scalar_t__ force_link_speed; scalar_t__ req_duplex; scalar_t__ duplex_setting; scalar_t__ advertising; scalar_t__ auto_link_speeds; } ;
struct bnxt {int /*<<< orphan*/  dev; struct bnxt_link_info link_info; } ;

/* Variables and functions */
 int BNXT_AUTONEG_FLOW_CTRL ; 
 int BNXT_AUTONEG_SPEED ; 
 scalar_t__ BNXT_AUTO_MODE (scalar_t__) ; 
 scalar_t__ BNXT_LINK_AUTO_NONE ; 
 int BNXT_LINK_PAUSE_BOTH ; 
 int /*<<< orphan*/  BNXT_SINGLE_PF (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_eee_config_ok (struct bnxt*) ; 
 int bnxt_hwrm_set_link_setting (struct bnxt*,int,int) ; 
 int bnxt_hwrm_set_pause (struct bnxt*) ; 
 int bnxt_update_link (struct bnxt*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_update_phy_setting(struct bnxt *bp)
{
	int rc;
	bool update_link = false;
	bool update_pause = false;
	bool update_eee = false;
	struct bnxt_link_info *link_info = &bp->link_info;

	rc = bnxt_update_link(bp, true);
	if (rc) {
		netdev_err(bp->dev, "failed to update link (rc: %x)\n",
			   rc);
		return rc;
	}
	if (!BNXT_SINGLE_PF(bp))
		return 0;

	if ((link_info->autoneg & BNXT_AUTONEG_FLOW_CTRL) &&
	    (link_info->auto_pause_setting & BNXT_LINK_PAUSE_BOTH) !=
	    link_info->req_flow_ctrl)
		update_pause = true;
	if (!(link_info->autoneg & BNXT_AUTONEG_FLOW_CTRL) &&
	    link_info->force_pause_setting != link_info->req_flow_ctrl)
		update_pause = true;
	if (!(link_info->autoneg & BNXT_AUTONEG_SPEED)) {
		if (BNXT_AUTO_MODE(link_info->auto_mode))
			update_link = true;
		if (link_info->req_link_speed != link_info->force_link_speed)
			update_link = true;
		if (link_info->req_duplex != link_info->duplex_setting)
			update_link = true;
	} else {
		if (link_info->auto_mode == BNXT_LINK_AUTO_NONE)
			update_link = true;
		if (link_info->advertising != link_info->auto_link_speeds)
			update_link = true;
	}

	/* The last close may have shutdown the link, so need to call
	 * PHY_CFG to bring it back up.
	 */
	if (!netif_carrier_ok(bp->dev))
		update_link = true;

	if (!bnxt_eee_config_ok(bp))
		update_eee = true;

	if (update_link)
		rc = bnxt_hwrm_set_link_setting(bp, update_pause, update_eee);
	else if (update_pause)
		rc = bnxt_hwrm_set_pause(bp);
	if (rc) {
		netdev_err(bp->dev, "failed to update phy setting (rc: %x)\n",
			   rc);
		return rc;
	}

	return rc;
}