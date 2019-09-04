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
struct tegra_mipi {int /*<<< orphan*/  clk; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 struct tegra_mipi* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int tegra_mipi_remove(struct platform_device *pdev)
{
	struct tegra_mipi *mipi = platform_get_drvdata(pdev);

	clk_unprepare(mipi->clk);

	return 0;
}