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
struct mtk_thermal {int /*<<< orphan*/  clk_auxadc; int /*<<< orphan*/  clk_peri_therm; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct mtk_thermal* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mtk_thermal_remove(struct platform_device *pdev)
{
	struct mtk_thermal *mt = platform_get_drvdata(pdev);

	clk_disable_unprepare(mt->clk_peri_therm);
	clk_disable_unprepare(mt->clk_auxadc);

	return 0;
}