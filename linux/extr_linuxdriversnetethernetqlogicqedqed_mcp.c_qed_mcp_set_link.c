#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct qed_ptt {int dummy; } ;
struct qed_mcp_mb_params {int eee_cfg; int data_src_size; struct qed_mcp_mb_params* p_data_src; int /*<<< orphan*/  cmd; int /*<<< orphan*/  feature_config_flags; int /*<<< orphan*/  loopback_mode; int /*<<< orphan*/  adv_speed; int /*<<< orphan*/  pause; int /*<<< orphan*/  speed; } ;
struct TYPE_8__ {int adv_caps; int tx_lpi_timer; scalar_t__ tx_lpi_enable; scalar_t__ enable; } ;
struct TYPE_6__ {int /*<<< orphan*/  advertised_speeds; int /*<<< orphan*/  forced_speed; int /*<<< orphan*/  autoneg; } ;
struct TYPE_5__ {scalar_t__ forced_tx; scalar_t__ forced_rx; scalar_t__ autoneg; } ;
struct qed_mcp_link_params {TYPE_4__ eee; int /*<<< orphan*/  loopback_mode; TYPE_2__ speed; TYPE_1__ pause; } ;
struct qed_hwfn {int b_drv_link_init; TYPE_3__* mcp_info; } ;
struct eth_phy_cfg {int eee_cfg; int data_src_size; struct eth_phy_cfg* p_data_src; int /*<<< orphan*/  cmd; int /*<<< orphan*/  feature_config_flags; int /*<<< orphan*/  loopback_mode; int /*<<< orphan*/  adv_speed; int /*<<< orphan*/  pause; int /*<<< orphan*/  speed; } ;
typedef  int /*<<< orphan*/  phy_cfg ;
typedef  int /*<<< orphan*/  mb_params ;
struct TYPE_7__ {int capabilities; struct qed_mcp_link_params link_input; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_INIT_PHY ; 
 int /*<<< orphan*/  DRV_MSG_CODE_LINK_RESET ; 
 int EEE_CFG_ADV_SPEED_10G ; 
 int EEE_CFG_ADV_SPEED_1G ; 
 int EEE_CFG_EEE_ENABLED ; 
 int EEE_CFG_TX_LPI ; 
 int EEE_TX_TIMER_USEC_MASK ; 
 int EEE_TX_TIMER_USEC_OFFSET ; 
 int /*<<< orphan*/  ETH_PAUSE_AUTONEG ; 
 int /*<<< orphan*/  ETH_PAUSE_RX ; 
 int /*<<< orphan*/  ETH_PAUSE_TX ; 
 int FW_MB_PARAM_FEATURE_SUPPORT_EEE ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int QED_EEE_10G_ADV ; 
 int QED_EEE_1G_ADV ; 
 int /*<<< orphan*/  memset (struct qed_mcp_mb_params*,int /*<<< orphan*/ ,int) ; 
 int qed_mcp_cmd_and_union (struct qed_hwfn*,struct qed_ptt*,struct qed_mcp_mb_params*) ; 
 int /*<<< orphan*/  qed_mcp_handle_link_change (struct qed_hwfn*,struct qed_ptt*,int) ; 

int qed_mcp_set_link(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt, bool b_up)
{
	struct qed_mcp_link_params *params = &p_hwfn->mcp_info->link_input;
	struct qed_mcp_mb_params mb_params;
	struct eth_phy_cfg phy_cfg;
	int rc = 0;
	u32 cmd;

	/* Set the shmem configuration according to params */
	memset(&phy_cfg, 0, sizeof(phy_cfg));
	cmd = b_up ? DRV_MSG_CODE_INIT_PHY : DRV_MSG_CODE_LINK_RESET;
	if (!params->speed.autoneg)
		phy_cfg.speed = params->speed.forced_speed;
	phy_cfg.pause |= (params->pause.autoneg) ? ETH_PAUSE_AUTONEG : 0;
	phy_cfg.pause |= (params->pause.forced_rx) ? ETH_PAUSE_RX : 0;
	phy_cfg.pause |= (params->pause.forced_tx) ? ETH_PAUSE_TX : 0;
	phy_cfg.adv_speed = params->speed.advertised_speeds;
	phy_cfg.loopback_mode = params->loopback_mode;

	/* There are MFWs that share this capability regardless of whether
	 * this is feasible or not. And given that at the very least adv_caps
	 * would be set internally by qed, we want to make sure LFA would
	 * still work.
	 */
	if ((p_hwfn->mcp_info->capabilities &
	     FW_MB_PARAM_FEATURE_SUPPORT_EEE) && params->eee.enable) {
		phy_cfg.eee_cfg |= EEE_CFG_EEE_ENABLED;
		if (params->eee.tx_lpi_enable)
			phy_cfg.eee_cfg |= EEE_CFG_TX_LPI;
		if (params->eee.adv_caps & QED_EEE_1G_ADV)
			phy_cfg.eee_cfg |= EEE_CFG_ADV_SPEED_1G;
		if (params->eee.adv_caps & QED_EEE_10G_ADV)
			phy_cfg.eee_cfg |= EEE_CFG_ADV_SPEED_10G;
		phy_cfg.eee_cfg |= (params->eee.tx_lpi_timer <<
				    EEE_TX_TIMER_USEC_OFFSET) &
				   EEE_TX_TIMER_USEC_MASK;
	}

	p_hwfn->b_drv_link_init = b_up;

	if (b_up) {
		DP_VERBOSE(p_hwfn, NETIF_MSG_LINK,
			   "Configuring Link: Speed 0x%08x, Pause 0x%08x, adv_speed 0x%08x, loopback 0x%08x, features 0x%08x\n",
			   phy_cfg.speed,
			   phy_cfg.pause,
			   phy_cfg.adv_speed,
			   phy_cfg.loopback_mode,
			   phy_cfg.feature_config_flags);
	} else {
		DP_VERBOSE(p_hwfn, NETIF_MSG_LINK,
			   "Resetting link\n");
	}

	memset(&mb_params, 0, sizeof(mb_params));
	mb_params.cmd = cmd;
	mb_params.p_data_src = &phy_cfg;
	mb_params.data_src_size = sizeof(phy_cfg);
	rc = qed_mcp_cmd_and_union(p_hwfn, p_ptt, &mb_params);

	/* if mcp fails to respond we must abort */
	if (rc) {
		DP_ERR(p_hwfn, "MCP response failure, aborting\n");
		return rc;
	}

	/* Mimic link-change attention, done for several reasons:
	 *  - On reset, there's no guarantee MFW would trigger
	 *    an attention.
	 *  - On initialization, older MFWs might not indicate link change
	 *    during LFA, so we'll never get an UP indication.
	 */
	qed_mcp_handle_link_change(p_hwfn, p_ptt, !b_up);

	return 0;
}