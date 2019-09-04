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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {scalar_t__ device; scalar_t__ vendor; int /*<<< orphan*/  dev; } ;
struct cpt_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpt_unregister_interrupts (struct cpt_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct cpt_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpt_shutdown(struct pci_dev *pdev)
{
	struct cpt_device *cpt = pci_get_drvdata(pdev);

	if (!cpt)
		return;

	dev_info(&pdev->dev, "Shutdown device %x:%x.\n",
		 (u32)pdev->vendor, (u32)pdev->device);

	cpt_unregister_interrupts(cpt);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);
}