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
struct tegra_bpmp_thermal {int /*<<< orphan*/  bpmp; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MRQ_THERMAL ; 
 struct tegra_bpmp_thermal* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tegra_bpmp_free_mrq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_bpmp_thermal*) ; 

__attribute__((used)) static int tegra_bpmp_thermal_remove(struct platform_device *pdev)
{
	struct tegra_bpmp_thermal *tegra = platform_get_drvdata(pdev);

	tegra_bpmp_free_mrq(tegra->bpmp, MRQ_THERMAL, tegra);

	return 0;
}