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
struct tegra_usb_phy {int /*<<< orphan*/  pll_u; int /*<<< orphan*/  is_ulpi_phy; int /*<<< orphan*/  vbus; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utmip_pad_close (struct tegra_usb_phy*) ; 

__attribute__((used)) static void tegra_usb_phy_close(struct tegra_usb_phy *phy)
{
	if (!IS_ERR(phy->vbus))
		regulator_disable(phy->vbus);

	if (!phy->is_ulpi_phy)
		utmip_pad_close(phy);

	clk_disable_unprepare(phy->pll_u);
}