#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  resv; } ;
struct ttm_buffer_object {int type; int /*<<< orphan*/ * ttm; TYPE_2__ base; struct ttm_bo_device* bdev; } ;
struct ttm_bo_device {TYPE_1__* driver; scalar_t__ no_retry; scalar_t__ need_dma32; } ;
struct TYPE_3__ {int /*<<< orphan*/ * (* ttm_tt_create ) (struct ttm_buffer_object*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TTM_PAGE_FLAG_DMA32 ; 
 int /*<<< orphan*/  TTM_PAGE_FLAG_NO_RETRY ; 
 int /*<<< orphan*/  TTM_PAGE_FLAG_SG ; 
 int /*<<< orphan*/  TTM_PAGE_FLAG_ZERO_ALLOC ; 
 int /*<<< orphan*/  dma_resv_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/ * stub1 (struct ttm_buffer_object*,int /*<<< orphan*/ ) ; 
#define  ttm_bo_type_device 130 
#define  ttm_bo_type_kernel 129 
#define  ttm_bo_type_sg 128 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int ttm_tt_create(struct ttm_buffer_object *bo, bool zero_alloc)
{
	struct ttm_bo_device *bdev = bo->bdev;
	uint32_t page_flags = 0;

	dma_resv_assert_held(bo->base.resv);

	if (bdev->need_dma32)
		page_flags |= TTM_PAGE_FLAG_DMA32;

	if (bdev->no_retry)
		page_flags |= TTM_PAGE_FLAG_NO_RETRY;

	switch (bo->type) {
	case ttm_bo_type_device:
		if (zero_alloc)
			page_flags |= TTM_PAGE_FLAG_ZERO_ALLOC;
		break;
	case ttm_bo_type_kernel:
		break;
	case ttm_bo_type_sg:
		page_flags |= TTM_PAGE_FLAG_SG;
		break;
	default:
		bo->ttm = NULL;
		pr_err("Illegal buffer object type\n");
		return -EINVAL;
	}

	bo->ttm = bdev->driver->ttm_tt_create(bo, page_flags);
	if (unlikely(bo->ttm == NULL))
		return -ENOMEM;

	return 0;
}