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
struct TYPE_7__ {int num_pages; TYPE_4__* ttm; } ;
struct virtio_gpu_object {int /*<<< orphan*/ * pages; TYPE_3__ tbo; } ;
struct virtio_gpu_device {int /*<<< orphan*/  vdev; } ;
struct ttm_operation_ctx {int interruptible; int no_wait_gpu; } ;
struct sg_table {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_8__ {scalar_t__ state; TYPE_2__* bdev; struct page** pages; } ;
struct TYPE_6__ {TYPE_1__* driver; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* ttm_tt_populate ) (TYPE_4__*,struct ttm_operation_ctx*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PAGE_MASK ; 
 int PAGE_SHIFT ; 
 size_t SCATTERLIST_MAX_SEGMENT ; 
 int __sg_alloc_table_from_pages (int /*<<< orphan*/ *,struct page**,int,int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,struct ttm_operation_ctx*) ; 
 scalar_t__ tt_unpopulated ; 
 size_t virtio_max_dma_size (int /*<<< orphan*/ ) ; 

int virtio_gpu_object_get_sg_table(struct virtio_gpu_device *qdev,
				   struct virtio_gpu_object *bo)
{
	int ret;
	struct page **pages = bo->tbo.ttm->pages;
	int nr_pages = bo->tbo.num_pages;
	struct ttm_operation_ctx ctx = {
		.interruptible = false,
		.no_wait_gpu = false
	};
	size_t max_segment;

	/* wtf swapping */
	if (bo->pages)
		return 0;

	if (bo->tbo.ttm->state == tt_unpopulated)
		bo->tbo.ttm->bdev->driver->ttm_tt_populate(bo->tbo.ttm, &ctx);
	bo->pages = kmalloc(sizeof(struct sg_table), GFP_KERNEL);
	if (!bo->pages)
		goto out;

	max_segment = virtio_max_dma_size(qdev->vdev);
	max_segment &= PAGE_MASK;
	if (max_segment > SCATTERLIST_MAX_SEGMENT)
		max_segment = SCATTERLIST_MAX_SEGMENT;
	ret = __sg_alloc_table_from_pages(bo->pages, pages, nr_pages, 0,
					  nr_pages << PAGE_SHIFT,
					  max_segment, GFP_KERNEL);
	if (ret)
		goto out;
	return 0;
out:
	kfree(bo->pages);
	bo->pages = NULL;
	return -ENOMEM;
}