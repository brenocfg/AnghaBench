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
struct vsp1_dl_entry {int dummy; } ;
struct vsp1_dl_body_pool {size_t size; unsigned int max_entries; int /*<<< orphan*/  free; scalar_t__ mem; scalar_t__ entries; scalar_t__ dma; struct vsp1_dl_body_pool* pool; struct vsp1_dl_body_pool* bodies; int /*<<< orphan*/  lock; struct vsp1_device* vsp1; } ;
struct vsp1_dl_body {size_t size; unsigned int max_entries; int /*<<< orphan*/  free; scalar_t__ mem; scalar_t__ entries; scalar_t__ dma; struct vsp1_dl_body* pool; struct vsp1_dl_body* bodies; int /*<<< orphan*/  lock; struct vsp1_device* vsp1; } ;
struct vsp1_device {int /*<<< orphan*/  bus_master; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ dma_alloc_wc (int /*<<< orphan*/ ,size_t,scalar_t__*,int /*<<< orphan*/ ) ; 
 struct vsp1_dl_body_pool* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vsp1_dl_body_pool*) ; 
 struct vsp1_dl_body_pool* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct vsp1_dl_body_pool *
vsp1_dl_body_pool_create(struct vsp1_device *vsp1, unsigned int num_bodies,
			 unsigned int num_entries, size_t extra_size)
{
	struct vsp1_dl_body_pool *pool;
	size_t dlb_size;
	unsigned int i;

	pool = kzalloc(sizeof(*pool), GFP_KERNEL);
	if (!pool)
		return NULL;

	pool->vsp1 = vsp1;

	/*
	 * TODO: 'extra_size' is only used by vsp1_dlm_create(), to allocate
	 * extra memory for the display list header. We need only one header per
	 * display list, not per display list body, thus this allocation is
	 * extraneous and should be reworked in the future.
	 */
	dlb_size = num_entries * sizeof(struct vsp1_dl_entry) + extra_size;
	pool->size = dlb_size * num_bodies;

	pool->bodies = kcalloc(num_bodies, sizeof(*pool->bodies), GFP_KERNEL);
	if (!pool->bodies) {
		kfree(pool);
		return NULL;
	}

	pool->mem = dma_alloc_wc(vsp1->bus_master, pool->size, &pool->dma,
				 GFP_KERNEL);
	if (!pool->mem) {
		kfree(pool->bodies);
		kfree(pool);
		return NULL;
	}

	spin_lock_init(&pool->lock);
	INIT_LIST_HEAD(&pool->free);

	for (i = 0; i < num_bodies; ++i) {
		struct vsp1_dl_body *dlb = &pool->bodies[i];

		dlb->pool = pool;
		dlb->max_entries = num_entries;

		dlb->dma = pool->dma + i * dlb_size;
		dlb->entries = pool->mem + i * dlb_size;

		list_add_tail(&dlb->free, &pool->free);
	}

	return pool;
}