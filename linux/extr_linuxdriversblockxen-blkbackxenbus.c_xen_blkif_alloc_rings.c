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
struct xen_blkif_ring {int active; int /*<<< orphan*/  st_print; struct xen_blkif* blkif; int /*<<< orphan*/  shutdown_wq; int /*<<< orphan*/  pending_free_wq; int /*<<< orphan*/  pending_free_lock; int /*<<< orphan*/  free_pages; int /*<<< orphan*/  free_pages_lock; int /*<<< orphan*/  persistent_purge_work; int /*<<< orphan*/  persistent_purge_list; int /*<<< orphan*/  pending_free; int /*<<< orphan*/  wq; int /*<<< orphan*/  blk_ring_lock; } ;
struct xen_blkif {unsigned int nr_rings; struct xen_blkif_ring* rings; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 struct xen_blkif_ring* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_blkbk_unmap_purged_grants ; 

__attribute__((used)) static int xen_blkif_alloc_rings(struct xen_blkif *blkif)
{
	unsigned int r;

	blkif->rings = kcalloc(blkif->nr_rings, sizeof(struct xen_blkif_ring),
			       GFP_KERNEL);
	if (!blkif->rings)
		return -ENOMEM;

	for (r = 0; r < blkif->nr_rings; r++) {
		struct xen_blkif_ring *ring = &blkif->rings[r];

		spin_lock_init(&ring->blk_ring_lock);
		init_waitqueue_head(&ring->wq);
		INIT_LIST_HEAD(&ring->pending_free);
		INIT_LIST_HEAD(&ring->persistent_purge_list);
		INIT_WORK(&ring->persistent_purge_work, xen_blkbk_unmap_purged_grants);
		spin_lock_init(&ring->free_pages_lock);
		INIT_LIST_HEAD(&ring->free_pages);

		spin_lock_init(&ring->pending_free_lock);
		init_waitqueue_head(&ring->pending_free_wq);
		init_waitqueue_head(&ring->shutdown_wq);
		ring->blkif = blkif;
		ring->st_print = jiffies;
		ring->active = true;
	}

	return 0;
}