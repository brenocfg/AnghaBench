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
struct gnttab_dma_alloc_args {int coherent; int /*<<< orphan*/  dev_bus_addr; scalar_t__ vaddr; struct gntdev_grant_map* frames; struct gntdev_grant_map* pages; int /*<<< orphan*/  nr_pages; int /*<<< orphan*/  dev; } ;
struct gntdev_grant_map {int dma_flags; struct gntdev_grant_map* kunmap_ops; struct gntdev_grant_map* kmap_ops; struct gntdev_grant_map* unmap_ops; struct gntdev_grant_map* map_ops; struct gntdev_grant_map* grants; struct gntdev_grant_map* pages; struct gntdev_grant_map* frames; int /*<<< orphan*/  count; int /*<<< orphan*/  dma_bus_addr; scalar_t__ dma_vaddr; int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
 int GNTDEV_DMA_FLAG_COHERENT ; 
 int /*<<< orphan*/  gnttab_dma_free_pages (struct gnttab_dma_alloc_args*) ; 
 int /*<<< orphan*/  gnttab_free_pages (int /*<<< orphan*/ ,struct gntdev_grant_map*) ; 
 int /*<<< orphan*/  kfree (struct gntdev_grant_map*) ; 

__attribute__((used)) static void gntdev_free_map(struct gntdev_grant_map *map)
{
	if (map == NULL)
		return;

#ifdef CONFIG_XEN_GRANT_DMA_ALLOC
	if (map->dma_vaddr) {
		struct gnttab_dma_alloc_args args;

		args.dev = map->dma_dev;
		args.coherent = !!(map->dma_flags & GNTDEV_DMA_FLAG_COHERENT);
		args.nr_pages = map->count;
		args.pages = map->pages;
		args.frames = map->frames;
		args.vaddr = map->dma_vaddr;
		args.dev_bus_addr = map->dma_bus_addr;

		gnttab_dma_free_pages(&args);
	} else
#endif
	if (map->pages)
		gnttab_free_pages(map->count, map->pages);

#ifdef CONFIG_XEN_GRANT_DMA_ALLOC
	kfree(map->frames);
#endif
	kfree(map->pages);
	kfree(map->grants);
	kfree(map->map_ops);
	kfree(map->unmap_ops);
	kfree(map->kmap_ops);
	kfree(map->kunmap_ops);
	kfree(map);
}