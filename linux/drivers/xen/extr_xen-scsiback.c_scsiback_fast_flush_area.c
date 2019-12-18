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
struct vscsibk_pend {unsigned int n_grants; scalar_t__* grant_handles; struct page** pages; scalar_t__ n_sg; int /*<<< orphan*/ * sgl; } ;
struct page {int dummy; } ;
struct gnttab_unmap_grant_ref {int dummy; } ;
typedef  scalar_t__ grant_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GNTMAP_host_map ; 
 scalar_t__ SCSIBACK_INVALID_HANDLE ; 
 int VSCSI_GRANT_BATCH ; 
 int /*<<< orphan*/  gnttab_set_unmap_op (struct gnttab_unmap_grant_ref*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int gnttab_unmap_refs (struct gnttab_unmap_grant_ref*,int /*<<< orphan*/ *,struct page**,unsigned int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_free_pages (struct page**,unsigned int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  vaddr (struct vscsibk_pend*,unsigned int) ; 

__attribute__((used)) static void scsiback_fast_flush_area(struct vscsibk_pend *req)
{
	struct gnttab_unmap_grant_ref unmap[VSCSI_GRANT_BATCH];
	struct page *pages[VSCSI_GRANT_BATCH];
	unsigned int i, invcount = 0;
	grant_handle_t handle;
	int err;

	kfree(req->sgl);
	req->sgl = NULL;
	req->n_sg = 0;

	if (!req->n_grants)
		return;

	for (i = 0; i < req->n_grants; i++) {
		handle = req->grant_handles[i];
		if (handle == SCSIBACK_INVALID_HANDLE)
			continue;
		gnttab_set_unmap_op(&unmap[invcount], vaddr(req, i),
				    GNTMAP_host_map, handle);
		req->grant_handles[i] = SCSIBACK_INVALID_HANDLE;
		pages[invcount] = req->pages[i];
		put_page(pages[invcount]);
		invcount++;
		if (invcount < VSCSI_GRANT_BATCH)
			continue;
		err = gnttab_unmap_refs(unmap, NULL, pages, invcount);
		BUG_ON(err);
		invcount = 0;
	}

	if (invcount) {
		err = gnttab_unmap_refs(unmap, NULL, pages, invcount);
		BUG_ON(err);
	}

	put_free_pages(req->pages, req->n_grants);
	req->n_grants = 0;
}