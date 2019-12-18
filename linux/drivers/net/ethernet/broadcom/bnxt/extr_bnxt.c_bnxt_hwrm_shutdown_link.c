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
struct hwrm_port_phy_cfg_input {int /*<<< orphan*/  flags; int /*<<< orphan*/  member_0; } ;
struct bnxt {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_SINGLE_PF (struct bnxt*) ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG ; 
 int /*<<< orphan*/  PORT_PHY_CFG_REQ_FLAGS_FORCE_LINK_DWN ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_port_phy_cfg_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_port_phy_cfg_input*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_num_vf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_hwrm_shutdown_link(struct bnxt *bp)
{
	struct hwrm_port_phy_cfg_input req = {0};

	if (!BNXT_SINGLE_PF(bp))
		return 0;

	if (pci_num_vf(bp->pdev))
		return 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_PHY_CFG, -1, -1);
	req.flags = cpu_to_le32(PORT_PHY_CFG_REQ_FLAGS_FORCE_LINK_DWN);
	return hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
}