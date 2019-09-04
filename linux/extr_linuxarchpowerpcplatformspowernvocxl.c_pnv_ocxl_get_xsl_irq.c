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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct pci_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 

int pnv_ocxl_get_xsl_irq(struct pci_dev *dev, int *hwirq)
{
	int rc;

	rc = of_property_read_u32(dev->dev.of_node, "ibm,opal-xsl-irq", hwirq);
	if (rc) {
		dev_err(&dev->dev,
			"Can't get translation interrupt for device\n");
		return rc;
	}
	return 0;
}