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
struct mtk_dpi {int power_ctl; int power_sta; int /*<<< orphan*/  engine_clk; int /*<<< orphan*/  pixel_clk; } ;
typedef  enum mtk_dpi_power_ctl { ____Placeholder_mtk_dpi_power_ctl } mtk_dpi_power_ctl ;

/* Variables and functions */
 int DPI_POWER_ENABLE ; 
 int DPI_POWER_START ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_dpi_disable (struct mtk_dpi*) ; 

__attribute__((used)) static void mtk_dpi_power_off(struct mtk_dpi *dpi, enum mtk_dpi_power_ctl pctl)
{
	dpi->power_ctl &= ~pctl;

	if ((dpi->power_ctl & DPI_POWER_START) ||
	    (dpi->power_ctl & DPI_POWER_ENABLE))
		return;

	if (!dpi->power_sta)
		return;

	mtk_dpi_disable(dpi);
	clk_disable_unprepare(dpi->pixel_clk);
	clk_disable_unprepare(dpi->engine_clk);
	dpi->power_sta = false;
}