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
struct rockchip_pcie {int link_gen; int /*<<< orphan*/ * phys; int /*<<< orphan*/  pipe_rst; int /*<<< orphan*/  mgmt_rst; int /*<<< orphan*/  core_rst; int /*<<< orphan*/  mgmt_sticky_rst; scalar_t__ is_rc; int /*<<< orphan*/  lanes; int /*<<< orphan*/  pclk_rst; int /*<<< orphan*/  aclk_rst; int /*<<< orphan*/  pm_rst; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int MAX_LANE_NUM ; 
 int PCIE_CLIENT_ARI_ENABLE ; 
 int /*<<< orphan*/  PCIE_CLIENT_CONFIG ; 
 int PCIE_CLIENT_CONF_DISABLE ; 
 int PCIE_CLIENT_CONF_ENABLE ; 
 int PCIE_CLIENT_CONF_LANE_NUM (int /*<<< orphan*/ ) ; 
 int PCIE_CLIENT_GEN_SEL_1 ; 
 int PCIE_CLIENT_GEN_SEL_2 ; 
 int PCIE_CLIENT_LINK_TRAIN_ENABLE ; 
 int PCIE_CLIENT_MODE_EP ; 
 int PCIE_CLIENT_MODE_RC ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int phy_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int phy_power_on (int /*<<< orphan*/ ) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rockchip_pcie_write (struct rockchip_pcie*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

int rockchip_pcie_init_port(struct rockchip_pcie *rockchip)
{
	struct device *dev = rockchip->dev;
	int err, i;
	u32 regs;

	err = reset_control_assert(rockchip->aclk_rst);
	if (err) {
		dev_err(dev, "assert aclk_rst err %d\n", err);
		return err;
	}

	err = reset_control_assert(rockchip->pclk_rst);
	if (err) {
		dev_err(dev, "assert pclk_rst err %d\n", err);
		return err;
	}

	err = reset_control_assert(rockchip->pm_rst);
	if (err) {
		dev_err(dev, "assert pm_rst err %d\n", err);
		return err;
	}

	for (i = 0; i < MAX_LANE_NUM; i++) {
		err = phy_init(rockchip->phys[i]);
		if (err) {
			dev_err(dev, "init phy%d err %d\n", i, err);
			goto err_exit_phy;
		}
	}

	err = reset_control_assert(rockchip->core_rst);
	if (err) {
		dev_err(dev, "assert core_rst err %d\n", err);
		goto err_exit_phy;
	}

	err = reset_control_assert(rockchip->mgmt_rst);
	if (err) {
		dev_err(dev, "assert mgmt_rst err %d\n", err);
		goto err_exit_phy;
	}

	err = reset_control_assert(rockchip->mgmt_sticky_rst);
	if (err) {
		dev_err(dev, "assert mgmt_sticky_rst err %d\n", err);
		goto err_exit_phy;
	}

	err = reset_control_assert(rockchip->pipe_rst);
	if (err) {
		dev_err(dev, "assert pipe_rst err %d\n", err);
		goto err_exit_phy;
	}

	udelay(10);

	err = reset_control_deassert(rockchip->pm_rst);
	if (err) {
		dev_err(dev, "deassert pm_rst err %d\n", err);
		goto err_exit_phy;
	}

	err = reset_control_deassert(rockchip->aclk_rst);
	if (err) {
		dev_err(dev, "deassert aclk_rst err %d\n", err);
		goto err_exit_phy;
	}

	err = reset_control_deassert(rockchip->pclk_rst);
	if (err) {
		dev_err(dev, "deassert pclk_rst err %d\n", err);
		goto err_exit_phy;
	}

	if (rockchip->link_gen == 2)
		rockchip_pcie_write(rockchip, PCIE_CLIENT_GEN_SEL_2,
				    PCIE_CLIENT_CONFIG);
	else
		rockchip_pcie_write(rockchip, PCIE_CLIENT_GEN_SEL_1,
				    PCIE_CLIENT_CONFIG);

	regs = PCIE_CLIENT_LINK_TRAIN_ENABLE | PCIE_CLIENT_ARI_ENABLE |
	       PCIE_CLIENT_CONF_LANE_NUM(rockchip->lanes);

	if (rockchip->is_rc)
		regs |= PCIE_CLIENT_CONF_ENABLE | PCIE_CLIENT_MODE_RC;
	else
		regs |= PCIE_CLIENT_CONF_DISABLE | PCIE_CLIENT_MODE_EP;

	rockchip_pcie_write(rockchip, regs, PCIE_CLIENT_CONFIG);

	for (i = 0; i < MAX_LANE_NUM; i++) {
		err = phy_power_on(rockchip->phys[i]);
		if (err) {
			dev_err(dev, "power on phy%d err %d\n", i, err);
			goto err_power_off_phy;
		}
	}

	/*
	 * Please don't reorder the deassert sequence of the following
	 * four reset pins.
	 */
	err = reset_control_deassert(rockchip->mgmt_sticky_rst);
	if (err) {
		dev_err(dev, "deassert mgmt_sticky_rst err %d\n", err);
		goto err_power_off_phy;
	}

	err = reset_control_deassert(rockchip->core_rst);
	if (err) {
		dev_err(dev, "deassert core_rst err %d\n", err);
		goto err_power_off_phy;
	}

	err = reset_control_deassert(rockchip->mgmt_rst);
	if (err) {
		dev_err(dev, "deassert mgmt_rst err %d\n", err);
		goto err_power_off_phy;
	}

	err = reset_control_deassert(rockchip->pipe_rst);
	if (err) {
		dev_err(dev, "deassert pipe_rst err %d\n", err);
		goto err_power_off_phy;
	}

	return 0;
err_power_off_phy:
	while (i--)
		phy_power_off(rockchip->phys[i]);
	i = MAX_LANE_NUM;
err_exit_phy:
	while (i--)
		phy_exit(rockchip->phys[i]);
	return err;
}