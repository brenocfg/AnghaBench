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
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_mipi_tx_power_on_signal (struct phy*) ; 
 struct mtk_mipi_tx* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int mtk_mipi_tx_power_on(struct phy *phy)
{
	struct mtk_mipi_tx *mipi_tx = phy_get_drvdata(phy);
	int ret;

	/* Power up core and enable PLL */
	ret = clk_prepare_enable(mipi_tx->pll);
	if (ret < 0)
		return ret;

	/* Enable DSI Lane LDO outputs, disable pad tie low */
	mtk_mipi_tx_power_on_signal(phy);

	return 0;
}