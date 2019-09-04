#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct qlcnic_hardware_context {scalar_t__ port_type; int board_type; int module_type; scalar_t__ has_link_events; void* link_autoneg; int /*<<< orphan*/  physical_port; int /*<<< orphan*/  link_duplex; scalar_t__ link_speed; scalar_t__ linkup; int /*<<< orphan*/  pci_func; } ;
struct qlcnic_adapter {struct qlcnic_hardware_context* ahw; TYPE_1__* pdev; int /*<<< orphan*/  netdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_5__ {void* port; void* autoneg; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  duplex; scalar_t__ speed; } ;
struct ethtool_link_ksettings {TYPE_3__ link_modes; TYPE_2__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ADVERTISED_10000baseT_Full ; 
 scalar_t__ ADVERTISED_1000baseT_Full ; 
 scalar_t__ ADVERTISED_1000baseT_Half ; 
 scalar_t__ ADVERTISED_100baseT_Full ; 
 scalar_t__ ADVERTISED_100baseT_Half ; 
 scalar_t__ ADVERTISED_Autoneg ; 
 scalar_t__ ADVERTISED_FIBRE ; 
 scalar_t__ ADVERTISED_MII ; 
 scalar_t__ ADVERTISED_TP ; 
 void* AUTONEG_DISABLE ; 
 void* AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int EIO ; 
#define  LINKEVENT_MODULE_OPTICAL_LRM 148 
#define  LINKEVENT_MODULE_OPTICAL_SFP_1G 147 
#define  LINKEVENT_MODULE_OPTICAL_SRLR 146 
#define  LINKEVENT_MODULE_OPTICAL_UNKNOWN 145 
#define  LINKEVENT_MODULE_TWINAX 144 
#define  LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLE 143 
#define  LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLELEN 142 
 scalar_t__ P3P_LINK_SPEED_MHZ ; 
 int /*<<< orphan*/  P3P_LINK_SPEED_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ P3P_LINK_SPEED_VAL (int /*<<< orphan*/ ,scalar_t__) ; 
 void* PORT_FIBRE ; 
 void* PORT_MII ; 
 void* PORT_OTHER ; 
 void* PORT_TP ; 
#define  QLCNIC_BRDTYPE_P3P_10000_BASE_T 141 
#define  QLCNIC_BRDTYPE_P3P_10G_CX4 140 
#define  QLCNIC_BRDTYPE_P3P_10G_CX4_LP 139 
#define  QLCNIC_BRDTYPE_P3P_10G_SFP_CT 138 
#define  QLCNIC_BRDTYPE_P3P_10G_SFP_PLUS 137 
#define  QLCNIC_BRDTYPE_P3P_10G_SFP_QT 136 
#define  QLCNIC_BRDTYPE_P3P_10G_TP 135 
#define  QLCNIC_BRDTYPE_P3P_10G_XFP 134 
#define  QLCNIC_BRDTYPE_P3P_4_GB 133 
#define  QLCNIC_BRDTYPE_P3P_4_GB_MM 132 
#define  QLCNIC_BRDTYPE_P3P_HMEZ 131 
#define  QLCNIC_BRDTYPE_P3P_IMEZ 130 
#define  QLCNIC_BRDTYPE_P3P_REF_QG 129 
#define  QLCNIC_BRDTYPE_P3P_XG_LOM 128 
 scalar_t__ QLCNIC_GBE ; 
 scalar_t__ QLCNIC_PORT_MODE_802_3_AP ; 
 int /*<<< orphan*/  QLCNIC_PORT_MODE_ADDR ; 
 scalar_t__ QLCNIC_XGBE ; 
 scalar_t__ QLCRD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ SPEED_UNKNOWN ; 
 scalar_t__ SUPPORTED_10000baseT_Full ; 
 scalar_t__ SUPPORTED_1000baseT_Full ; 
 scalar_t__ SUPPORTED_1000baseT_Half ; 
 scalar_t__ SUPPORTED_100baseT_Full ; 
 scalar_t__ SUPPORTED_100baseT_Half ; 
 scalar_t__ SUPPORTED_10baseT_Full ; 
 scalar_t__ SUPPORTED_10baseT_Half ; 
 scalar_t__ SUPPORTED_Autoneg ; 
 scalar_t__ SUPPORTED_FIBRE ; 
 scalar_t__ SUPPORTED_MII ; 
 scalar_t__ SUPPORTED_TP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qlcnic_82xx_get_link_ksettings(struct qlcnic_adapter *adapter,
					  struct ethtool_link_ksettings *ecmd)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	u32 speed, reg;
	int check_sfp_module = 0, err = 0;
	u16 pcifn = ahw->pci_func;
	u32 supported, advertising;

	/* read which mode */
	if (adapter->ahw->port_type == QLCNIC_GBE) {
		supported = (SUPPORTED_10baseT_Half |
				   SUPPORTED_10baseT_Full |
				   SUPPORTED_100baseT_Half |
				   SUPPORTED_100baseT_Full |
				   SUPPORTED_1000baseT_Half |
				   SUPPORTED_1000baseT_Full);

		advertising = (ADVERTISED_100baseT_Half |
				     ADVERTISED_100baseT_Full |
				     ADVERTISED_1000baseT_Half |
				     ADVERTISED_1000baseT_Full);

		ecmd->base.speed = adapter->ahw->link_speed;
		ecmd->base.duplex = adapter->ahw->link_duplex;
		ecmd->base.autoneg = adapter->ahw->link_autoneg;

	} else if (adapter->ahw->port_type == QLCNIC_XGBE) {
		u32 val = 0;
		val = QLCRD32(adapter, QLCNIC_PORT_MODE_ADDR, &err);

		if (val == QLCNIC_PORT_MODE_802_3_AP) {
			supported = SUPPORTED_1000baseT_Full;
			advertising = ADVERTISED_1000baseT_Full;
		} else {
			supported = SUPPORTED_10000baseT_Full;
			advertising = ADVERTISED_10000baseT_Full;
		}

		if (netif_running(adapter->netdev) && ahw->has_link_events) {
			if (ahw->linkup) {
				reg = QLCRD32(adapter,
					      P3P_LINK_SPEED_REG(pcifn), &err);
				speed = P3P_LINK_SPEED_VAL(pcifn, reg);
				ahw->link_speed = speed * P3P_LINK_SPEED_MHZ;
			}

			ecmd->base.speed = ahw->link_speed;
			ecmd->base.autoneg = ahw->link_autoneg;
			ecmd->base.duplex = ahw->link_duplex;
			goto skip;
		}

		ecmd->base.speed = SPEED_UNKNOWN;
		ecmd->base.duplex = DUPLEX_UNKNOWN;
		ecmd->base.autoneg = AUTONEG_DISABLE;
	} else
		return -EIO;

skip:
	ecmd->base.phy_address = adapter->ahw->physical_port;

	switch (adapter->ahw->board_type) {
	case QLCNIC_BRDTYPE_P3P_REF_QG:
	case QLCNIC_BRDTYPE_P3P_4_GB:
	case QLCNIC_BRDTYPE_P3P_4_GB_MM:
		supported |= SUPPORTED_Autoneg;
		advertising |= ADVERTISED_Autoneg;
		/* fall through */
	case QLCNIC_BRDTYPE_P3P_10G_CX4:
	case QLCNIC_BRDTYPE_P3P_10G_CX4_LP:
	case QLCNIC_BRDTYPE_P3P_10000_BASE_T:
		supported |= SUPPORTED_TP;
		advertising |= ADVERTISED_TP;
		ecmd->base.port = PORT_TP;
		ecmd->base.autoneg =  adapter->ahw->link_autoneg;
		break;
	case QLCNIC_BRDTYPE_P3P_IMEZ:
	case QLCNIC_BRDTYPE_P3P_XG_LOM:
	case QLCNIC_BRDTYPE_P3P_HMEZ:
		supported |= SUPPORTED_MII;
		advertising |= ADVERTISED_MII;
		ecmd->base.port = PORT_MII;
		ecmd->base.autoneg = AUTONEG_DISABLE;
		break;
	case QLCNIC_BRDTYPE_P3P_10G_SFP_PLUS:
	case QLCNIC_BRDTYPE_P3P_10G_SFP_CT:
	case QLCNIC_BRDTYPE_P3P_10G_SFP_QT:
		advertising |= ADVERTISED_TP;
		supported |= SUPPORTED_TP;
		check_sfp_module = netif_running(adapter->netdev) &&
				   ahw->has_link_events;
		/* fall through */
	case QLCNIC_BRDTYPE_P3P_10G_XFP:
		supported |= SUPPORTED_FIBRE;
		advertising |= ADVERTISED_FIBRE;
		ecmd->base.port = PORT_FIBRE;
		ecmd->base.autoneg = AUTONEG_DISABLE;
		break;
	case QLCNIC_BRDTYPE_P3P_10G_TP:
		if (adapter->ahw->port_type == QLCNIC_XGBE) {
			ecmd->base.autoneg = AUTONEG_DISABLE;
			supported |= (SUPPORTED_FIBRE | SUPPORTED_TP);
			advertising |=
				(ADVERTISED_FIBRE | ADVERTISED_TP);
			ecmd->base.port = PORT_FIBRE;
			check_sfp_module = netif_running(adapter->netdev) &&
					   ahw->has_link_events;
		} else {
			ecmd->base.autoneg = AUTONEG_ENABLE;
			supported |= (SUPPORTED_TP | SUPPORTED_Autoneg);
			advertising |=
				(ADVERTISED_TP | ADVERTISED_Autoneg);
			ecmd->base.port = PORT_TP;
		}
		break;
	default:
		dev_err(&adapter->pdev->dev, "Unsupported board model %d\n",
			adapter->ahw->board_type);
		return -EIO;
	}

	if (check_sfp_module) {
		switch (adapter->ahw->module_type) {
		case LINKEVENT_MODULE_OPTICAL_UNKNOWN:
		case LINKEVENT_MODULE_OPTICAL_SRLR:
		case LINKEVENT_MODULE_OPTICAL_LRM:
		case LINKEVENT_MODULE_OPTICAL_SFP_1G:
			ecmd->base.port = PORT_FIBRE;
			break;
		case LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLE:
		case LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLELEN:
		case LINKEVENT_MODULE_TWINAX:
			ecmd->base.port = PORT_TP;
			break;
		default:
			ecmd->base.port = PORT_OTHER;
		}
	}

	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.advertising,
						advertising);

	return 0;
}