#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct cxl {TYPE_1__ dev; TYPE_2__* native; } ;
struct TYPE_4__ {int /*<<< orphan*/ * p2_mmio; int /*<<< orphan*/ * p1_mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cxl_unmap_adapter_regs(struct cxl *adapter)
{
	if (adapter->native->p1_mmio) {
		iounmap(adapter->native->p1_mmio);
		adapter->native->p1_mmio = NULL;
		pci_release_region(to_pci_dev(adapter->dev.parent), 2);
	}
	if (adapter->native->p2_mmio) {
		iounmap(adapter->native->p2_mmio);
		adapter->native->p2_mmio = NULL;
		pci_release_region(to_pci_dev(adapter->dev.parent), 0);
	}
}