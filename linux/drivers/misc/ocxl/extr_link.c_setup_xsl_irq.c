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
struct spa {int /*<<< orphan*/  irq_name; int /*<<< orphan*/  virq; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ocxl_link {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; int /*<<< orphan*/  domain; struct spa* spa; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  irq_create_mapping (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int map_irq_registers (struct pci_dev*,struct spa*) ; 
 int pnv_ocxl_get_xsl_irq (struct pci_dev*,int*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocxl_link*) ; 
 int /*<<< orphan*/  unmap_irq_registers (struct spa*) ; 
 int /*<<< orphan*/  xsl_fault_handler ; 

__attribute__((used)) static int setup_xsl_irq(struct pci_dev *dev, struct ocxl_link *link)
{
	struct spa *spa = link->spa;
	int rc;
	int hwirq;

	rc = pnv_ocxl_get_xsl_irq(dev, &hwirq);
	if (rc)
		return rc;

	rc = map_irq_registers(dev, spa);
	if (rc)
		return rc;

	spa->irq_name = kasprintf(GFP_KERNEL, "ocxl-xsl-%x-%x-%x",
				link->domain, link->bus, link->dev);
	if (!spa->irq_name) {
		dev_err(&dev->dev, "Can't allocate name for xsl interrupt\n");
		rc = -ENOMEM;
		goto err_xsl;
	}
	/*
	 * At some point, we'll need to look into allowing a higher
	 * number of interrupts. Could we have an IRQ domain per link?
	 */
	spa->virq = irq_create_mapping(NULL, hwirq);
	if (!spa->virq) {
		dev_err(&dev->dev,
			"irq_create_mapping failed for translation interrupt\n");
		rc = -EINVAL;
		goto err_name;
	}

	dev_dbg(&dev->dev, "hwirq %d mapped to virq %d\n", hwirq, spa->virq);

	rc = request_irq(spa->virq, xsl_fault_handler, 0, spa->irq_name,
			link);
	if (rc) {
		dev_err(&dev->dev,
			"request_irq failed for translation interrupt: %d\n",
			rc);
		rc = -EINVAL;
		goto err_mapping;
	}
	return 0;

err_mapping:
	irq_dispose_mapping(spa->virq);
err_name:
	kfree(spa->irq_name);
err_xsl:
	unmap_irq_registers(spa);
	return rc;
}