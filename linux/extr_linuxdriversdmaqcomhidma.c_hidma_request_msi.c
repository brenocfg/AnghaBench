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
struct hidma_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int hidma_request_msi(struct hidma_dev *dmadev,
			     struct platform_device *pdev)
{
#ifdef CONFIG_GENERIC_MSI_IRQ_DOMAIN
	int rc;
	struct msi_desc *desc;
	struct msi_desc *failed_desc = NULL;

	rc = platform_msi_domain_alloc_irqs(&pdev->dev, HIDMA_MSI_INTS,
					    hidma_write_msi_msg);
	if (rc)
		return rc;

	for_each_msi_entry(desc, &pdev->dev) {
		if (!desc->platform.msi_index)
			dmadev->msi_virqbase = desc->irq;

		rc = devm_request_irq(&pdev->dev, desc->irq,
				       hidma_chirq_handler_msi,
				       0, "qcom-hidma-msi",
				       &dmadev->lldev);
		if (rc) {
			failed_desc = desc;
			break;
		}
	}

	if (rc) {
		/* free allocated MSI interrupts above */
		for_each_msi_entry(desc, &pdev->dev) {
			if (desc == failed_desc)
				break;
			devm_free_irq(&pdev->dev, desc->irq,
				      &dmadev->lldev);
		}
	} else {
		/* Add callback to free MSIs on teardown */
		hidma_ll_setup_irq(dmadev->lldev, true);

	}
	if (rc)
		dev_warn(&pdev->dev,
			 "failed to request MSI irq, falling back to wired IRQ\n");
	return rc;
#else
	return -EINVAL;
#endif
}