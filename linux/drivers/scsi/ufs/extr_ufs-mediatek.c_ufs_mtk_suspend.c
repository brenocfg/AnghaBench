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
struct ufs_mtk_host {int /*<<< orphan*/  mphy; } ;
struct ufs_hba {int dummy; } ;
typedef  enum ufs_pm_op { ____Placeholder_ufs_pm_op } ufs_pm_op ;

/* Variables and functions */
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 struct ufs_mtk_host* ufshcd_get_variant (struct ufs_hba*) ; 
 scalar_t__ ufshcd_is_link_hibern8 (struct ufs_hba*) ; 

__attribute__((used)) static int ufs_mtk_suspend(struct ufs_hba *hba, enum ufs_pm_op pm_op)
{
	struct ufs_mtk_host *host = ufshcd_get_variant(hba);

	if (ufshcd_is_link_hibern8(hba))
		phy_power_off(host->mphy);

	return 0;
}