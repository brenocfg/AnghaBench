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
struct da9052_hwmon {int /*<<< orphan*/  tsiref; int /*<<< orphan*/  da9052; scalar_t__ tsi_as_adc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_IRQ_TSIREADY ; 
 int /*<<< orphan*/  da9052_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct da9052_hwmon*) ; 
 struct da9052_hwmon* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9052_hwmon_remove(struct platform_device *pdev)
{
	struct da9052_hwmon *hwmon = platform_get_drvdata(pdev);

	if (hwmon->tsi_as_adc) {
		da9052_free_irq(hwmon->da9052, DA9052_IRQ_TSIREADY, hwmon);
		regulator_disable(hwmon->tsiref);
	}

	return 0;
}