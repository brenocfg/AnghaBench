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
struct hwrm_port_phy_cfg_input {int /*<<< orphan*/  enables; int /*<<< orphan*/  lpbk; int /*<<< orphan*/  member_0; } ;
struct bnxt {int dummy; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG ; 
 int /*<<< orphan*/  PORT_PHY_CFG_REQ_ENABLES_LPBK ; 
 int /*<<< orphan*/  PORT_PHY_CFG_REQ_LPBK_EXTERNAL ; 
 int /*<<< orphan*/  PORT_PHY_CFG_REQ_LPBK_LOCAL ; 
 int /*<<< orphan*/  PORT_PHY_CFG_REQ_LPBK_NONE ; 
 int /*<<< orphan*/  bnxt_disable_an_for_lpbk (struct bnxt*,struct hwrm_port_phy_cfg_input*) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_port_phy_cfg_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_port_phy_cfg_input*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_hwrm_phy_loopback(struct bnxt *bp, bool enable, bool ext)
{
	struct hwrm_port_phy_cfg_input req = {0};

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_PHY_CFG, -1, -1);

	if (enable) {
		bnxt_disable_an_for_lpbk(bp, &req);
		if (ext)
			req.lpbk = PORT_PHY_CFG_REQ_LPBK_EXTERNAL;
		else
			req.lpbk = PORT_PHY_CFG_REQ_LPBK_LOCAL;
	} else {
		req.lpbk = PORT_PHY_CFG_REQ_LPBK_NONE;
	}
	req.enables = cpu_to_le32(PORT_PHY_CFG_REQ_ENABLES_LPBK);
	return hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
}