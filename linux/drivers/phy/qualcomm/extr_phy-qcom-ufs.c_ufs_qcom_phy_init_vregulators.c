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
struct ufs_qcom_phy {int /*<<< orphan*/  vddp_ref_clk; int /*<<< orphan*/  dev; int /*<<< orphan*/  vdda_phy; int /*<<< orphan*/  vdda_pll; } ;

/* Variables and functions */
 int ufs_qcom_phy_init_vreg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

int ufs_qcom_phy_init_vregulators(struct ufs_qcom_phy *phy_common)
{
	int err;

	err = ufs_qcom_phy_init_vreg(phy_common->dev, &phy_common->vdda_pll,
		"vdda-pll");
	if (err)
		goto out;

	err = ufs_qcom_phy_init_vreg(phy_common->dev, &phy_common->vdda_phy,
		"vdda-phy");

	if (err)
		goto out;

	err = ufs_qcom_phy_init_vreg(phy_common->dev, &phy_common->vddp_ref_clk,
				     "vddp-ref-clk");

out:
	return err;
}