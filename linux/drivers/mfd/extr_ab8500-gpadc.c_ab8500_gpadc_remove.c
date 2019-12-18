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
struct ab8500_gpadc {scalar_t__ irq_sw; scalar_t__ irq_hw; int /*<<< orphan*/  dev; int /*<<< orphan*/  regu; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct ab8500_gpadc*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct ab8500_gpadc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ab8500_gpadc_remove(struct platform_device *pdev)
{
	struct ab8500_gpadc *gpadc = platform_get_drvdata(pdev);

	/* remove this gpadc entry from the list */
	list_del(&gpadc->node);
	/* remove interrupt  - completion of Sw ADC conversion */
	if (gpadc->irq_sw >= 0)
		free_irq(gpadc->irq_sw, gpadc);
	if (gpadc->irq_hw >= 0)
		free_irq(gpadc->irq_hw, gpadc);

	pm_runtime_get_sync(gpadc->dev);
	pm_runtime_disable(gpadc->dev);

	regulator_disable(gpadc->regu);

	pm_runtime_set_suspended(gpadc->dev);

	pm_runtime_put_noidle(gpadc->dev);

	return 0;
}