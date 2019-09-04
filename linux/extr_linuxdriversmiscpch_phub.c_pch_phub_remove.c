#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct pci_dev {TYPE_1__ dev; } ;
struct pch_phub_reg {int /*<<< orphan*/  pch_phub_base_address; } ;
struct TYPE_4__ {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 TYPE_2__ dev_attr_pch_mac ; 
 int /*<<< orphan*/  kfree (struct pch_phub_reg*) ; 
 int /*<<< orphan*/  pch_bin_attr ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct pch_phub_reg* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pch_phub_remove(struct pci_dev *pdev)
{
	struct pch_phub_reg *chip = pci_get_drvdata(pdev);

	sysfs_remove_file(&pdev->dev.kobj, &dev_attr_pch_mac.attr);
	sysfs_remove_bin_file(&pdev->dev.kobj, &pch_bin_attr);
	pci_iounmap(pdev, chip->pch_phub_base_address);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	kfree(chip);
}