#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct TYPE_4__ {int autoneg; int forced_rx; int forced_tx; } ;
struct TYPE_3__ {int /*<<< orphan*/  forced_speed; int /*<<< orphan*/  advertised_speeds; int /*<<< orphan*/  autoneg; } ;
struct qed_mcp_link_params {int /*<<< orphan*/  eee; int /*<<< orphan*/  loopback_mode; TYPE_2__ pause; TYPE_1__ speed; } ;
struct qed_link_params {int override_flags; int adv_speeds; int pause_config; int loopback_mode; int /*<<< orphan*/  link_up; int /*<<< orphan*/  eee; int /*<<< orphan*/  forced_speed; int /*<<< orphan*/  autoneg; } ;
struct qed_hwfn {int dummy; } ;
struct qed_dev {struct qed_hwfn* hwfns; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  ETH_LOOPBACK_EXT ; 
 int /*<<< orphan*/  ETH_LOOPBACK_EXT_PHY ; 
 int /*<<< orphan*/  ETH_LOOPBACK_INT_PHY ; 
 int /*<<< orphan*/  ETH_LOOPBACK_MAC ; 
 int /*<<< orphan*/  ETH_LOOPBACK_NONE ; 
 scalar_t__ IS_VF (struct qed_dev*) ; 
 int /*<<< orphan*/  NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G ; 
 int /*<<< orphan*/  NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G ; 
 int /*<<< orphan*/  NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_20G ; 
 int /*<<< orphan*/  NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G ; 
 int /*<<< orphan*/  NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G ; 
 int /*<<< orphan*/  NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_50G ; 
 int /*<<< orphan*/  NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_BB_100G ; 
 int /*<<< orphan*/  QED_IOV_WQ_VF_FORCE_LINK_QUERY_FLAG ; 
#define  QED_LINK_LOOPBACK_EXT 131 
#define  QED_LINK_LOOPBACK_EXT_PHY 130 
#define  QED_LINK_LOOPBACK_INT_PHY 129 
#define  QED_LINK_LOOPBACK_MAC 128 
 int QED_LINK_OVERRIDE_EEE_CONFIG ; 
 int QED_LINK_OVERRIDE_LOOPBACK_MODE ; 
 int QED_LINK_OVERRIDE_PAUSE_CONFIG ; 
 int QED_LINK_OVERRIDE_SPEED_ADV_SPEEDS ; 
 int QED_LINK_OVERRIDE_SPEED_AUTONEG ; 
 int QED_LINK_OVERRIDE_SPEED_FORCED_SPEED ; 
 int QED_LINK_PAUSE_AUTONEG_ENABLE ; 
 int QED_LINK_PAUSE_RX_ENABLE ; 
 int QED_LINK_PAUSE_TX_ENABLE ; 
 int QED_LM_100000baseCR4_Full_BIT ; 
 int QED_LM_100000baseKR4_Full_BIT ; 
 int QED_LM_100000baseLR4_ER4_Full_BIT ; 
 int QED_LM_100000baseSR4_Full_BIT ; 
 int QED_LM_10000baseCR_Full_BIT ; 
 int QED_LM_10000baseKR_Full_BIT ; 
 int QED_LM_10000baseKX4_Full_BIT ; 
 int QED_LM_10000baseLRM_Full_BIT ; 
 int QED_LM_10000baseLR_Full_BIT ; 
 int QED_LM_10000baseR_FEC_BIT ; 
 int QED_LM_10000baseSR_Full_BIT ; 
 int QED_LM_10000baseT_Full_BIT ; 
 int QED_LM_1000baseKX_Full_BIT ; 
 int QED_LM_1000baseT_Full_BIT ; 
 int QED_LM_1000baseX_Full_BIT ; 
 int QED_LM_20000baseKR2_Full_BIT ; 
 int QED_LM_25000baseCR_Full_BIT ; 
 int QED_LM_25000baseKR_Full_BIT ; 
 int QED_LM_25000baseSR_Full_BIT ; 
 int QED_LM_40000baseCR4_Full_BIT ; 
 int QED_LM_40000baseKR4_Full_BIT ; 
 int QED_LM_40000baseLR4_Full_BIT ; 
 int QED_LM_40000baseSR4_Full_BIT ; 
 int QED_LM_50000baseCR2_Full_BIT ; 
 int QED_LM_50000baseKR2_Full_BIT ; 
 int QED_LM_50000baseSR2_Full_BIT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct qed_mcp_link_params* qed_mcp_get_link_params (struct qed_hwfn*) ; 
 int qed_mcp_set_link (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 
 struct qed_ptt* qed_ptt_acquire (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_ptt_release (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_schedule_iov (struct qed_hwfn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_set_link(struct qed_dev *cdev, struct qed_link_params *params)
{
	struct qed_hwfn *hwfn;
	struct qed_mcp_link_params *link_params;
	struct qed_ptt *ptt;
	u32 sup_caps;
	int rc;

	if (!cdev)
		return -ENODEV;

	/* The link should be set only once per PF */
	hwfn = &cdev->hwfns[0];

	/* When VF wants to set link, force it to read the bulletin instead.
	 * This mimics the PF behavior, where a noitification [both immediate
	 * and possible later] would be generated when changing properties.
	 */
	if (IS_VF(cdev)) {
		qed_schedule_iov(hwfn, QED_IOV_WQ_VF_FORCE_LINK_QUERY_FLAG);
		return 0;
	}

	ptt = qed_ptt_acquire(hwfn);
	if (!ptt)
		return -EBUSY;

	link_params = qed_mcp_get_link_params(hwfn);
	if (params->override_flags & QED_LINK_OVERRIDE_SPEED_AUTONEG)
		link_params->speed.autoneg = params->autoneg;
	if (params->override_flags & QED_LINK_OVERRIDE_SPEED_ADV_SPEEDS) {
		link_params->speed.advertised_speeds = 0;
		sup_caps = QED_LM_1000baseT_Full_BIT |
			   QED_LM_1000baseKX_Full_BIT |
			   QED_LM_1000baseX_Full_BIT;
		if (params->adv_speeds & sup_caps)
			link_params->speed.advertised_speeds |=
			    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G;
		sup_caps = QED_LM_10000baseT_Full_BIT |
			   QED_LM_10000baseKR_Full_BIT |
			   QED_LM_10000baseKX4_Full_BIT |
			   QED_LM_10000baseR_FEC_BIT |
			   QED_LM_10000baseCR_Full_BIT |
			   QED_LM_10000baseSR_Full_BIT |
			   QED_LM_10000baseLR_Full_BIT |
			   QED_LM_10000baseLRM_Full_BIT;
		if (params->adv_speeds & sup_caps)
			link_params->speed.advertised_speeds |=
			    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G;
		if (params->adv_speeds & QED_LM_20000baseKR2_Full_BIT)
			link_params->speed.advertised_speeds |=
				NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_20G;
		sup_caps = QED_LM_25000baseKR_Full_BIT |
			   QED_LM_25000baseCR_Full_BIT |
			   QED_LM_25000baseSR_Full_BIT;
		if (params->adv_speeds & sup_caps)
			link_params->speed.advertised_speeds |=
			    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G;
		sup_caps = QED_LM_40000baseLR4_Full_BIT |
			   QED_LM_40000baseKR4_Full_BIT |
			   QED_LM_40000baseCR4_Full_BIT |
			   QED_LM_40000baseSR4_Full_BIT;
		if (params->adv_speeds & sup_caps)
			link_params->speed.advertised_speeds |=
				NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G;
		sup_caps = QED_LM_50000baseKR2_Full_BIT |
			   QED_LM_50000baseCR2_Full_BIT |
			   QED_LM_50000baseSR2_Full_BIT;
		if (params->adv_speeds & sup_caps)
			link_params->speed.advertised_speeds |=
			    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_50G;
		sup_caps = QED_LM_100000baseKR4_Full_BIT |
			   QED_LM_100000baseSR4_Full_BIT |
			   QED_LM_100000baseCR4_Full_BIT |
			   QED_LM_100000baseLR4_ER4_Full_BIT;
		if (params->adv_speeds & sup_caps)
			link_params->speed.advertised_speeds |=
			    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_BB_100G;
	}
	if (params->override_flags & QED_LINK_OVERRIDE_SPEED_FORCED_SPEED)
		link_params->speed.forced_speed = params->forced_speed;
	if (params->override_flags & QED_LINK_OVERRIDE_PAUSE_CONFIG) {
		if (params->pause_config & QED_LINK_PAUSE_AUTONEG_ENABLE)
			link_params->pause.autoneg = true;
		else
			link_params->pause.autoneg = false;
		if (params->pause_config & QED_LINK_PAUSE_RX_ENABLE)
			link_params->pause.forced_rx = true;
		else
			link_params->pause.forced_rx = false;
		if (params->pause_config & QED_LINK_PAUSE_TX_ENABLE)
			link_params->pause.forced_tx = true;
		else
			link_params->pause.forced_tx = false;
	}
	if (params->override_flags & QED_LINK_OVERRIDE_LOOPBACK_MODE) {
		switch (params->loopback_mode) {
		case QED_LINK_LOOPBACK_INT_PHY:
			link_params->loopback_mode = ETH_LOOPBACK_INT_PHY;
			break;
		case QED_LINK_LOOPBACK_EXT_PHY:
			link_params->loopback_mode = ETH_LOOPBACK_EXT_PHY;
			break;
		case QED_LINK_LOOPBACK_EXT:
			link_params->loopback_mode = ETH_LOOPBACK_EXT;
			break;
		case QED_LINK_LOOPBACK_MAC:
			link_params->loopback_mode = ETH_LOOPBACK_MAC;
			break;
		default:
			link_params->loopback_mode = ETH_LOOPBACK_NONE;
			break;
		}
	}

	if (params->override_flags & QED_LINK_OVERRIDE_EEE_CONFIG)
		memcpy(&link_params->eee, &params->eee,
		       sizeof(link_params->eee));

	rc = qed_mcp_set_link(hwfn, ptt, params->link_up);

	qed_ptt_release(hwfn, ptt);

	return rc;
}