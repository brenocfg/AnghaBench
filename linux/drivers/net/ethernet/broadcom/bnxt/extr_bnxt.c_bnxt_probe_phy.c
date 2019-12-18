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
struct bnxt_link_info {int autoneg; int auto_pause_setting; int req_flow_ctrl; int force_pause_setting; int /*<<< orphan*/  duplex_setting; int /*<<< orphan*/  req_duplex; int /*<<< orphan*/  force_link_speed; int /*<<< orphan*/  req_link_speed; scalar_t__ auto_link_speeds; scalar_t__ advertising; int /*<<< orphan*/  auto_mode; scalar_t__ support_speeds; scalar_t__ support_auto_speeds; } ;
struct bnxt {int hwrm_spec_code; int /*<<< orphan*/  dev; struct bnxt_link_info link_info; } ;

/* Variables and functions */
 int BNXT_AUTONEG_FLOW_CTRL ; 
 int BNXT_AUTONEG_SPEED ; 
 scalar_t__ BNXT_AUTO_MODE (int /*<<< orphan*/ ) ; 
 int BNXT_LINK_PAUSE_BOTH ; 
 int PORT_PHY_CFG_REQ_AUTO_PAUSE_AUTONEG_PAUSE ; 
 int bnxt_hwrm_phy_qcaps (struct bnxt*) ; 
 int bnxt_update_link (struct bnxt*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int bnxt_probe_phy(struct bnxt *bp, bool fw_dflt)
{
	int rc = 0;
	struct bnxt_link_info *link_info = &bp->link_info;

	rc = bnxt_hwrm_phy_qcaps(bp);
	if (rc) {
		netdev_err(bp->dev, "Probe phy can't get phy capabilities (rc: %x)\n",
			   rc);
		return rc;
	}
	rc = bnxt_update_link(bp, false);
	if (rc) {
		netdev_err(bp->dev, "Probe phy can't update link (rc: %x)\n",
			   rc);
		return rc;
	}

	/* Older firmware does not have supported_auto_speeds, so assume
	 * that all supported speeds can be autonegotiated.
	 */
	if (link_info->auto_link_speeds && !link_info->support_auto_speeds)
		link_info->support_auto_speeds = link_info->support_speeds;

	if (!fw_dflt)
		return 0;

	/*initialize the ethool setting copy with NVM settings */
	if (BNXT_AUTO_MODE(link_info->auto_mode)) {
		link_info->autoneg = BNXT_AUTONEG_SPEED;
		if (bp->hwrm_spec_code >= 0x10201) {
			if (link_info->auto_pause_setting &
			    PORT_PHY_CFG_REQ_AUTO_PAUSE_AUTONEG_PAUSE)
				link_info->autoneg |= BNXT_AUTONEG_FLOW_CTRL;
		} else {
			link_info->autoneg |= BNXT_AUTONEG_FLOW_CTRL;
		}
		link_info->advertising = link_info->auto_link_speeds;
	} else {
		link_info->req_link_speed = link_info->force_link_speed;
		link_info->req_duplex = link_info->duplex_setting;
	}
	if (link_info->autoneg & BNXT_AUTONEG_FLOW_CTRL)
		link_info->req_flow_ctrl =
			link_info->auto_pause_setting & BNXT_LINK_PAUSE_BOTH;
	else
		link_info->req_flow_ctrl = link_info->force_pause_setting;
	return 0;
}