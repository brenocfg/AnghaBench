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
struct cxl_afu {int dummy; } ;
struct cxl {int slices; struct cxl_afu** afu; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxl_pci_remove_adapter (struct cxl*) ; 
 int /*<<< orphan*/  cxl_pci_remove_afu (struct cxl_afu*) ; 
 struct cxl* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void cxl_remove(struct pci_dev *dev)
{
	struct cxl *adapter = pci_get_drvdata(dev);
	struct cxl_afu *afu;
	int i;

	/*
	 * Lock to prevent someone grabbing a ref through the adapter list as
	 * we are removing it
	 */
	for (i = 0; i < adapter->slices; i++) {
		afu = adapter->afu[i];
		cxl_pci_remove_afu(afu);
	}
	cxl_pci_remove_adapter(adapter);
}