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
typedef  enum fw_port_type { ____Placeholder_fw_port_type } fw_port_type ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseKR_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseR_FEC_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseSR_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseKX_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_25000baseCR_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_25000baseKR_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_50000baseSR2_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Asym_Pause_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Autoneg_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Backplane_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_FIBRE_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Pause_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_TP_BIT ; 
 unsigned int FW_PORT_CAP32_802_3_ASM_DIR ; 
 unsigned int FW_PORT_CAP32_802_3_PAUSE ; 
 unsigned int FW_PORT_CAP32_ANEG ; 
 unsigned int FW_PORT_CAP32_SPEED_100G ; 
 unsigned int FW_PORT_CAP32_SPEED_100M ; 
 unsigned int FW_PORT_CAP32_SPEED_10G ; 
 unsigned int FW_PORT_CAP32_SPEED_1G ; 
 unsigned int FW_PORT_CAP32_SPEED_25G ; 
 unsigned int FW_PORT_CAP32_SPEED_40G ; 
 unsigned int FW_PORT_CAP32_SPEED_50G ; 
#define  FW_PORT_TYPE_BP40_BA 149 
#define  FW_PORT_TYPE_BP4_AP 148 
#define  FW_PORT_TYPE_BP_AP 147 
#define  FW_PORT_TYPE_BT_SGMII 146 
#define  FW_PORT_TYPE_BT_XAUI 145 
#define  FW_PORT_TYPE_BT_XFI 144 
#define  FW_PORT_TYPE_CR2_QSFP 143 
#define  FW_PORT_TYPE_CR4_QSFP 142 
#define  FW_PORT_TYPE_CR_QSFP 141 
#define  FW_PORT_TYPE_FIBER_XAUI 140 
#define  FW_PORT_TYPE_FIBER_XFI 139 
#define  FW_PORT_TYPE_KR 138 
#define  FW_PORT_TYPE_KR4_100G 137 
#define  FW_PORT_TYPE_KR_SFP28 136 
#define  FW_PORT_TYPE_KR_XLAUI 135 
#define  FW_PORT_TYPE_KX 134 
#define  FW_PORT_TYPE_KX4 133 
#define  FW_PORT_TYPE_QSA 132 
#define  FW_PORT_TYPE_QSFP 131 
#define  FW_PORT_TYPE_QSFP_10G 130 
#define  FW_PORT_TYPE_SFP 129 
#define  FW_PORT_TYPE_SFP28 128 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void fw_caps_to_lmm(enum fw_port_type port_type,
			   unsigned int fw_caps,
			   unsigned long *link_mode_mask)
{
	#define SET_LMM(__lmm_name) \
		__set_bit(ETHTOOL_LINK_MODE_ ## __lmm_name ## _BIT, \
			  link_mode_mask)

	#define FW_CAPS_TO_LMM(__fw_name, __lmm_name) \
		do { \
			if (fw_caps & FW_PORT_CAP32_ ## __fw_name) \
				SET_LMM(__lmm_name); \
		} while (0)

	switch (port_type) {
	case FW_PORT_TYPE_BT_SGMII:
	case FW_PORT_TYPE_BT_XFI:
	case FW_PORT_TYPE_BT_XAUI:
		SET_LMM(TP);
		FW_CAPS_TO_LMM(SPEED_100M, 100baseT_Full);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseT_Full);
		break;

	case FW_PORT_TYPE_KX4:
	case FW_PORT_TYPE_KX:
		SET_LMM(Backplane);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseKX_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKX4_Full);
		break;

	case FW_PORT_TYPE_KR:
		SET_LMM(Backplane);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKR_Full);
		break;

	case FW_PORT_TYPE_BP_AP:
		SET_LMM(Backplane);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseKX_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseR_FEC);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKR_Full);
		break;

	case FW_PORT_TYPE_BP4_AP:
		SET_LMM(Backplane);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseKX_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseR_FEC);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKR_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKX4_Full);
		break;

	case FW_PORT_TYPE_FIBER_XFI:
	case FW_PORT_TYPE_FIBER_XAUI:
	case FW_PORT_TYPE_SFP:
	case FW_PORT_TYPE_QSFP_10G:
	case FW_PORT_TYPE_QSA:
		SET_LMM(FIBRE);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseT_Full);
		break;

	case FW_PORT_TYPE_BP40_BA:
	case FW_PORT_TYPE_QSFP:
		SET_LMM(FIBRE);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_40G, 40000baseSR4_Full);
		break;

	case FW_PORT_TYPE_CR_QSFP:
	case FW_PORT_TYPE_SFP28:
		SET_LMM(FIBRE);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_25G, 25000baseCR_Full);
		break;

	case FW_PORT_TYPE_KR_SFP28:
		SET_LMM(Backplane);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKR_Full);
		FW_CAPS_TO_LMM(SPEED_25G, 25000baseKR_Full);
		break;

	case FW_PORT_TYPE_KR_XLAUI:
		SET_LMM(Backplane);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseKX_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKR_Full);
		FW_CAPS_TO_LMM(SPEED_40G, 40000baseKR4_Full);
		break;

	case FW_PORT_TYPE_CR2_QSFP:
		SET_LMM(FIBRE);
		FW_CAPS_TO_LMM(SPEED_50G, 50000baseSR2_Full);
		break;

	case FW_PORT_TYPE_KR4_100G:
	case FW_PORT_TYPE_CR4_QSFP:
		SET_LMM(FIBRE);
		FW_CAPS_TO_LMM(SPEED_1G,  1000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseSR_Full);
		FW_CAPS_TO_LMM(SPEED_40G, 40000baseSR4_Full);
		FW_CAPS_TO_LMM(SPEED_25G, 25000baseCR_Full);
		FW_CAPS_TO_LMM(SPEED_50G, 50000baseCR2_Full);
		FW_CAPS_TO_LMM(SPEED_100G, 100000baseCR4_Full);
		break;

	default:
		break;
	}

	FW_CAPS_TO_LMM(ANEG, Autoneg);
	FW_CAPS_TO_LMM(802_3_PAUSE, Pause);
	FW_CAPS_TO_LMM(802_3_ASM_DIR, Asym_Pause);

	#undef FW_CAPS_TO_LMM
	#undef SET_LMM
}