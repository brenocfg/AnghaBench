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
struct ufs_qcom_host {struct phy* generic_phy; } ;
struct ufs_hba {int dummy; } ;
struct phy {int dummy; } ;
typedef  enum ufs_pm_op { ____Placeholder_ufs_pm_op } ufs_pm_op ;

/* Variables and functions */
 int /*<<< orphan*/  phy_power_off (struct phy*) ; 
 int /*<<< orphan*/  ufs_qcom_disable_lane_clks (struct ufs_qcom_host*) ; 
 int /*<<< orphan*/  ufs_qcom_is_link_active (struct ufs_hba*) ; 
 scalar_t__ ufs_qcom_is_link_off (struct ufs_hba*) ; 
 struct ufs_qcom_host* ufshcd_get_variant (struct ufs_hba*) ; 

__attribute__((used)) static int ufs_qcom_suspend(struct ufs_hba *hba, enum ufs_pm_op pm_op)
{
	struct ufs_qcom_host *host = ufshcd_get_variant(hba);
	struct phy *phy = host->generic_phy;
	int ret = 0;

	if (ufs_qcom_is_link_off(hba)) {
		/*
		 * Disable the tx/rx lane symbol clocks before PHY is
		 * powered down as the PLL source should be disabled
		 * after downstream clocks are disabled.
		 */
		ufs_qcom_disable_lane_clks(host);
		phy_power_off(phy);

	} else if (!ufs_qcom_is_link_active(hba)) {
		ufs_qcom_disable_lane_clks(host);
	}

	return ret;
}