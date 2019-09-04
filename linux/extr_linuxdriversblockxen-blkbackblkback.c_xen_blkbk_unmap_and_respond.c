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
struct xen_blkif_ring {int dummy; } ;
struct gntab_unmap_queue_data {unsigned int count; int /*<<< orphan*/  pages; int /*<<< orphan*/ * kunmap_ops; int /*<<< orphan*/  unmap_ops; int /*<<< orphan*/  done; struct pending_req* data; } ;
struct pending_req {struct gntab_unmap_queue_data gnttab_unmap_data; int /*<<< orphan*/  unmap_pages; int /*<<< orphan*/  unmap; int /*<<< orphan*/  nr_segs; struct grant_page** segments; struct xen_blkif_ring* ring; } ;
struct grant_page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gnttab_unmap_refs_async (struct gntab_unmap_queue_data*) ; 
 int /*<<< orphan*/  xen_blkbk_unmap_and_respond_callback ; 
 unsigned int xen_blkbk_unmap_prepare (struct xen_blkif_ring*,struct grant_page**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xen_blkbk_unmap_and_respond(struct pending_req *req)
{
	struct gntab_unmap_queue_data* work = &req->gnttab_unmap_data;
	struct xen_blkif_ring *ring = req->ring;
	struct grant_page **pages = req->segments;
	unsigned int invcount;

	invcount = xen_blkbk_unmap_prepare(ring, pages, req->nr_segs,
					   req->unmap, req->unmap_pages);

	work->data = req;
	work->done = xen_blkbk_unmap_and_respond_callback;
	work->unmap_ops = req->unmap;
	work->kunmap_ops = NULL;
	work->pages = req->unmap_pages;
	work->count = invcount;

	gnttab_unmap_refs_async(&req->gnttab_unmap_data);
}