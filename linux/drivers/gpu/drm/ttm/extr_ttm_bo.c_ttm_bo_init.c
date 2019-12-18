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
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_placement {int dummy; } ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct ttm_buffer_object {int dummy; } ;
struct ttm_bo_device {int dummy; } ;
struct sg_table {int dummy; } ;
struct dma_resv {int dummy; } ;
typedef  enum ttm_bo_type { ____Placeholder_ttm_bo_type } ttm_bo_type ;

/* Variables and functions */
 int ttm_bo_init_reserved (struct ttm_bo_device*,struct ttm_buffer_object*,unsigned long,int,struct ttm_placement*,int /*<<< orphan*/ ,struct ttm_operation_ctx*,size_t,struct sg_table*,struct dma_resv*,void (*) (struct ttm_buffer_object*)) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (struct ttm_buffer_object*) ; 

int ttm_bo_init(struct ttm_bo_device *bdev,
		struct ttm_buffer_object *bo,
		unsigned long size,
		enum ttm_bo_type type,
		struct ttm_placement *placement,
		uint32_t page_alignment,
		bool interruptible,
		size_t acc_size,
		struct sg_table *sg,
		struct dma_resv *resv,
		void (*destroy) (struct ttm_buffer_object *))
{
	struct ttm_operation_ctx ctx = { interruptible, false };
	int ret;

	ret = ttm_bo_init_reserved(bdev, bo, size, type, placement,
				   page_alignment, &ctx, acc_size,
				   sg, resv, destroy);
	if (ret)
		return ret;

	if (!resv)
		ttm_bo_unreserve(bo);

	return 0;
}