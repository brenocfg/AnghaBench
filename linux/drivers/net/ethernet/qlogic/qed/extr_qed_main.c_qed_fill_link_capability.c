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
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int ETH_TRANSCEIVER_STATE_UNPLUGGED ; 
 int ETH_TRANSCEIVER_TYPE_1000BASET ; 
 int ETH_TRANSCEIVER_TYPE_100G_SR4 ; 
 int ETH_TRANSCEIVER_TYPE_10G_BASET ; 
 int ETH_TRANSCEIVER_TYPE_10G_ER ; 
 int ETH_TRANSCEIVER_TYPE_10G_LR ; 
 int ETH_TRANSCEIVER_TYPE_10G_LRM ; 
 int ETH_TRANSCEIVER_TYPE_10G_SR ; 
 int ETH_TRANSCEIVER_TYPE_1G_LX ; 
 int ETH_TRANSCEIVER_TYPE_1G_SX ; 
 int ETH_TRANSCEIVER_TYPE_25G_SR ; 
 int ETH_TRANSCEIVER_TYPE_40G_LR4 ; 
 int ETH_TRANSCEIVER_TYPE_40G_SR4 ; 
#define  MEDIA_BASE_T 136 
#define  MEDIA_DA_TWINAX 135 
#define  MEDIA_KR 134 
#define  MEDIA_MODULE_FIBER 133 
#define  MEDIA_NOT_PRESENT 132 
#define  MEDIA_SFPP_10G_FIBER 131 
#define  MEDIA_SFP_1G_FIBER 130 
#define  MEDIA_UNSPECIFIED 129 
#define  MEDIA_XFP_FIBER 128 
 int /*<<< orphan*/  NETIF_MSG_DRV ; 
 int NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G ; 
 int NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G ; 
 int NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_20G ; 
 int NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G ; 
 int NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G ; 
 int NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_50G ; 
 int NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_BB_100G ; 
 int NVM_CFG1_PORT_PORT_TYPE_EXT_PHY ; 
 int NVM_CFG1_PORT_PORT_TYPE_MODULE ; 
 int NVM_CFG1_PORT_PORT_TYPE_UNDEFINED ; 
 int QED_LM_100000baseCR4_Full_BIT ; 
 int QED_LM_100000baseKR4_Full_BIT ; 
 int QED_LM_100000baseSR4_Full_BIT ; 
 int QED_LM_10000baseCR_Full_BIT ; 
 int QED_LM_10000baseKR_Full_BIT ; 
 int QED_LM_10000baseLRM_Full_BIT ; 
 int QED_LM_10000baseLR_Full_BIT ; 
 int QED_LM_10000baseR_FEC_BIT ; 
 int QED_LM_10000baseSR_Full_BIT ; 
 int QED_LM_10000baseT_Full_BIT ; 
 int QED_LM_1000baseKX_Full_BIT ; 
 int QED_LM_1000baseT_Full_BIT ; 
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
 int QED_LM_Backplane_BIT ; 
 int QED_LM_FIBRE_BIT ; 
 int QED_LM_TP_BIT ; 
 int /*<<< orphan*/  QED_MSG_DEBUG ; 
 scalar_t__ qed_mcp_get_board_config (struct qed_hwfn*,struct qed_ptt*,int*) ; 
 scalar_t__ qed_mcp_get_media_type (struct qed_hwfn*,struct qed_ptt*,int*) ; 
 scalar_t__ qed_mcp_get_transceiver_data (struct qed_hwfn*,struct qed_ptt*,int*,int*) ; 
 scalar_t__ qed_mcp_trans_speed_mask (struct qed_hwfn*,struct qed_ptt*,int*) ; 

__attribute__((used)) static void qed_fill_link_capability(struct qed_hwfn *hwfn,
				     struct qed_ptt *ptt, u32 capability,
				     u32 *if_capability)
{
	u32 media_type, tcvr_state, tcvr_type;
	u32 speed_mask, board_cfg;

	if (qed_mcp_get_media_type(hwfn, ptt, &media_type))
		media_type = MEDIA_UNSPECIFIED;

	if (qed_mcp_get_transceiver_data(hwfn, ptt, &tcvr_state, &tcvr_type))
		tcvr_type = ETH_TRANSCEIVER_STATE_UNPLUGGED;

	if (qed_mcp_trans_speed_mask(hwfn, ptt, &speed_mask))
		speed_mask = 0xFFFFFFFF;

	if (qed_mcp_get_board_config(hwfn, ptt, &board_cfg))
		board_cfg = NVM_CFG1_PORT_PORT_TYPE_UNDEFINED;

	DP_VERBOSE(hwfn->cdev, NETIF_MSG_DRV,
		   "Media_type = 0x%x tcvr_state = 0x%x tcvr_type = 0x%x speed_mask = 0x%x board_cfg = 0x%x\n",
		   media_type, tcvr_state, tcvr_type, speed_mask, board_cfg);

	switch (media_type) {
	case MEDIA_DA_TWINAX:
		*if_capability |= QED_LM_FIBRE_BIT;
		if (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_20G)
			*if_capability |= QED_LM_20000baseKR2_Full_BIT;
		/* For DAC media multiple speed capabilities are supported*/
		capability = capability & speed_mask;
		if (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G)
			*if_capability |= QED_LM_1000baseKX_Full_BIT;
		if (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G)
			*if_capability |= QED_LM_10000baseCR_Full_BIT;
		if (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G)
			*if_capability |= QED_LM_40000baseCR4_Full_BIT;
		if (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G)
			*if_capability |= QED_LM_25000baseCR_Full_BIT;
		if (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_50G)
			*if_capability |= QED_LM_50000baseCR2_Full_BIT;
		if (capability &
			NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_BB_100G)
			*if_capability |= QED_LM_100000baseCR4_Full_BIT;
		break;
	case MEDIA_BASE_T:
		*if_capability |= QED_LM_TP_BIT;
		if (board_cfg & NVM_CFG1_PORT_PORT_TYPE_EXT_PHY) {
			if (capability &
			    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G) {
				*if_capability |= QED_LM_1000baseT_Full_BIT;
			}
			if (capability &
			    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G) {
				*if_capability |= QED_LM_10000baseT_Full_BIT;
			}
		}
		if (board_cfg & NVM_CFG1_PORT_PORT_TYPE_MODULE) {
			*if_capability |= QED_LM_FIBRE_BIT;
			if (tcvr_type == ETH_TRANSCEIVER_TYPE_1000BASET)
				*if_capability |= QED_LM_1000baseT_Full_BIT;
			if (tcvr_type == ETH_TRANSCEIVER_TYPE_10G_BASET)
				*if_capability |= QED_LM_10000baseT_Full_BIT;
		}
		break;
	case MEDIA_SFP_1G_FIBER:
	case MEDIA_SFPP_10G_FIBER:
	case MEDIA_XFP_FIBER:
	case MEDIA_MODULE_FIBER:
		*if_capability |= QED_LM_FIBRE_BIT;
		if (capability &
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G) {
			if ((tcvr_type == ETH_TRANSCEIVER_TYPE_1G_LX) ||
			    (tcvr_type == ETH_TRANSCEIVER_TYPE_1G_SX))
				*if_capability |= QED_LM_1000baseKX_Full_BIT;
		}
		if (capability &
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G) {
			if (tcvr_type == ETH_TRANSCEIVER_TYPE_10G_SR)
				*if_capability |= QED_LM_10000baseSR_Full_BIT;
			if (tcvr_type == ETH_TRANSCEIVER_TYPE_10G_LR)
				*if_capability |= QED_LM_10000baseLR_Full_BIT;
			if (tcvr_type == ETH_TRANSCEIVER_TYPE_10G_LRM)
				*if_capability |= QED_LM_10000baseLRM_Full_BIT;
			if (tcvr_type == ETH_TRANSCEIVER_TYPE_10G_ER)
				*if_capability |= QED_LM_10000baseR_FEC_BIT;
		}
		if (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_20G)
			*if_capability |= QED_LM_20000baseKR2_Full_BIT;
		if (capability &
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G) {
			if (tcvr_type == ETH_TRANSCEIVER_TYPE_25G_SR)
				*if_capability |= QED_LM_25000baseSR_Full_BIT;
		}
		if (capability &
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G) {
			if (tcvr_type == ETH_TRANSCEIVER_TYPE_40G_LR4)
				*if_capability |= QED_LM_40000baseLR4_Full_BIT;
			if (tcvr_type == ETH_TRANSCEIVER_TYPE_40G_SR4)
				*if_capability |= QED_LM_40000baseSR4_Full_BIT;
		}
		if (capability &
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_50G)
			*if_capability |= QED_LM_50000baseKR2_Full_BIT;
		if (capability &
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_BB_100G) {
			if (tcvr_type == ETH_TRANSCEIVER_TYPE_100G_SR4)
				*if_capability |= QED_LM_100000baseSR4_Full_BIT;
		}

		break;
	case MEDIA_KR:
		*if_capability |= QED_LM_Backplane_BIT;
		if (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_20G)
			*if_capability |= QED_LM_20000baseKR2_Full_BIT;
		if (capability &
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G)
			*if_capability |= QED_LM_1000baseKX_Full_BIT;
		if (capability &
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G)
			*if_capability |= QED_LM_10000baseKR_Full_BIT;
		if (capability &
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G)
			*if_capability |= QED_LM_25000baseKR_Full_BIT;
		if (capability &
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G)
			*if_capability |= QED_LM_40000baseKR4_Full_BIT;
		if (capability &
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_50G)
			*if_capability |= QED_LM_50000baseKR2_Full_BIT;
		if (capability &
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_BB_100G)
			*if_capability |= QED_LM_100000baseKR4_Full_BIT;
		break;
	case MEDIA_UNSPECIFIED:
	case MEDIA_NOT_PRESENT:
		DP_VERBOSE(hwfn->cdev, QED_MSG_DEBUG,
			   "Unknown media and transceiver type;\n");
		break;
	}
}