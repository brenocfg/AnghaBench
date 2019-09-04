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
struct xen_add_to_physmap {int /*<<< orphan*/  gpfn; int /*<<< orphan*/  space; scalar_t__ idx; int /*<<< orphan*/  domid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DOMID_SELF ; 
 scalar_t__ HYPERVISOR_memory_op (int /*<<< orphan*/ ,struct xen_add_to_physmap*) ; 
 int /*<<< orphan*/  XENMAPSPACE_shared_info ; 
 int /*<<< orphan*/  XENMEM_add_to_physmap ; 
 int /*<<< orphan*/  shared_info_pfn ; 

void xen_hvm_init_shared_info(void)
{
	struct xen_add_to_physmap xatp;

	xatp.domid = DOMID_SELF;
	xatp.idx = 0;
	xatp.space = XENMAPSPACE_shared_info;
	xatp.gpfn = shared_info_pfn;
	if (HYPERVISOR_memory_op(XENMEM_add_to_physmap, &xatp))
		BUG();
}