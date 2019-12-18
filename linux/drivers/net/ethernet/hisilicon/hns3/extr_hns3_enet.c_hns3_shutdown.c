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
struct hnae3_ae_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D3hot ; 
 scalar_t__ SYSTEM_POWER_OFF ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct hnae3_ae_dev*) ; 
 int /*<<< orphan*/  hnae3_unregister_ae_dev (struct hnae3_ae_dev*) ; 
 struct hnae3_ae_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ system_state ; 

__attribute__((used)) static void hns3_shutdown(struct pci_dev *pdev)
{
	struct hnae3_ae_dev *ae_dev = pci_get_drvdata(pdev);

	hnae3_unregister_ae_dev(ae_dev);
	devm_kfree(&pdev->dev, ae_dev);
	pci_set_drvdata(pdev, NULL);

	if (system_state == SYSTEM_POWER_OFF)
		pci_set_power_state(pdev, PCI_D3hot);
}