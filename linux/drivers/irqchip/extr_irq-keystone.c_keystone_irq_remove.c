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
struct keystone_irq_device {int /*<<< orphan*/  irqd; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int KEYSTONE_N_IRQ ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct keystone_irq_device*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 struct keystone_irq_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int keystone_irq_remove(struct platform_device *pdev)
{
	struct keystone_irq_device *kirq = platform_get_drvdata(pdev);
	int hwirq;

	free_irq(kirq->irq, kirq);

	for (hwirq = 0; hwirq < KEYSTONE_N_IRQ; hwirq++)
		irq_dispose_mapping(irq_find_mapping(kirq->irqd, hwirq));

	irq_domain_remove(kirq->irqd);
	return 0;
}