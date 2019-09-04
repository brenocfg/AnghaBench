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
struct pm_irq_chip {int /*<<< orphan*/  irqdomain; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pm_irq_chip* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8xxx_remove_child ; 

__attribute__((used)) static int pm8xxx_remove(struct platform_device *pdev)
{
	int irq = platform_get_irq(pdev, 0);
	struct pm_irq_chip *chip = platform_get_drvdata(pdev);

	device_for_each_child(&pdev->dev, NULL, pm8xxx_remove_child);
	irq_set_chained_handler_and_data(irq, NULL, NULL);
	irq_domain_remove(chip->irqdomain);

	return 0;
}