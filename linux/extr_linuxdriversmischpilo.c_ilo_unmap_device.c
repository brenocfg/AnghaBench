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
struct pci_dev {int dummy; } ;
struct ilo_hwinfo {int /*<<< orphan*/  mmio_vaddr; int /*<<< orphan*/  ram_vaddr; int /*<<< orphan*/  db_vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ilo_unmap_device(struct pci_dev *pdev, struct ilo_hwinfo *hw)
{
	pci_iounmap(pdev, hw->db_vaddr);
	pci_iounmap(pdev, hw->ram_vaddr);
	pci_iounmap(pdev, hw->mmio_vaddr);
}