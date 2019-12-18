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
struct cxl_afu {TYPE_1__* native; int /*<<< orphan*/ * p2n_mmio; } ;
struct TYPE_2__ {int /*<<< orphan*/ * afu_desc_mmio; int /*<<< orphan*/ * p1n_mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pci_unmap_slice_regs(struct cxl_afu *afu)
{
	if (afu->p2n_mmio) {
		iounmap(afu->p2n_mmio);
		afu->p2n_mmio = NULL;
	}
	if (afu->native->p1n_mmio) {
		iounmap(afu->native->p1n_mmio);
		afu->native->p1n_mmio = NULL;
	}
	if (afu->native->afu_desc_mmio) {
		iounmap(afu->native->afu_desc_mmio);
		afu->native->afu_desc_mmio = NULL;
	}
}