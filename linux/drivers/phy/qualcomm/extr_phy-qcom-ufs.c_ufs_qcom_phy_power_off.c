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
struct TYPE_4__ {scalar_t__ reg; } ;
struct ufs_qcom_phy {int /*<<< orphan*/  ufs_reset; TYPE_2__ vdda_phy; int /*<<< orphan*/  dev; TYPE_2__ vdda_pll; TYPE_2__ vddp_ref_clk; TYPE_1__* phy_spec_ops; } ;
struct phy {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* power_control ) (struct ufs_qcom_phy*,int) ;} ;

/* Variables and functions */
 struct ufs_qcom_phy* get_ufs_qcom_phy (struct phy*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ufs_qcom_phy*,int) ; 
 int /*<<< orphan*/  ufs_qcom_phy_disable_iface_clk (struct ufs_qcom_phy*) ; 
 int /*<<< orphan*/  ufs_qcom_phy_disable_ref_clk (struct ufs_qcom_phy*) ; 
 int /*<<< orphan*/  ufs_qcom_phy_disable_vreg (int /*<<< orphan*/ ,TYPE_2__*) ; 

int ufs_qcom_phy_power_off(struct phy *generic_phy)
{
	struct ufs_qcom_phy *phy_common = get_ufs_qcom_phy(generic_phy);

	phy_common->phy_spec_ops->power_control(phy_common, false);

	if (phy_common->vddp_ref_clk.reg)
		ufs_qcom_phy_disable_vreg(phy_common->dev,
					  &phy_common->vddp_ref_clk);
	ufs_qcom_phy_disable_ref_clk(phy_common);
	ufs_qcom_phy_disable_iface_clk(phy_common);

	ufs_qcom_phy_disable_vreg(phy_common->dev, &phy_common->vdda_pll);
	ufs_qcom_phy_disable_vreg(phy_common->dev, &phy_common->vdda_phy);
	reset_control_assert(phy_common->ufs_reset);
	return 0;
}