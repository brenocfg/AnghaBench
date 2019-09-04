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
struct hidma_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void hidma_free_msis(struct hidma_dev *dmadev)
{
#ifdef CONFIG_GENERIC_MSI_IRQ_DOMAIN
	struct device *dev = dmadev->ddev.dev;
	struct msi_desc *desc;

	/* free allocated MSI interrupts above */
	for_each_msi_entry(desc, dev)
		devm_free_irq(dev, desc->irq, &dmadev->lldev);

	platform_msi_domain_free_irqs(dev);
#endif
}