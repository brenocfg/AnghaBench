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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct jz4740_adc {int /*<<< orphan*/  clk; TYPE_1__* mem; int /*<<< orphan*/  base; int /*<<< orphan*/  irq; int /*<<< orphan*/  gc; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int IRQ_LEVEL ; 
 int /*<<< orphan*/  IRQ_MSK (int) ; 
 int IRQ_NOPROBE ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_remove_generic_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ *) ; 
 struct jz4740_adc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 

__attribute__((used)) static int jz4740_adc_remove(struct platform_device *pdev)
{
	struct jz4740_adc *adc = platform_get_drvdata(pdev);

	mfd_remove_devices(&pdev->dev);

	irq_remove_generic_chip(adc->gc, IRQ_MSK(5), IRQ_NOPROBE | IRQ_LEVEL, 0);
	kfree(adc->gc);
	irq_set_chained_handler_and_data(adc->irq, NULL, NULL);

	iounmap(adc->base);
	release_mem_region(adc->mem->start, resource_size(adc->mem));

	clk_put(adc->clk);

	return 0;
}