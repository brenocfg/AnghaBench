#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct gntdev_grant_map {int count; int flags; TYPE_2__* unmap_ops; int /*<<< orphan*/ * pages; scalar_t__ dma_vaddr; TYPE_3__* kmap_ops; TYPE_2__* kunmap_ops; TYPE_3__* map_ops; int /*<<< orphan*/  index; TYPE_1__* grants; } ;
struct TYPE_8__ {int handle; scalar_t__ status; } ;
struct TYPE_7__ {int handle; int /*<<< orphan*/  dev_bus_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  domid; int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int GNTMAP_host_map ; 
 int /*<<< orphan*/  PageHighMem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pfn_to_phys (unsigned long) ; 
 int gnttab_map_refs (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gnttab_set_map_op (TYPE_3__*,unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnttab_set_unmap_op (TYPE_2__*,unsigned long,int,int) ; 
 int /*<<< orphan*/  page_to_pfn (int /*<<< orphan*/ ) ; 
 unsigned long pfn_to_bfn (int /*<<< orphan*/ ) ; 
 scalar_t__ pfn_to_kaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ use_ptemod ; 

int gntdev_map_grant_pages(struct gntdev_grant_map *map)
{
	int i, err = 0;

	if (!use_ptemod) {
		/* Note: it could already be mapped */
		if (map->map_ops[0].handle != -1)
			return 0;
		for (i = 0; i < map->count; i++) {
			unsigned long addr = (unsigned long)
				pfn_to_kaddr(page_to_pfn(map->pages[i]));
			gnttab_set_map_op(&map->map_ops[i], addr, map->flags,
				map->grants[i].ref,
				map->grants[i].domid);
			gnttab_set_unmap_op(&map->unmap_ops[i], addr,
				map->flags, -1 /* handle */);
		}
	} else {
		/*
		 * Setup the map_ops corresponding to the pte entries pointing
		 * to the kernel linear addresses of the struct pages.
		 * These ptes are completely different from the user ptes dealt
		 * with find_grant_ptes.
		 */
		for (i = 0; i < map->count; i++) {
			unsigned long address = (unsigned long)
				pfn_to_kaddr(page_to_pfn(map->pages[i]));
			BUG_ON(PageHighMem(map->pages[i]));

			gnttab_set_map_op(&map->kmap_ops[i], address,
				map->flags | GNTMAP_host_map,
				map->grants[i].ref,
				map->grants[i].domid);
			gnttab_set_unmap_op(&map->kunmap_ops[i], address,
				map->flags | GNTMAP_host_map, -1);
		}
	}

	pr_debug("map %d+%d\n", map->index, map->count);
	err = gnttab_map_refs(map->map_ops, use_ptemod ? map->kmap_ops : NULL,
			map->pages, map->count);
	if (err)
		return err;

	for (i = 0; i < map->count; i++) {
		if (map->map_ops[i].status) {
			err = -EINVAL;
			continue;
		}

		map->unmap_ops[i].handle = map->map_ops[i].handle;
		if (use_ptemod)
			map->kunmap_ops[i].handle = map->kmap_ops[i].handle;
#ifdef CONFIG_XEN_GRANT_DMA_ALLOC
		else if (map->dma_vaddr) {
			unsigned long bfn;

			bfn = pfn_to_bfn(page_to_pfn(map->pages[i]));
			map->unmap_ops[i].dev_bus_addr = __pfn_to_phys(bfn);
		}
#endif
	}
	return err;
}