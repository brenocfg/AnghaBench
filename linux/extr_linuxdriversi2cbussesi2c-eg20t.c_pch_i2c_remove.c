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
struct adapter_info {int ch_num; TYPE_1__* pch_data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pch_base_address; int /*<<< orphan*/  pch_adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct adapter_info*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct adapter_info*) ; 
 int /*<<< orphan*/  pch_i2c_disbl_int (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct adapter_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 

__attribute__((used)) static void pch_i2c_remove(struct pci_dev *pdev)
{
	int i;
	struct adapter_info *adap_info = pci_get_drvdata(pdev);

	free_irq(pdev->irq, adap_info);

	for (i = 0; i < adap_info->ch_num; i++) {
		pch_i2c_disbl_int(&adap_info->pch_data[i]);
		i2c_del_adapter(&adap_info->pch_data[i].pch_adapter);
	}

	if (adap_info->pch_data[0].pch_base_address)
		pci_iounmap(pdev, adap_info->pch_data[0].pch_base_address);

	for (i = 0; i < adap_info->ch_num; i++)
		adap_info->pch_data[i].pch_base_address = NULL;

	pci_release_regions(pdev);

	pci_disable_device(pdev);
	kfree(adap_info);
}