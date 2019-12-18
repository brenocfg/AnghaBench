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
typedef  int /*<<< orphan*/  u64 ;
struct gntdev_grant_map {int flags; unsigned int count; int /*<<< orphan*/ * unmap_ops; TYPE_2__* grants; int /*<<< orphan*/ * map_ops; TYPE_1__* vma; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_6__ {int /*<<< orphan*/  maddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  domid; int /*<<< orphan*/  ref; } ;
struct TYPE_4__ {unsigned long vm_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int GNTMAP_application_map ; 
 int GNTMAP_contains_pte ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  XENFEAT_gnttab_map_avail_bits ; 
 int _GNTMAP_guest_avail0 ; 
 TYPE_3__ arbitrary_virt_to_machine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_set_map_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnttab_set_unmap_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ xen_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_grant_ptes(pte_t *pte, unsigned long addr, void *data)
{
	struct gntdev_grant_map *map = data;
	unsigned int pgnr = (addr - map->vma->vm_start) >> PAGE_SHIFT;
	int flags = map->flags | GNTMAP_application_map | GNTMAP_contains_pte;
	u64 pte_maddr;

	BUG_ON(pgnr >= map->count);
	pte_maddr = arbitrary_virt_to_machine(pte).maddr;

	/*
	 * Set the PTE as special to force get_user_pages_fast() fall
	 * back to the slow path.  If this is not supported as part of
	 * the grant map, it will be done afterwards.
	 */
	if (xen_feature(XENFEAT_gnttab_map_avail_bits))
		flags |= (1 << _GNTMAP_guest_avail0);

	gnttab_set_map_op(&map->map_ops[pgnr], pte_maddr, flags,
			  map->grants[pgnr].ref,
			  map->grants[pgnr].domid);
	gnttab_set_unmap_op(&map->unmap_ops[pgnr], pte_maddr, flags,
			    -1 /* handle */);
	return 0;
}