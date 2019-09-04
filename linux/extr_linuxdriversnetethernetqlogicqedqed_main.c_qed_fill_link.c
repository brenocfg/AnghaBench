#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct qed_mcp_link_state {int partner_adv_speed; scalar_t__ partner_adv_pause; int /*<<< orphan*/  eee_lp_adv_caps; scalar_t__ eee_adv_caps; int /*<<< orphan*/  eee_active; scalar_t__ an_complete; int /*<<< orphan*/  speed; scalar_t__ link_up; } ;
struct TYPE_8__ {int /*<<< orphan*/  tx_lpi_timer; int /*<<< orphan*/  tx_lpi_enable; int /*<<< orphan*/  enable; scalar_t__ adv_caps; } ;
struct TYPE_11__ {scalar_t__ forced_tx; scalar_t__ forced_rx; scalar_t__ autoneg; } ;
struct TYPE_10__ {int advertised_speeds; scalar_t__ autoneg; } ;
struct qed_mcp_link_params {TYPE_2__ eee; TYPE_5__ pause; TYPE_4__ speed; } ;
struct qed_mcp_link_capabilities {int speed_capabilities; scalar_t__ default_eee; int /*<<< orphan*/  eee_speed_caps; scalar_t__ default_speed_autoneg; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx_lpi_timer; int /*<<< orphan*/  tx_lpi_enable; int /*<<< orphan*/  enable; int /*<<< orphan*/  lp_adv_caps; scalar_t__ adv_caps; } ;
struct qed_link_output {int link_up; int supported_caps; int advertised_caps; int lp_caps; int eee_supported; TYPE_1__ eee; int /*<<< orphan*/  sup_caps; int /*<<< orphan*/  eee_active; int /*<<< orphan*/  pause_config; scalar_t__ autoneg; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct qed_hwfn {TYPE_6__* cdev; } ;
struct TYPE_12__ {TYPE_3__* pdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G ; 
 int NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G ; 
 int NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G ; 
 int NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G ; 
 int NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_50G ; 
 int NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_BB_100G ; 
 scalar_t__ QED_LINK_PARTNER_ASYMMETRIC_PAUSE ; 
 scalar_t__ QED_LINK_PARTNER_BOTH_PAUSE ; 
 int QED_LINK_PARTNER_SPEED_100G ; 
 int QED_LINK_PARTNER_SPEED_10G ; 
 int QED_LINK_PARTNER_SPEED_1G_FD ; 
 int QED_LINK_PARTNER_SPEED_1G_HD ; 
 int QED_LINK_PARTNER_SPEED_25G ; 
 int QED_LINK_PARTNER_SPEED_40G ; 
 int QED_LINK_PARTNER_SPEED_50G ; 
 int /*<<< orphan*/  QED_LINK_PAUSE_AUTONEG_ENABLE ; 
 int /*<<< orphan*/  QED_LINK_PAUSE_RX_ENABLE ; 
 int /*<<< orphan*/  QED_LINK_PAUSE_TX_ENABLE ; 
 int QED_LM_100000baseKR4_Full_BIT ; 
 int QED_LM_10000baseKR_Full_BIT ; 
 int QED_LM_1000baseT_Full_BIT ; 
 int QED_LM_1000baseT_Half_BIT ; 
 int QED_LM_25000baseKR_Full_BIT ; 
 int QED_LM_40000baseLR4_Full_BIT ; 
 int QED_LM_50000baseKR2_Full_BIT ; 
 int QED_LM_Asym_Pause_BIT ; 
 int QED_LM_Autoneg_BIT ; 
 int QED_LM_FIBRE_BIT ; 
 int QED_LM_Pause_BIT ; 
 scalar_t__ QED_MCP_EEE_UNSUPPORTED ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (struct qed_link_output*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qed_get_link_data (struct qed_hwfn*,struct qed_mcp_link_params*,struct qed_mcp_link_state*,struct qed_mcp_link_capabilities*) ; 
 int /*<<< orphan*/  qed_get_port_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_mcp_get_media_type (TYPE_6__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qed_fill_link(struct qed_hwfn *hwfn,
			  struct qed_link_output *if_link)
{
	struct qed_mcp_link_params params;
	struct qed_mcp_link_state link;
	struct qed_mcp_link_capabilities link_caps;
	u32 media_type;

	memset(if_link, 0, sizeof(*if_link));

	/* Prepare source inputs */
	if (qed_get_link_data(hwfn, &params, &link, &link_caps)) {
		dev_warn(&hwfn->cdev->pdev->dev, "no link data available\n");
		return;
	}

	/* Set the link parameters to pass to protocol driver */
	if (link.link_up)
		if_link->link_up = true;

	/* TODO - at the moment assume supported and advertised speed equal */
	if_link->supported_caps = QED_LM_FIBRE_BIT;
	if (link_caps.default_speed_autoneg)
		if_link->supported_caps |= QED_LM_Autoneg_BIT;
	if (params.pause.autoneg ||
	    (params.pause.forced_rx && params.pause.forced_tx))
		if_link->supported_caps |= QED_LM_Asym_Pause_BIT;
	if (params.pause.autoneg || params.pause.forced_rx ||
	    params.pause.forced_tx)
		if_link->supported_caps |= QED_LM_Pause_BIT;

	if_link->advertised_caps = if_link->supported_caps;
	if (params.speed.autoneg)
		if_link->advertised_caps |= QED_LM_Autoneg_BIT;
	else
		if_link->advertised_caps &= ~QED_LM_Autoneg_BIT;
	if (params.speed.advertised_speeds &
	    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G)
		if_link->advertised_caps |= QED_LM_1000baseT_Half_BIT |
		    QED_LM_1000baseT_Full_BIT;
	if (params.speed.advertised_speeds &
	    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G)
		if_link->advertised_caps |= QED_LM_10000baseKR_Full_BIT;
	if (params.speed.advertised_speeds &
	    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G)
		if_link->advertised_caps |= QED_LM_25000baseKR_Full_BIT;
	if (params.speed.advertised_speeds &
	    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G)
		if_link->advertised_caps |= QED_LM_40000baseLR4_Full_BIT;
	if (params.speed.advertised_speeds &
	    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_50G)
		if_link->advertised_caps |= QED_LM_50000baseKR2_Full_BIT;
	if (params.speed.advertised_speeds &
	    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_BB_100G)
		if_link->advertised_caps |= QED_LM_100000baseKR4_Full_BIT;

	if (link_caps.speed_capabilities &
	    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G)
		if_link->supported_caps |= QED_LM_1000baseT_Half_BIT |
		    QED_LM_1000baseT_Full_BIT;
	if (link_caps.speed_capabilities &
	    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G)
		if_link->supported_caps |= QED_LM_10000baseKR_Full_BIT;
	if (link_caps.speed_capabilities &
	    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G)
		if_link->supported_caps |= QED_LM_25000baseKR_Full_BIT;
	if (link_caps.speed_capabilities &
	    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G)
		if_link->supported_caps |= QED_LM_40000baseLR4_Full_BIT;
	if (link_caps.speed_capabilities &
	    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_50G)
		if_link->supported_caps |= QED_LM_50000baseKR2_Full_BIT;
	if (link_caps.speed_capabilities &
	    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_BB_100G)
		if_link->supported_caps |= QED_LM_100000baseKR4_Full_BIT;

	if (link.link_up)
		if_link->speed = link.speed;

	/* TODO - fill duplex properly */
	if_link->duplex = DUPLEX_FULL;
	qed_mcp_get_media_type(hwfn->cdev, &media_type);
	if_link->port = qed_get_port_type(media_type);

	if_link->autoneg = params.speed.autoneg;

	if (params.pause.autoneg)
		if_link->pause_config |= QED_LINK_PAUSE_AUTONEG_ENABLE;
	if (params.pause.forced_rx)
		if_link->pause_config |= QED_LINK_PAUSE_RX_ENABLE;
	if (params.pause.forced_tx)
		if_link->pause_config |= QED_LINK_PAUSE_TX_ENABLE;

	/* Link partner capabilities */
	if (link.partner_adv_speed & QED_LINK_PARTNER_SPEED_1G_HD)
		if_link->lp_caps |= QED_LM_1000baseT_Half_BIT;
	if (link.partner_adv_speed & QED_LINK_PARTNER_SPEED_1G_FD)
		if_link->lp_caps |= QED_LM_1000baseT_Full_BIT;
	if (link.partner_adv_speed & QED_LINK_PARTNER_SPEED_10G)
		if_link->lp_caps |= QED_LM_10000baseKR_Full_BIT;
	if (link.partner_adv_speed & QED_LINK_PARTNER_SPEED_25G)
		if_link->lp_caps |= QED_LM_25000baseKR_Full_BIT;
	if (link.partner_adv_speed & QED_LINK_PARTNER_SPEED_40G)
		if_link->lp_caps |= QED_LM_40000baseLR4_Full_BIT;
	if (link.partner_adv_speed & QED_LINK_PARTNER_SPEED_50G)
		if_link->lp_caps |= QED_LM_50000baseKR2_Full_BIT;
	if (link.partner_adv_speed & QED_LINK_PARTNER_SPEED_100G)
		if_link->lp_caps |= QED_LM_100000baseKR4_Full_BIT;

	if (link.an_complete)
		if_link->lp_caps |= QED_LM_Autoneg_BIT;

	if (link.partner_adv_pause)
		if_link->lp_caps |= QED_LM_Pause_BIT;
	if (link.partner_adv_pause == QED_LINK_PARTNER_ASYMMETRIC_PAUSE ||
	    link.partner_adv_pause == QED_LINK_PARTNER_BOTH_PAUSE)
		if_link->lp_caps |= QED_LM_Asym_Pause_BIT;

	if (link_caps.default_eee == QED_MCP_EEE_UNSUPPORTED) {
		if_link->eee_supported = false;
	} else {
		if_link->eee_supported = true;
		if_link->eee_active = link.eee_active;
		if_link->sup_caps = link_caps.eee_speed_caps;
		/* MFW clears adv_caps on eee disable; use configured value */
		if_link->eee.adv_caps = link.eee_adv_caps ? link.eee_adv_caps :
					params.eee.adv_caps;
		if_link->eee.lp_adv_caps = link.eee_lp_adv_caps;
		if_link->eee.enable = params.eee.enable;
		if_link->eee.tx_lpi_enable = params.eee.tx_lpi_enable;
		if_link->eee.tx_lpi_timer = params.eee.tx_lpi_timer;
	}
}