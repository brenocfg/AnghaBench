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
struct TYPE_2__ {void (* release ) (struct xen_pcibk_device*,struct pci_dev*,int) ;} ;

/* Variables and functions */
 void stub1 (struct xen_pcibk_device*,struct pci_dev*,int) ; 
 TYPE_1__* xen_pcibk_backend ; 

__attribute__((used)) static inline void xen_pcibk_release_pci_dev(struct xen_pcibk_device *pdev,
					     struct pci_dev *dev, bool lock)
{
	if (xen_pcibk_backend && xen_pcibk_backend->release)
		return xen_pcibk_backend->release(pdev, dev, lock);
}