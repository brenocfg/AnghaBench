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
struct mtk_dpi {int power_ctl; int power_sta; int /*<<< orphan*/  engine_clk; int /*<<< orphan*/  dev; int /*<<< orphan*/  pixel_clk; } ;
typedef  enum mtk_dpi_power_ctl { ____Placeholder_mtk_dpi_power_ctl } mtk_dpi_power_ctl ;

/* Variables and functions */
 int DPI_POWER_ENABLE ; 
 int DPI_POWER_START ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtk_dpi_enable (struct mtk_dpi*) ; 

__attribute__((used)) static int mtk_dpi_power_on(struct mtk_dpi *dpi, enum mtk_dpi_power_ctl pctl)
{
	int ret;

	dpi->power_ctl |= pctl;

	if (!(dpi->power_ctl & DPI_POWER_START) &&
	    !(dpi->power_ctl & DPI_POWER_ENABLE))
		return 0;

	if (dpi->power_sta)
		return 0;

	ret = clk_prepare_enable(dpi->engine_clk);
	if (ret) {
		dev_err(dpi->dev, "Failed to enable engine clock: %d\n", ret);
		goto err_eng;
	}

	ret = clk_prepare_enable(dpi->pixel_clk);
	if (ret) {
		dev_err(dpi->dev, "Failed to enable pixel clock: %d\n", ret);
		goto err_pixel;
	}

	mtk_dpi_enable(dpi);
	dpi->power_sta = true;
	return 0;

err_pixel:
	clk_disable_unprepare(dpi->engine_clk);
err_eng:
	dpi->power_ctl &= ~pctl;
	return ret;
}