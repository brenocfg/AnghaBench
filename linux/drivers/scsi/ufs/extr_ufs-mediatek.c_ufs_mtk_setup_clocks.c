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
typedef  enum ufs_notify_change_status { ____Placeholder_ufs_notify_change_status } ufs_notify_change_status ;

/* Variables and functions */
 int EINVAL ; 
#define  POST_CHANGE 129 
#define  PRE_CHANGE 128 
 int phy_power_off (int /*<<< orphan*/ ) ; 
 int phy_power_on (int /*<<< orphan*/ ) ; 
 struct ufs_mtk_host* ufshcd_get_variant (struct ufs_hba*) ; 

__attribute__((used)) static int ufs_mtk_setup_clocks(struct ufs_hba *hba, bool on,
				enum ufs_notify_change_status status)
{
	struct ufs_mtk_host *host = ufshcd_get_variant(hba);
	int ret = -EINVAL;

	/*
	 * In case ufs_mtk_init() is not yet done, simply ignore.
	 * This ufs_mtk_setup_clocks() shall be called from
	 * ufs_mtk_init() after init is done.
	 */
	if (!host)
		return 0;

	switch (status) {
	case PRE_CHANGE:
		if (!on)
			ret = phy_power_off(host->mphy);
		break;
	case POST_CHANGE:
		if (on)
			ret = phy_power_on(host->mphy);
		break;
	}

	return ret;
}