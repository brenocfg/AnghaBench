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
struct xen_pcibk_device {int dummy; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int (* find ) (struct pci_dev*,struct xen_pcibk_device*,unsigned int*,unsigned int*,unsigned int*) ;} ;

/* Variables and functions */
 int stub1 (struct pci_dev*,struct xen_pcibk_device*,unsigned int*,unsigned int*,unsigned int*) ; 
 TYPE_1__* xen_pcibk_backend ; 

__attribute__((used)) static inline int xen_pcibk_get_pcifront_dev(struct pci_dev *pcidev,
					     struct xen_pcibk_device *pdev,
					     unsigned int *domain,
					     unsigned int *bus,
					     unsigned int *devfn)
{
	if (xen_pcibk_backend && xen_pcibk_backend->find)
		return xen_pcibk_backend->find(pcidev, pdev, domain, bus,
					       devfn);
	return -1;
}