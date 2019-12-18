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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ism_dev {int /*<<< orphan*/  smcd; } ;

/* Variables and functions */
 struct ism_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ism_dev_exit (struct ism_dev*) ; 
 int /*<<< orphan*/  kfree (struct ism_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  smcd_free_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ism_remove(struct pci_dev *pdev)
{
	struct ism_dev *ism = dev_get_drvdata(&pdev->dev);

	ism_dev_exit(ism);

	smcd_free_dev(ism->smcd);
	pci_release_mem_regions(pdev);
	pci_disable_device(pdev);
	dev_set_drvdata(&pdev->dev, NULL);
	kfree(ism);
}