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
struct irqsteer_data {int irq_count; int /*<<< orphan*/  ipg_clk; int /*<<< orphan*/  domain; int /*<<< orphan*/ * irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct irqsteer_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int imx_irqsteer_remove(struct platform_device *pdev)
{
	struct irqsteer_data *irqsteer_data = platform_get_drvdata(pdev);
	int i;

	for (i = 0; i < irqsteer_data->irq_count; i++)
		irq_set_chained_handler_and_data(irqsteer_data->irq[i],
						 NULL, NULL);

	irq_domain_remove(irqsteer_data->domain);

	clk_disable_unprepare(irqsteer_data->ipg_clk);

	return 0;
}