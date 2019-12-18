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
struct ufs_mtk_phy {int /*<<< orphan*/  unipro_clk; int /*<<< orphan*/  dev; int /*<<< orphan*/  mp_clk; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct ufs_mtk_phy* get_ufs_mtk_phy (struct phy*) ; 
 int /*<<< orphan*/  ufs_mtk_phy_set_active (struct ufs_mtk_phy*) ; 

__attribute__((used)) static int ufs_mtk_phy_power_on(struct phy *generic_phy)
{
	struct ufs_mtk_phy *phy = get_ufs_mtk_phy(generic_phy);
	int ret;

	ret = clk_prepare_enable(phy->unipro_clk);
	if (ret) {
		dev_err(phy->dev, "unipro_clk enable failed %d\n", ret);
		goto out;
	}

	ret = clk_prepare_enable(phy->mp_clk);
	if (ret) {
		dev_err(phy->dev, "mp_clk enable failed %d\n", ret);
		goto out_unprepare_unipro_clk;
	}

	ufs_mtk_phy_set_active(phy);

	return 0;

out_unprepare_unipro_clk:
	clk_disable_unprepare(phy->unipro_clk);
out:
	return ret;
}