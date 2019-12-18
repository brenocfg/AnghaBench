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
struct ufs_mtk_phy {int /*<<< orphan*/  mp_clk; int /*<<< orphan*/  unipro_clk; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct ufs_mtk_phy* get_ufs_mtk_phy (struct phy*) ; 
 int /*<<< orphan*/  ufs_mtk_phy_set_deep_hibern (struct ufs_mtk_phy*) ; 

__attribute__((used)) static int ufs_mtk_phy_power_off(struct phy *generic_phy)
{
	struct ufs_mtk_phy *phy = get_ufs_mtk_phy(generic_phy);

	ufs_mtk_phy_set_deep_hibern(phy);

	clk_disable_unprepare(phy->unipro_clk);
	clk_disable_unprepare(phy->mp_clk);

	return 0;
}