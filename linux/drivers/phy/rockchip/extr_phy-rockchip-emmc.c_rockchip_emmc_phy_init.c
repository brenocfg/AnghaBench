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
struct rockchip_emmc_phy {int /*<<< orphan*/ * emmcclk; } ;
struct phy {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 struct rockchip_emmc_phy* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int rockchip_emmc_phy_init(struct phy *phy)
{
	struct rockchip_emmc_phy *rk_phy = phy_get_drvdata(phy);
	int ret = 0;

	/*
	 * We purposely get the clock here and not in probe to avoid the
	 * circular dependency problem.  We expect:
	 * - PHY driver to probe
	 * - SDHCI driver to start probe
	 * - SDHCI driver to register it's clock
	 * - SDHCI driver to get the PHY
	 * - SDHCI driver to init the PHY
	 *
	 * The clock is optional, so upon any error we just set to NULL.
	 *
	 * NOTE: we don't do anything special for EPROBE_DEFER here.  Given the
	 * above expected use case, EPROBE_DEFER isn't sensible to expect, so
	 * it's just like any other error.
	 */
	rk_phy->emmcclk = clk_get(&phy->dev, "emmcclk");
	if (IS_ERR(rk_phy->emmcclk)) {
		dev_dbg(&phy->dev, "Error getting emmcclk: %d\n", ret);
		rk_phy->emmcclk = NULL;
	}

	return ret;
}