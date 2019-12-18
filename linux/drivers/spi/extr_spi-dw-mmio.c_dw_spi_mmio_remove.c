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
struct platform_device {int dummy; } ;
struct dw_spi_mmio {int /*<<< orphan*/  clk; int /*<<< orphan*/  pclk; int /*<<< orphan*/  dws; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_spi_remove_host (int /*<<< orphan*/ *) ; 
 struct dw_spi_mmio* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int dw_spi_mmio_remove(struct platform_device *pdev)
{
	struct dw_spi_mmio *dwsmmio = platform_get_drvdata(pdev);

	dw_spi_remove_host(&dwsmmio->dws);
	clk_disable_unprepare(dwsmmio->pclk);
	clk_disable_unprepare(dwsmmio->clk);

	return 0;
}