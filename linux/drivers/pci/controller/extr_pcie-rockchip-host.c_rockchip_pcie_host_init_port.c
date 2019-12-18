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
struct rockchip_pcie {int link_gen; int lanes_map; int /*<<< orphan*/ * phys; scalar_t__ apb_base; int /*<<< orphan*/  ep_gpio; struct device* dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int BIT (int) ; 
 int MAX_LANE_NUM ; 
 scalar_t__ PCIE_CLIENT_BASIC_STATUS1 ; 
 scalar_t__ PCIE_CLIENT_CONFIG ; 
 int PCIE_CLIENT_LINK_TRAIN_ENABLE ; 
 scalar_t__ PCIE_CORE_CONFIG_VENDOR ; 
 scalar_t__ PCIE_CORE_CTRL ; 
 scalar_t__ PCIE_CORE_CTRL_PLC1 ; 
 int PCIE_CORE_CTRL_PLC1_FTS_CNT ; 
 int PCIE_CORE_CTRL_PLC1_FTS_MASK ; 
 int PCIE_CORE_CTRL_PLC1_FTS_SHIFT ; 
 int PCIE_CORE_PL_CONF_LANE_MASK ; 
 int PCIE_CORE_PL_CONF_LANE_SHIFT ; 
 int /*<<< orphan*/  PCIE_LINK_IS_GEN2 (int) ; 
 int /*<<< orphan*/  PCIE_LINK_UP (int) ; 
 scalar_t__ PCIE_RC_CONFIG_DCSR ; 
 int PCIE_RC_CONFIG_DCSR_MPS_256 ; 
 int PCIE_RC_CONFIG_DCSR_MPS_MASK ; 
 scalar_t__ PCIE_RC_CONFIG_LCS ; 
 scalar_t__ PCIE_RC_CONFIG_LINK_CAP ; 
 int PCIE_RC_CONFIG_LINK_CAP_L0S ; 
 scalar_t__ PCIE_RC_CONFIG_RID_CCR ; 
 int PCIE_RC_CONFIG_SCC_SHIFT ; 
 scalar_t__ PCIE_RC_CONFIG_THP_CAP ; 
 int PCIE_RC_CONFIG_THP_CAP_NEXT_MASK ; 
 int PCI_CLASS_BRIDGE_PCI ; 
 int PCI_EXP_LNKCTL_RCB ; 
 int PCI_EXP_LNKCTL_RL ; 
 int PCI_EXP_LNKSTA_SLC ; 
 int ROCKCHIP_VENDOR_ID ; 
 int USEC_PER_MSEC ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int readl_poll_timeout (scalar_t__,int,int /*<<< orphan*/ ,int,int) ; 
 int rockchip_pcie_init_port (struct rockchip_pcie*) ; 
 int rockchip_pcie_lane_map (struct rockchip_pcie*) ; 
 int rockchip_pcie_read (struct rockchip_pcie*,scalar_t__) ; 
 int /*<<< orphan*/  rockchip_pcie_set_power_limit (struct rockchip_pcie*) ; 
 int /*<<< orphan*/  rockchip_pcie_write (struct rockchip_pcie*,int,scalar_t__) ; 

__attribute__((used)) static int rockchip_pcie_host_init_port(struct rockchip_pcie *rockchip)
{
	struct device *dev = rockchip->dev;
	int err, i = MAX_LANE_NUM;
	u32 status;

	gpiod_set_value_cansleep(rockchip->ep_gpio, 0);

	err = rockchip_pcie_init_port(rockchip);
	if (err)
		return err;

	/* Fix the transmitted FTS count desired to exit from L0s. */
	status = rockchip_pcie_read(rockchip, PCIE_CORE_CTRL_PLC1);
	status = (status & ~PCIE_CORE_CTRL_PLC1_FTS_MASK) |
		 (PCIE_CORE_CTRL_PLC1_FTS_CNT << PCIE_CORE_CTRL_PLC1_FTS_SHIFT);
	rockchip_pcie_write(rockchip, status, PCIE_CORE_CTRL_PLC1);

	rockchip_pcie_set_power_limit(rockchip);

	/* Set RC's clock architecture as common clock */
	status = rockchip_pcie_read(rockchip, PCIE_RC_CONFIG_LCS);
	status |= PCI_EXP_LNKSTA_SLC << 16;
	rockchip_pcie_write(rockchip, status, PCIE_RC_CONFIG_LCS);

	/* Set RC's RCB to 128 */
	status = rockchip_pcie_read(rockchip, PCIE_RC_CONFIG_LCS);
	status |= PCI_EXP_LNKCTL_RCB;
	rockchip_pcie_write(rockchip, status, PCIE_RC_CONFIG_LCS);

	/* Enable Gen1 training */
	rockchip_pcie_write(rockchip, PCIE_CLIENT_LINK_TRAIN_ENABLE,
			    PCIE_CLIENT_CONFIG);

	gpiod_set_value_cansleep(rockchip->ep_gpio, 1);

	/* 500ms timeout value should be enough for Gen1/2 training */
	err = readl_poll_timeout(rockchip->apb_base + PCIE_CLIENT_BASIC_STATUS1,
				 status, PCIE_LINK_UP(status), 20,
				 500 * USEC_PER_MSEC);
	if (err) {
		dev_err(dev, "PCIe link training gen1 timeout!\n");
		goto err_power_off_phy;
	}

	if (rockchip->link_gen == 2) {
		/*
		 * Enable retrain for gen2. This should be configured only after
		 * gen1 finished.
		 */
		status = rockchip_pcie_read(rockchip, PCIE_RC_CONFIG_LCS);
		status |= PCI_EXP_LNKCTL_RL;
		rockchip_pcie_write(rockchip, status, PCIE_RC_CONFIG_LCS);

		err = readl_poll_timeout(rockchip->apb_base + PCIE_CORE_CTRL,
					 status, PCIE_LINK_IS_GEN2(status), 20,
					 500 * USEC_PER_MSEC);
		if (err)
			dev_dbg(dev, "PCIe link training gen2 timeout, fall back to gen1!\n");
	}

	/* Check the final link width from negotiated lane counter from MGMT */
	status = rockchip_pcie_read(rockchip, PCIE_CORE_CTRL);
	status = 0x1 << ((status & PCIE_CORE_PL_CONF_LANE_MASK) >>
			  PCIE_CORE_PL_CONF_LANE_SHIFT);
	dev_dbg(dev, "current link width is x%d\n", status);

	/* Power off unused lane(s) */
	rockchip->lanes_map = rockchip_pcie_lane_map(rockchip);
	for (i = 0; i < MAX_LANE_NUM; i++) {
		if (!(rockchip->lanes_map & BIT(i))) {
			dev_dbg(dev, "idling lane %d\n", i);
			phy_power_off(rockchip->phys[i]);
		}
	}

	rockchip_pcie_write(rockchip, ROCKCHIP_VENDOR_ID,
			    PCIE_CORE_CONFIG_VENDOR);
	rockchip_pcie_write(rockchip,
			    PCI_CLASS_BRIDGE_PCI << PCIE_RC_CONFIG_SCC_SHIFT,
			    PCIE_RC_CONFIG_RID_CCR);

	/* Clear THP cap's next cap pointer to remove L1 substate cap */
	status = rockchip_pcie_read(rockchip, PCIE_RC_CONFIG_THP_CAP);
	status &= ~PCIE_RC_CONFIG_THP_CAP_NEXT_MASK;
	rockchip_pcie_write(rockchip, status, PCIE_RC_CONFIG_THP_CAP);

	/* Clear L0s from RC's link cap */
	if (of_property_read_bool(dev->of_node, "aspm-no-l0s")) {
		status = rockchip_pcie_read(rockchip, PCIE_RC_CONFIG_LINK_CAP);
		status &= ~PCIE_RC_CONFIG_LINK_CAP_L0S;
		rockchip_pcie_write(rockchip, status, PCIE_RC_CONFIG_LINK_CAP);
	}

	status = rockchip_pcie_read(rockchip, PCIE_RC_CONFIG_DCSR);
	status &= ~PCIE_RC_CONFIG_DCSR_MPS_MASK;
	status |= PCIE_RC_CONFIG_DCSR_MPS_256;
	rockchip_pcie_write(rockchip, status, PCIE_RC_CONFIG_DCSR);

	return 0;
err_power_off_phy:
	while (i--)
		phy_power_off(rockchip->phys[i]);
	i = MAX_LANE_NUM;
	while (i--)
		phy_exit(rockchip->phys[i]);
	return err;
}