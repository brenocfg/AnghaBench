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
struct pci_dev {int dummy; } ;
struct cxl {TYPE_1__* native; } ;
struct TYPE_2__ {int /*<<< orphan*/ * p1_mmio; void* p2_mmio; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p1_base (struct pci_dev*) ; 
 int /*<<< orphan*/  p1_size (struct pci_dev*) ; 
 int /*<<< orphan*/  p2_base (struct pci_dev*) ; 
 int /*<<< orphan*/  p2_size (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int) ; 
 scalar_t__ pci_request_region (struct pci_dev*,int,char*) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxl_map_adapter_regs(struct cxl *adapter, struct pci_dev *dev)
{
	if (pci_request_region(dev, 2, "priv 2 regs"))
		goto err1;
	if (pci_request_region(dev, 0, "priv 1 regs"))
		goto err2;

	pr_devel("cxl_map_adapter_regs: p1: %#016llx %#llx, p2: %#016llx %#llx",
			p1_base(dev), p1_size(dev), p2_base(dev), p2_size(dev));

	if (!(adapter->native->p1_mmio = ioremap(p1_base(dev), p1_size(dev))))
		goto err3;

	if (!(adapter->native->p2_mmio = ioremap(p2_base(dev), p2_size(dev))))
		goto err4;

	return 0;

err4:
	iounmap(adapter->native->p1_mmio);
	adapter->native->p1_mmio = NULL;
err3:
	pci_release_region(dev, 0);
err2:
	pci_release_region(dev, 2);
err1:
	return -ENOMEM;
}