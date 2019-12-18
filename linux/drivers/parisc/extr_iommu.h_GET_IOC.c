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
struct pci_hba_data {struct ioc* iommu; } ;
struct ioc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct pci_hba_data* parisc_walk_tree (struct device*) ; 

__attribute__((used)) static inline struct ioc *GET_IOC(struct device *dev)
{
	struct pci_hba_data *pdata = parisc_walk_tree(dev);

	if (!pdata)
		return NULL;
	return pdata->iommu;
}