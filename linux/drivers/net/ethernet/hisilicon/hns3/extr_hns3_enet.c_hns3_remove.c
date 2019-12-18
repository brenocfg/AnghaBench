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
struct hnae3_ae_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCI_IOV ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hnae3_unregister_ae_dev (struct hnae3_ae_dev*) ; 
 int /*<<< orphan*/  hns3_disable_sriov (struct pci_dev*) ; 
 scalar_t__ hns3_is_phys_func (struct pci_dev*) ; 
 struct hnae3_ae_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns3_remove(struct pci_dev *pdev)
{
	struct hnae3_ae_dev *ae_dev = pci_get_drvdata(pdev);

	if (hns3_is_phys_func(pdev) && IS_ENABLED(CONFIG_PCI_IOV))
		hns3_disable_sriov(pdev);

	hnae3_unregister_ae_dev(ae_dev);
	pci_set_drvdata(pdev, NULL);
}