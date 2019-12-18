#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct gnttab_dma_alloc_args {int coherent; int nr_pages; int /*<<< orphan*/  dev_bus_addr; int /*<<< orphan*/  vaddr; void* frames; int /*<<< orphan*/ * pages; int /*<<< orphan*/  dev; } ;
struct gntdev_priv {int /*<<< orphan*/  dma_dev; } ;
struct gntdev_grant_map {int dma_flags; int count; int /*<<< orphan*/  users; scalar_t__ index; TYPE_4__* kunmap_ops; TYPE_3__* kmap_ops; TYPE_2__* unmap_ops; TYPE_1__* map_ops; int /*<<< orphan*/ * pages; int /*<<< orphan*/  dma_bus_addr; int /*<<< orphan*/  dma_vaddr; void* frames; int /*<<< orphan*/  dma_dev; int /*<<< orphan*/ * grants; } ;
struct TYPE_8__ {int handle; } ;
struct TYPE_7__ {int handle; } ;
struct TYPE_6__ {int handle; } ;
struct TYPE_5__ {int handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GNTDEV_DMA_FLAG_COHERENT ; 
 int GNTDEV_DMA_FLAG_WC ; 
 int /*<<< orphan*/  gntdev_free_map (struct gntdev_grant_map*) ; 
 scalar_t__ gnttab_alloc_pages (int,int /*<<< orphan*/ *) ; 
 scalar_t__ gnttab_dma_alloc_pages (struct gnttab_dma_alloc_args*) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct gntdev_grant_map* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

struct gntdev_grant_map *gntdev_alloc_map(struct gntdev_priv *priv, int count,
					  int dma_flags)
{
	struct gntdev_grant_map *add;
	int i;

	add = kzalloc(sizeof(*add), GFP_KERNEL);
	if (NULL == add)
		return NULL;

	add->grants    = kcalloc(count, sizeof(add->grants[0]), GFP_KERNEL);
	add->map_ops   = kcalloc(count, sizeof(add->map_ops[0]), GFP_KERNEL);
	add->unmap_ops = kcalloc(count, sizeof(add->unmap_ops[0]), GFP_KERNEL);
	add->kmap_ops  = kcalloc(count, sizeof(add->kmap_ops[0]), GFP_KERNEL);
	add->kunmap_ops = kcalloc(count, sizeof(add->kunmap_ops[0]), GFP_KERNEL);
	add->pages     = kcalloc(count, sizeof(add->pages[0]), GFP_KERNEL);
	if (NULL == add->grants    ||
	    NULL == add->map_ops   ||
	    NULL == add->unmap_ops ||
	    NULL == add->kmap_ops  ||
	    NULL == add->kunmap_ops ||
	    NULL == add->pages)
		goto err;

#ifdef CONFIG_XEN_GRANT_DMA_ALLOC
	add->dma_flags = dma_flags;

	/*
	 * Check if this mapping is requested to be backed
	 * by a DMA buffer.
	 */
	if (dma_flags & (GNTDEV_DMA_FLAG_WC | GNTDEV_DMA_FLAG_COHERENT)) {
		struct gnttab_dma_alloc_args args;

		add->frames = kcalloc(count, sizeof(add->frames[0]),
				      GFP_KERNEL);
		if (!add->frames)
			goto err;

		/* Remember the device, so we can free DMA memory. */
		add->dma_dev = priv->dma_dev;

		args.dev = priv->dma_dev;
		args.coherent = !!(dma_flags & GNTDEV_DMA_FLAG_COHERENT);
		args.nr_pages = count;
		args.pages = add->pages;
		args.frames = add->frames;

		if (gnttab_dma_alloc_pages(&args))
			goto err;

		add->dma_vaddr = args.vaddr;
		add->dma_bus_addr = args.dev_bus_addr;
	} else
#endif
	if (gnttab_alloc_pages(count, add->pages))
		goto err;

	for (i = 0; i < count; i++) {
		add->map_ops[i].handle = -1;
		add->unmap_ops[i].handle = -1;
		add->kmap_ops[i].handle = -1;
		add->kunmap_ops[i].handle = -1;
	}

	add->index = 0;
	add->count = count;
	refcount_set(&add->users, 1);

	return add;

err:
	gntdev_free_map(add);
	return NULL;
}