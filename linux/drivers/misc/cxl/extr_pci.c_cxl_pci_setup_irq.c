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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct cxl {TYPE_1__ dev; } ;

/* Variables and functions */
 int pnv_cxl_ioda_msi_setup (struct pci_dev*,unsigned int,unsigned int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

int cxl_pci_setup_irq(struct cxl *adapter, unsigned int hwirq,
		unsigned int virq)
{
	struct pci_dev *dev = to_pci_dev(adapter->dev.parent);

	return pnv_cxl_ioda_msi_setup(dev, hwirq, virq);
}