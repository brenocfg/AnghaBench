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
struct phy {int dummy; } ;
struct mtk_mipi_tx {int /*<<< orphan*/  pll; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_mipi_tx_power_off_signal (struct phy*) ; 
 struct mtk_mipi_tx* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int mtk_mipi_tx_power_off(struct phy *phy)
{
	struct mtk_mipi_tx *mipi_tx = phy_get_drvdata(phy);

	/* Enable pad tie low, disable DSI Lane LDO outputs */
	mtk_mipi_tx_power_off_signal(phy);

	/* Disable PLL and power down core */
	clk_disable_unprepare(mipi_tx->pll);

	return 0;
}