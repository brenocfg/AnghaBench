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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  nents; int /*<<< orphan*/ * sgl; } ;
struct aio_cb_data {unsigned int page_count; scalar_t__ cpl; int /*<<< orphan*/  flags; struct aio_cb_data* user_pages; TYPE_3__ sgt; TYPE_2__* ldev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dir; TYPE_1__* pldev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageReserved (struct aio_cb_data) ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct aio_cb_data*) ; 
 int /*<<< orphan*/  put_page (struct aio_cb_data) ; 
 int /*<<< orphan*/  set_page_dirty (struct aio_cb_data) ; 
 int /*<<< orphan*/  sg_free_table (TYPE_3__*) ; 

void  transfer_complete_cb(struct aio_cb_data *acd, size_t xfr_count, u32 flags)
{
	unsigned int i;

	BUG_ON(acd == NULL);
	BUG_ON(acd->user_pages == NULL);
	BUG_ON(acd->sgt.sgl == NULL);
	BUG_ON(acd->ldev == NULL);
	BUG_ON(acd->ldev->pldev == NULL);

	for (i = 0 ; i < acd->page_count ; i++) {
		if (!PageReserved(acd->user_pages[i])) {
			set_page_dirty(acd->user_pages[i]);
		}
	}

	dma_unmap_sg(&acd->ldev->pldev->dev, acd->sgt.sgl, acd->sgt.nents, acd->ldev->dir);

	for (i = 0 ; i < acd->page_count ; i++) {
		put_page(acd->user_pages[i]);
	}

	sg_free_table(&acd->sgt);

	kfree(acd->user_pages);

	acd->flags = flags;

	if (acd->cpl) {
		complete(acd->cpl);
	} else {
		/*
		 * There's no completion, so we're responsible for cleaning up
		 * the acd
		 */
		kfree(acd);
	}
}