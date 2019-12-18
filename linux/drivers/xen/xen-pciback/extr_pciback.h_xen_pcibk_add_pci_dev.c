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
typedef  int /*<<< orphan*/  publish_pci_dev_cb ;
struct TYPE_2__ {int (* add ) (struct xen_pcibk_device*,struct pci_dev*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct xen_pcibk_device*,struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* xen_pcibk_backend ; 

__attribute__((used)) static inline int xen_pcibk_add_pci_dev(struct xen_pcibk_device *pdev,
					struct pci_dev *dev,
					int devid,
					publish_pci_dev_cb publish_cb)
{
	if (xen_pcibk_backend && xen_pcibk_backend->add)
		return xen_pcibk_backend->add(pdev, dev, devid, publish_cb);
	return -1;
}