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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct hwrm_port_phy_cfg_input {int /*<<< orphan*/  flags; void* force_link_speed; int /*<<< orphan*/  enables; void* auto_link_speed_mask; int /*<<< orphan*/  auto_mode; } ;
struct TYPE_2__ {int autoneg; int /*<<< orphan*/  advertising; int /*<<< orphan*/  req_link_speed; } ;
struct bnxt {TYPE_1__ link_info; } ;

/* Variables and functions */
 int BNXT_AUTONEG_SPEED ; 
 int /*<<< orphan*/  PORT_PHY_CFG_REQ_AUTO_MODE_SPEED_MASK ; 
 int /*<<< orphan*/  PORT_PHY_CFG_REQ_ENABLES_AUTO_LINK_SPEED_MASK ; 
 int /*<<< orphan*/  PORT_PHY_CFG_REQ_ENABLES_AUTO_MODE ; 
 int /*<<< orphan*/  PORT_PHY_CFG_REQ_FLAGS_FORCE ; 
 int /*<<< orphan*/  PORT_PHY_CFG_REQ_FLAGS_RESET_PHY ; 
 int /*<<< orphan*/  PORT_PHY_CFG_REQ_FLAGS_RESTART_AUTONEG ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_hwrm_set_link_common(struct bnxt *bp,
				      struct hwrm_port_phy_cfg_input *req)
{
	u8 autoneg = bp->link_info.autoneg;
	u16 fw_link_speed = bp->link_info.req_link_speed;
	u16 advertising = bp->link_info.advertising;

	if (autoneg & BNXT_AUTONEG_SPEED) {
		req->auto_mode |=
			PORT_PHY_CFG_REQ_AUTO_MODE_SPEED_MASK;

		req->enables |= cpu_to_le32(
			PORT_PHY_CFG_REQ_ENABLES_AUTO_LINK_SPEED_MASK);
		req->auto_link_speed_mask = cpu_to_le16(advertising);

		req->enables |= cpu_to_le32(PORT_PHY_CFG_REQ_ENABLES_AUTO_MODE);
		req->flags |=
			cpu_to_le32(PORT_PHY_CFG_REQ_FLAGS_RESTART_AUTONEG);
	} else {
		req->force_link_speed = cpu_to_le16(fw_link_speed);
		req->flags |= cpu_to_le32(PORT_PHY_CFG_REQ_FLAGS_FORCE);
	}

	/* tell chimp that the setting takes effect immediately */
	req->flags |= cpu_to_le32(PORT_PHY_CFG_REQ_FLAGS_RESET_PHY);
}