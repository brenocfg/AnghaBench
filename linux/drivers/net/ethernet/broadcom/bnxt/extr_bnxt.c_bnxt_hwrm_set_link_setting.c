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
struct hwrm_port_phy_cfg_input {int /*<<< orphan*/  member_0; } ;
struct bnxt {int dummy; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_port_phy_cfg_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bnxt_hwrm_set_eee (struct bnxt*,struct hwrm_port_phy_cfg_input*) ; 
 int /*<<< orphan*/  bnxt_hwrm_set_link_common (struct bnxt*,struct hwrm_port_phy_cfg_input*) ; 
 int /*<<< orphan*/  bnxt_hwrm_set_pause_common (struct bnxt*,struct hwrm_port_phy_cfg_input*) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_port_phy_cfg_input*,int,int /*<<< orphan*/ ) ; 

int bnxt_hwrm_set_link_setting(struct bnxt *bp, bool set_pause, bool set_eee)
{
	struct hwrm_port_phy_cfg_input req = {0};

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_PHY_CFG, -1, -1);
	if (set_pause)
		bnxt_hwrm_set_pause_common(bp, &req);

	bnxt_hwrm_set_link_common(bp, &req);

	if (set_eee)
		bnxt_hwrm_set_eee(bp, &req);
	return hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
}