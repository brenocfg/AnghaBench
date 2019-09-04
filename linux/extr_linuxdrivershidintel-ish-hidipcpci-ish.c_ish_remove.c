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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct ishtp_device {int dummy; } ;
struct ish_hw {int /*<<< orphan*/  mem_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ishtp_device*) ; 
 int /*<<< orphan*/  ish_device_disable (struct ishtp_device*) ; 
 int /*<<< orphan*/  ishtp_bus_remove_all_clients (struct ishtp_device*,int) ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct ishtp_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 struct ish_hw* to_ish_hw (struct ishtp_device*) ; 

__attribute__((used)) static void ish_remove(struct pci_dev *pdev)
{
	struct ishtp_device *ishtp_dev = pci_get_drvdata(pdev);
	struct ish_hw *hw = to_ish_hw(ishtp_dev);

	ishtp_bus_remove_all_clients(ishtp_dev, false);
	ish_device_disable(ishtp_dev);

	free_irq(pdev->irq, ishtp_dev);
	pci_iounmap(pdev, hw->mem_addr);
	pci_release_regions(pdev);
	pci_clear_master(pdev);
	pci_disable_device(pdev);
}