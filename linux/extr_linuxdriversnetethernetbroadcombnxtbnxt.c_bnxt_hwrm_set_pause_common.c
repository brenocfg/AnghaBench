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
struct hwrm_port_phy_cfg_input {int /*<<< orphan*/  enables; int /*<<< orphan*/  force_pause; int /*<<< orphan*/  auto_pause; } ;
struct TYPE_2__ {int autoneg; int req_flow_ctrl; } ;
struct bnxt {int hwrm_spec_code; TYPE_1__ link_info; } ;

/* Variables and functions */
 int BNXT_AUTONEG_FLOW_CTRL ; 
 int BNXT_LINK_PAUSE_RX ; 
 int BNXT_LINK_PAUSE_TX ; 
 int /*<<< orphan*/  PORT_PHY_CFG_REQ_AUTO_PAUSE_AUTONEG_PAUSE ; 
 int /*<<< orphan*/  PORT_PHY_CFG_REQ_AUTO_PAUSE_RX ; 
 int /*<<< orphan*/  PORT_PHY_CFG_REQ_AUTO_PAUSE_TX ; 
 int /*<<< orphan*/  PORT_PHY_CFG_REQ_ENABLES_AUTO_PAUSE ; 
 int /*<<< orphan*/  PORT_PHY_CFG_REQ_ENABLES_FORCE_PAUSE ; 
 int /*<<< orphan*/  PORT_PHY_CFG_REQ_FORCE_PAUSE_RX ; 
 int /*<<< orphan*/  PORT_PHY_CFG_REQ_FORCE_PAUSE_TX ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnxt_hwrm_set_pause_common(struct bnxt *bp, struct hwrm_port_phy_cfg_input *req)
{
	if (bp->link_info.autoneg & BNXT_AUTONEG_FLOW_CTRL) {
		if (bp->hwrm_spec_code >= 0x10201)
			req->auto_pause =
				PORT_PHY_CFG_REQ_AUTO_PAUSE_AUTONEG_PAUSE;
		if (bp->link_info.req_flow_ctrl & BNXT_LINK_PAUSE_RX)
			req->auto_pause |= PORT_PHY_CFG_REQ_AUTO_PAUSE_RX;
		if (bp->link_info.req_flow_ctrl & BNXT_LINK_PAUSE_TX)
			req->auto_pause |= PORT_PHY_CFG_REQ_AUTO_PAUSE_TX;
		req->enables |=
			cpu_to_le32(PORT_PHY_CFG_REQ_ENABLES_AUTO_PAUSE);
	} else {
		if (bp->link_info.req_flow_ctrl & BNXT_LINK_PAUSE_RX)
			req->force_pause |= PORT_PHY_CFG_REQ_FORCE_PAUSE_RX;
		if (bp->link_info.req_flow_ctrl & BNXT_LINK_PAUSE_TX)
			req->force_pause |= PORT_PHY_CFG_REQ_FORCE_PAUSE_TX;
		req->enables |=
			cpu_to_le32(PORT_PHY_CFG_REQ_ENABLES_FORCE_PAUSE);
		if (bp->hwrm_spec_code >= 0x10201) {
			req->auto_pause = req->force_pause;
			req->enables |= cpu_to_le32(
				PORT_PHY_CFG_REQ_ENABLES_AUTO_PAUSE);
		}
	}
}