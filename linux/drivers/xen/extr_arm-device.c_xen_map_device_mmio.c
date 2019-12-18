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
typedef  int xen_ulong_t ;
typedef  int xen_pfn_t ;
struct xen_add_to_physmap_range {unsigned int size; int /*<<< orphan*/  errs; int /*<<< orphan*/  idxs; int /*<<< orphan*/  gpfns; int /*<<< orphan*/  space; int /*<<< orphan*/  domid; } ;
struct resource {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DOMID_SELF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HYPERVISOR_memory_op (int /*<<< orphan*/ ,struct xen_add_to_physmap_range*) ; 
 scalar_t__ IORESOURCE_MEM ; 
 int /*<<< orphan*/  XENMAPSPACE_dev_mmio ; 
 int /*<<< orphan*/  XENMEM_add_to_physmap_range ; 
 int /*<<< orphan*/  XEN_PAGE_SIZE ; 
 int XEN_PFN_DOWN (int /*<<< orphan*/ ) ; 
 int* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int /*<<< orphan*/  resource_size (struct resource const*) ; 
 scalar_t__ resource_type (struct resource const*) ; 
 int /*<<< orphan*/  set_xen_guest_handle (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xen_unmap_device_mmio (struct resource const*,unsigned int) ; 

__attribute__((used)) static int xen_map_device_mmio(const struct resource *resources,
			       unsigned int count)
{
	unsigned int i, j, nr;
	int rc = 0;
	const struct resource *r;
	xen_pfn_t *gpfns;
	xen_ulong_t *idxs;
	int *errs;

	for (i = 0; i < count; i++) {
		struct xen_add_to_physmap_range xatp = {
			.domid = DOMID_SELF,
			.space = XENMAPSPACE_dev_mmio
		};

		r = &resources[i];
		nr = DIV_ROUND_UP(resource_size(r), XEN_PAGE_SIZE);
		if ((resource_type(r) != IORESOURCE_MEM) || (nr == 0))
			continue;

		gpfns = kcalloc(nr, sizeof(xen_pfn_t), GFP_KERNEL);
		idxs = kcalloc(nr, sizeof(xen_ulong_t), GFP_KERNEL);
		errs = kcalloc(nr, sizeof(int), GFP_KERNEL);
		if (!gpfns || !idxs || !errs) {
			kfree(gpfns);
			kfree(idxs);
			kfree(errs);
			rc = -ENOMEM;
			goto unmap;
		}

		for (j = 0; j < nr; j++) {
			/*
			 * The regions are always mapped 1:1 to DOM0 and this is
			 * fine because the memory map for DOM0 is the same as
			 * the host (except for the RAM).
			 */
			gpfns[j] = XEN_PFN_DOWN(r->start) + j;
			idxs[j] = XEN_PFN_DOWN(r->start) + j;
		}

		xatp.size = nr;

		set_xen_guest_handle(xatp.gpfns, gpfns);
		set_xen_guest_handle(xatp.idxs, idxs);
		set_xen_guest_handle(xatp.errs, errs);

		rc = HYPERVISOR_memory_op(XENMEM_add_to_physmap_range, &xatp);
		kfree(gpfns);
		kfree(idxs);
		kfree(errs);
		if (rc)
			goto unmap;
	}

	return rc;

unmap:
	xen_unmap_device_mmio(resources, i);
	return rc;
}