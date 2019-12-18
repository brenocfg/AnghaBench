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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct madera {int /*<<< orphan*/  irq_data; int /*<<< orphan*/  irq; int /*<<< orphan*/ * irq_dev; } ;

/* Variables and functions */
 struct madera* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int madera_irq_remove(struct platform_device *pdev)
{
	struct madera *madera = dev_get_drvdata(pdev->dev.parent);

	/*
	 * The IRQ is disabled by the parent MFD driver before
	 * it starts cleaning up all child drivers
	 */
	madera->irq_dev = NULL;
	regmap_del_irq_chip(madera->irq, madera->irq_data);

	return 0;
}