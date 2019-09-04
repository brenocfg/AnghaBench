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
struct pci_dev {int dummy; } ;
struct cxl_irq_ranges {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct cxl {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pnv_cxl_release_hwirq_ranges (struct cxl_irq_ranges*,struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

void cxl_pci_release_irq_ranges(struct cxl_irq_ranges *irqs,
				struct cxl *adapter)
{
	struct pci_dev *dev = to_pci_dev(adapter->dev.parent);

	pnv_cxl_release_hwirq_ranges(irqs, dev);
}