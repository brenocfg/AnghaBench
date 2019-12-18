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
typedef  size_t u64 ;
struct TYPE_5__ {size_t start; size_t size; } ;
struct drm_gem_object {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct drm_gem_object base; } ;
struct panfrost_gem_object {int is_mapped; TYPE_2__ node; TYPE_3__* mmu; TYPE_1__ base; } ;
struct panfrost_device {int /*<<< orphan*/  dev; } ;
struct io_pgtable_ops {size_t (* unmap ) (struct io_pgtable_ops*,size_t,size_t,int /*<<< orphan*/ *) ;scalar_t__ (* iova_to_phys ) (struct io_pgtable_ops*,size_t) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  as; struct io_pgtable_ops* pgtbl_ops; } ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 size_t get_pgsize (size_t,size_t) ; 
 int /*<<< orphan*/  panfrost_mmu_flush_range (struct panfrost_device*,TYPE_3__*,size_t,size_t) ; 
 scalar_t__ stub1 (struct io_pgtable_ops*,size_t) ; 
 size_t stub2 (struct io_pgtable_ops*,size_t,size_t,int /*<<< orphan*/ *) ; 
 struct panfrost_device* to_panfrost_device (int /*<<< orphan*/ ) ; 

void panfrost_mmu_unmap(struct panfrost_gem_object *bo)
{
	struct drm_gem_object *obj = &bo->base.base;
	struct panfrost_device *pfdev = to_panfrost_device(obj->dev);
	struct io_pgtable_ops *ops = bo->mmu->pgtbl_ops;
	u64 iova = bo->node.start << PAGE_SHIFT;
	size_t len = bo->node.size << PAGE_SHIFT;
	size_t unmapped_len = 0;

	if (WARN_ON(!bo->is_mapped))
		return;

	dev_dbg(pfdev->dev, "unmap: as=%d, iova=%llx, len=%zx", bo->mmu->as, iova, len);

	while (unmapped_len < len) {
		size_t unmapped_page;
		size_t pgsize = get_pgsize(iova, len - unmapped_len);

		if (ops->iova_to_phys(ops, iova)) {
			unmapped_page = ops->unmap(ops, iova, pgsize, NULL);
			WARN_ON(unmapped_page != pgsize);
		}
		iova += pgsize;
		unmapped_len += pgsize;
	}

	panfrost_mmu_flush_range(pfdev, bo->mmu, bo->node.start << PAGE_SHIFT, len);
	bo->is_mapped = false;
}