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
struct xen_blkif_ring {int /*<<< orphan*/  inflight; struct xen_blkif* blkif; } ;
struct xen_blkif {int /*<<< orphan*/  drain_complete; int /*<<< orphan*/  drain; } ;
struct pending_req {int /*<<< orphan*/  status; int /*<<< orphan*/  operation; int /*<<< orphan*/  id; struct xen_blkif_ring* ring; } ;
struct gntab_unmap_queue_data {int /*<<< orphan*/  count; int /*<<< orphan*/  pages; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_req (struct xen_blkif_ring*,struct pending_req*) ; 
 int /*<<< orphan*/  make_response (struct xen_blkif_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_free_pages (struct xen_blkif_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_blkif_put (struct xen_blkif*) ; 

__attribute__((used)) static void xen_blkbk_unmap_and_respond_callback(int result, struct gntab_unmap_queue_data *data)
{
	struct pending_req *pending_req = (struct pending_req *)(data->data);
	struct xen_blkif_ring *ring = pending_req->ring;
	struct xen_blkif *blkif = ring->blkif;

	/* BUG_ON used to reproduce existing behaviour,
	   but is this the best way to deal with this? */
	BUG_ON(result);

	put_free_pages(ring, data->pages, data->count);
	make_response(ring, pending_req->id,
		      pending_req->operation, pending_req->status);
	free_req(ring, pending_req);
	/*
	 * Make sure the request is freed before releasing blkif,
	 * or there could be a race between free_req and the
	 * cleanup done in xen_blkif_free during shutdown.
	 *
	 * NB: The fact that we might try to wake up pending_free_wq
	 * before drain_complete (in case there's a drain going on)
	 * it's not a problem with our current implementation
	 * because we can assure there's no thread waiting on
	 * pending_free_wq if there's a drain going on, but it has
	 * to be taken into account if the current model is changed.
	 */
	if (atomic_dec_and_test(&ring->inflight) && atomic_read(&blkif->drain)) {
		complete(&blkif->drain_complete);
	}
	xen_blkif_put(blkif);
}