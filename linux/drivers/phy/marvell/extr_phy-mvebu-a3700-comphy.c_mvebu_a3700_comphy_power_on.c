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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  bus_width; } ;
struct phy {TYPE_1__ attrs; } ;
struct mvebu_a3700_comphy_lane {int mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  id; int /*<<< orphan*/  port; int /*<<< orphan*/  submode; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPHY_FW_MODE (int) ; 
 int /*<<< orphan*/  COMPHY_FW_NET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int COMPHY_FW_NOT_SUPPORTED ; 
 int /*<<< orphan*/  COMPHY_FW_PCIE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPHY_FW_SPEED_1_25G ; 
 int /*<<< orphan*/  COMPHY_FW_SPEED_3_125G ; 
 int /*<<< orphan*/  COMPHY_FW_SPEED_5G ; 
 int /*<<< orphan*/  COMPHY_SIP_POWER_ON ; 
 int ENOTSUPP ; 
#define  PHY_INTERFACE_MODE_2500BASEX 133 
#define  PHY_INTERFACE_MODE_SGMII 132 
#define  PHY_MODE_ETHERNET 131 
#define  PHY_MODE_PCIE 130 
#define  PHY_MODE_SATA 129 
#define  PHY_MODE_USB_HOST_SS 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int mvebu_a3700_comphy_get_fw_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mvebu_a3700_comphy_smc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mvebu_a3700_comphy_lane* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int mvebu_a3700_comphy_power_on(struct phy *phy)
{
	struct mvebu_a3700_comphy_lane *lane = phy_get_drvdata(phy);
	u32 fw_param;
	int fw_mode;
	int ret;

	fw_mode = mvebu_a3700_comphy_get_fw_mode(lane->id, lane->port,
						 lane->mode, lane->submode);
	if (fw_mode < 0) {
		dev_err(lane->dev, "invalid COMPHY mode\n");
		return fw_mode;
	}

	switch (lane->mode) {
	case PHY_MODE_USB_HOST_SS:
		dev_dbg(lane->dev, "set lane %d to USB3 host mode\n", lane->id);
		fw_param = COMPHY_FW_MODE(fw_mode);
		break;
	case PHY_MODE_SATA:
		dev_dbg(lane->dev, "set lane %d to SATA mode\n", lane->id);
		fw_param = COMPHY_FW_MODE(fw_mode);
		break;
	case PHY_MODE_ETHERNET:
		switch (lane->submode) {
		case PHY_INTERFACE_MODE_SGMII:
			dev_dbg(lane->dev, "set lane %d to SGMII mode\n",
				lane->id);
			fw_param = COMPHY_FW_NET(fw_mode, lane->port,
						 COMPHY_FW_SPEED_1_25G);
			break;
		case PHY_INTERFACE_MODE_2500BASEX:
			dev_dbg(lane->dev, "set lane %d to HS SGMII mode\n",
				lane->id);
			fw_param = COMPHY_FW_NET(fw_mode, lane->port,
						 COMPHY_FW_SPEED_3_125G);
			break;
		default:
			dev_err(lane->dev, "unsupported PHY submode (%d)\n",
				lane->submode);
			return -ENOTSUPP;
		}
		break;
	case PHY_MODE_PCIE:
		dev_dbg(lane->dev, "set lane %d to PCIe mode\n", lane->id);
		fw_param = COMPHY_FW_PCIE(fw_mode, lane->port,
					  COMPHY_FW_SPEED_5G,
					  phy->attrs.bus_width);
		break;
	default:
		dev_err(lane->dev, "unsupported PHY mode (%d)\n", lane->mode);
		return -ENOTSUPP;
	}

	ret = mvebu_a3700_comphy_smc(COMPHY_SIP_POWER_ON, lane->id, fw_param);
	if (ret == COMPHY_FW_NOT_SUPPORTED)
		dev_err(lane->dev,
			"unsupported SMC call, try updating your firmware\n");

	return ret;
}