#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cxl_afu {TYPE_1__* adapter; int /*<<< orphan*/  configured_state; } ;
struct TYPE_6__ {TYPE_2__* sl_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* release_serr_irq ) (struct cxl_afu*) ;} ;
struct TYPE_4__ {TYPE_3__* native; } ;

/* Variables and functions */
 int atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxl_native_release_psl_irq (struct cxl_afu*) ; 
 int /*<<< orphan*/  pci_unmap_slice_regs (struct cxl_afu*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  stub1 (struct cxl_afu*) ; 

__attribute__((used)) static void pci_deconfigure_afu(struct cxl_afu *afu)
{
	/*
	 * It's okay to deconfigure when AFU is already locked, otherwise wait
	 * until there are no readers
	 */
	if (atomic_read(&afu->configured_state) != -1) {
		while (atomic_cmpxchg(&afu->configured_state, 0, -1) != -1)
			schedule();
	}
	cxl_native_release_psl_irq(afu);
	if (afu->adapter->native->sl_ops->release_serr_irq)
		afu->adapter->native->sl_ops->release_serr_irq(afu);
	pci_unmap_slice_regs(afu);
}