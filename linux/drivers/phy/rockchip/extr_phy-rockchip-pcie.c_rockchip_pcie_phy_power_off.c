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
struct rockchip_pcie_phy {int /*<<< orphan*/  pcie_mutex; TYPE_1__* phy_data; int /*<<< orphan*/  reg_base; scalar_t__ pwr_cnt; int /*<<< orphan*/  phy_rst; } ;
struct phy_pcie_instance {scalar_t__ index; } ;
struct phy {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcie_laneoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIWORD_UPDATE (int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PHY_LANE_IDLE_A_SHIFT ; 
 int /*<<< orphan*/  PHY_LANE_IDLE_MASK ; 
 int PHY_LANE_IDLE_OFF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct phy_pcie_instance* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 struct rockchip_pcie_phy* to_pcie_phy (struct phy_pcie_instance*) ; 

__attribute__((used)) static int rockchip_pcie_phy_power_off(struct phy *phy)
{
	struct phy_pcie_instance *inst = phy_get_drvdata(phy);
	struct rockchip_pcie_phy *rk_phy = to_pcie_phy(inst);
	int err = 0;

	mutex_lock(&rk_phy->pcie_mutex);

	regmap_write(rk_phy->reg_base,
		     rk_phy->phy_data->pcie_laneoff,
		     HIWORD_UPDATE(PHY_LANE_IDLE_OFF,
				   PHY_LANE_IDLE_MASK,
				   PHY_LANE_IDLE_A_SHIFT + inst->index));

	if (--rk_phy->pwr_cnt)
		goto err_out;

	err = reset_control_assert(rk_phy->phy_rst);
	if (err) {
		dev_err(&phy->dev, "assert phy_rst err %d\n", err);
		goto err_restore;
	}

err_out:
	mutex_unlock(&rk_phy->pcie_mutex);
	return 0;

err_restore:
	rk_phy->pwr_cnt++;
	regmap_write(rk_phy->reg_base,
		     rk_phy->phy_data->pcie_laneoff,
		     HIWORD_UPDATE(!PHY_LANE_IDLE_OFF,
				   PHY_LANE_IDLE_MASK,
				   PHY_LANE_IDLE_A_SHIFT + inst->index));
	mutex_unlock(&rk_phy->pcie_mutex);
	return err;
}