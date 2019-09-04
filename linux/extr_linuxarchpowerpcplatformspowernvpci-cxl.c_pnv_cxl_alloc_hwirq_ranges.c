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
struct pnv_phb {scalar_t__ msi_base; int /*<<< orphan*/  msi_bmp; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct pci_controller {struct pnv_phb* private_data; } ;
struct cxl_irq_ranges {int* range; scalar_t__* offset; } ;

/* Variables and functions */
 int CXL_IRQ_RANGES ; 
 int ENOSPC ; 
 int /*<<< orphan*/  memset (struct cxl_irq_ranges*,int /*<<< orphan*/ ,int) ; 
 int msi_bitmap_alloc_hwirqs (int /*<<< orphan*/ *,int) ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnv_cxl_release_hwirq_ranges (struct cxl_irq_ranges*,struct pci_dev*) ; 
 int /*<<< orphan*/  pr_devel (char*,int,scalar_t__,int) ; 

int pnv_cxl_alloc_hwirq_ranges(struct cxl_irq_ranges *irqs,
			       struct pci_dev *dev, int num)
{
	struct pci_controller *hose = pci_bus_to_host(dev->bus);
	struct pnv_phb *phb = hose->private_data;
	int i, hwirq, try;

	memset(irqs, 0, sizeof(struct cxl_irq_ranges));

	/* 0 is reserved for the multiplexed PSL DSI interrupt */
	for (i = 1; i < CXL_IRQ_RANGES && num; i++) {
		try = num;
		while (try) {
			hwirq = msi_bitmap_alloc_hwirqs(&phb->msi_bmp, try);
			if (hwirq >= 0)
				break;
			try /= 2;
		}
		if (!try)
			goto fail;

		irqs->offset[i] = phb->msi_base + hwirq;
		irqs->range[i] = try;
		pr_devel("cxl alloc irq range 0x%x: offset: 0x%lx  limit: %li\n",
			 i, irqs->offset[i], irqs->range[i]);
		num -= try;
	}
	if (num)
		goto fail;

	return 0;
fail:
	pnv_cxl_release_hwirq_ranges(irqs, dev);
	return -ENOSPC;
}