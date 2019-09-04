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
struct TYPE_4__ {void* mfn; } ;
struct TYPE_5__ {TYPE_1__ domU; } ;
struct TYPE_6__ {TYPE_2__ console; void* store_mfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  FIX_PARAVIRT_BOOTMAP ; 
 int /*<<< orphan*/ * HYPERVISOR_shared_info ; 
 scalar_t__ HYPERVISOR_update_va_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pte_ma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fix_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 void* mfn_to_pfn (void*) ; 
 int /*<<< orphan*/  xen_dummy_shared_info ; 
 int /*<<< orphan*/  xen_mm_pin_all () ; 
 TYPE_3__* xen_start_info ; 

void xen_pv_pre_suspend(void)
{
	xen_mm_pin_all();

	xen_start_info->store_mfn = mfn_to_pfn(xen_start_info->store_mfn);
	xen_start_info->console.domU.mfn =
		mfn_to_pfn(xen_start_info->console.domU.mfn);

	BUG_ON(!irqs_disabled());

	HYPERVISOR_shared_info = &xen_dummy_shared_info;
	if (HYPERVISOR_update_va_mapping(fix_to_virt(FIX_PARAVIRT_BOOTMAP),
					 __pte_ma(0), 0))
		BUG();
}