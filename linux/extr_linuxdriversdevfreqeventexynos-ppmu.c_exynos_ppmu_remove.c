#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;
struct exynos_ppmu {TYPE_1__ ppmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct exynos_ppmu* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int exynos_ppmu_remove(struct platform_device *pdev)
{
	struct exynos_ppmu *info = platform_get_drvdata(pdev);

	clk_disable_unprepare(info->ppmu.clk);

	return 0;
}