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
struct TYPE_2__ {scalar_t__ platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SMP ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cpu_possible_mask ; 
 int cpuidle_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  exynos_coupled_idle_driver ; 
 scalar_t__ exynos_cpuidle_pdata ; 
 void* exynos_enter_aftr ; 
 int /*<<< orphan*/  exynos_idle_driver ; 
 scalar_t__ of_machine_is_compatible (char*) ; 

__attribute__((used)) static int exynos_cpuidle_probe(struct platform_device *pdev)
{
	int ret;

	if (IS_ENABLED(CONFIG_SMP) &&
	    (of_machine_is_compatible("samsung,exynos4210") ||
	     of_machine_is_compatible("samsung,exynos3250"))) {
		exynos_cpuidle_pdata = pdev->dev.platform_data;

		ret = cpuidle_register(&exynos_coupled_idle_driver,
				       cpu_possible_mask);
	} else {
		exynos_enter_aftr = (void *)(pdev->dev.platform_data);

		ret = cpuidle_register(&exynos_idle_driver, NULL);
	}

	if (ret) {
		dev_err(&pdev->dev, "failed to register cpuidle driver\n");
		return ret;
	}

	return 0;
}