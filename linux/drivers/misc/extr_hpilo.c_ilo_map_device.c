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
struct pci_dev {int subsystem_device; int /*<<< orphan*/  dev; } ;
struct ilo_hwinfo {int /*<<< orphan*/ * mmio_vaddr; int /*<<< orphan*/ * ram_vaddr; int /*<<< orphan*/ * db_vaddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ILOHW_CCB_SZ ; 
 int ONE_DB_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int max_ccb ; 
 void* pci_iomap (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/ * pci_iomap_range (struct pci_dev*,int,unsigned long,int) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int pci_resource_len (struct pci_dev*,int) ; 

__attribute__((used)) static int ilo_map_device(struct pci_dev *pdev, struct ilo_hwinfo *hw)
{
	int bar;
	unsigned long off;

	/* map the memory mapped i/o registers */
	hw->mmio_vaddr = pci_iomap(pdev, 1, 0);
	if (hw->mmio_vaddr == NULL) {
		dev_err(&pdev->dev, "Error mapping mmio\n");
		goto out;
	}

	/* map the adapter shared memory region */
	if (pdev->subsystem_device == 0x00E4) {
		bar = 5;
		/* Last 8k is reserved for CCBs */
		off = pci_resource_len(pdev, bar) - 0x2000;
	} else {
		bar = 2;
		off = 0;
	}
	hw->ram_vaddr = pci_iomap_range(pdev, bar, off, max_ccb * ILOHW_CCB_SZ);
	if (hw->ram_vaddr == NULL) {
		dev_err(&pdev->dev, "Error mapping shared mem\n");
		goto mmio_free;
	}

	/* map the doorbell aperture */
	hw->db_vaddr = pci_iomap(pdev, 3, max_ccb * ONE_DB_SIZE);
	if (hw->db_vaddr == NULL) {
		dev_err(&pdev->dev, "Error mapping doorbell\n");
		goto ram_free;
	}

	return 0;
ram_free:
	pci_iounmap(pdev, hw->ram_vaddr);
mmio_free:
	pci_iounmap(pdev, hw->mmio_vaddr);
out:
	return -ENOMEM;
}