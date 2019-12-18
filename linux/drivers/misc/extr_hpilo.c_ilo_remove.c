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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct ilo_hwinfo {TYPE_1__ cdev; } ;

/* Variables and functions */
 int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 int /*<<< orphan*/  clear_device (struct ilo_hwinfo*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ilo_hwinfo*) ; 
 int /*<<< orphan*/  ilo_class ; 
 int /*<<< orphan*/  ilo_disable_interrupts (struct ilo_hwinfo*) ; 
 scalar_t__* ilo_hwdev ; 
 int /*<<< orphan*/  ilo_major ; 
 int /*<<< orphan*/  ilo_unmap_device (struct pci_dev*,struct ilo_hwinfo*) ; 
 int /*<<< orphan*/  kfree (struct ilo_hwinfo*) ; 
 int max_ccb ; 
 struct ilo_hwinfo* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 

__attribute__((used)) static void ilo_remove(struct pci_dev *pdev)
{
	int i, minor;
	struct ilo_hwinfo *ilo_hw = pci_get_drvdata(pdev);

	if (!ilo_hw)
		return;

	clear_device(ilo_hw);

	minor = MINOR(ilo_hw->cdev.dev);
	for (i = minor; i < minor + max_ccb; i++)
		device_destroy(ilo_class, MKDEV(ilo_major, i));

	cdev_del(&ilo_hw->cdev);
	ilo_disable_interrupts(ilo_hw);
	free_irq(pdev->irq, ilo_hw);
	ilo_unmap_device(pdev, ilo_hw);
	pci_release_regions(pdev);
	/*
	 * pci_disable_device(pdev) used to be here. But this PCI device has
	 * two functions with interrupt lines connected to a single pin. The
	 * other one is a USB host controller. So when we disable the PIN here
	 * e.g. by rmmod hpilo, the controller stops working. It is because
	 * the interrupt link is disabled in ACPI since it is not refcounted
	 * yet. See acpi_pci_link_free_irq called from acpi_pci_irq_disable.
	 */
	kfree(ilo_hw);
	ilo_hwdev[(minor / max_ccb)] = 0;
}