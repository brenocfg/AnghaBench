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
struct vm_area_struct {struct ttm_buffer_object* vm_private_data; int /*<<< orphan*/  vm_start; } ;
struct TYPE_5__ {int mem_type; } ;
struct ttm_buffer_object {int num_pages; TYPE_3__* bdev; TYPE_4__* ttm; TYPE_1__ mem; } ;
typedef  unsigned long addr ;
struct TYPE_8__ {int page_flags; } ;
struct TYPE_7__ {TYPE_2__* driver; } ;
struct TYPE_6__ {int (* access_memory ) (struct ttm_buffer_object*,unsigned long,void*,int,int) ;} ;

/* Variables and functions */
 int EIO ; 
 unsigned long PAGE_SHIFT ; 
 int TTM_PAGE_FLAG_SWAPPED ; 
#define  TTM_PL_SYSTEM 129 
#define  TTM_PL_TT 128 
 int stub1 (struct ttm_buffer_object*,unsigned long,void*,int,int) ; 
 int ttm_bo_reserve (struct ttm_buffer_object*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (struct ttm_buffer_object*) ; 
 int ttm_bo_vm_access_kmap (struct ttm_buffer_object*,unsigned long,void*,int,int) ; 
 int ttm_tt_swapin (TYPE_4__*) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static int ttm_bo_vm_access(struct vm_area_struct *vma, unsigned long addr,
			    void *buf, int len, int write)
{
	unsigned long offset = (addr) - vma->vm_start;
	struct ttm_buffer_object *bo = vma->vm_private_data;
	int ret;

	if (len < 1 || (offset + len) >> PAGE_SHIFT > bo->num_pages)
		return -EIO;

	ret = ttm_bo_reserve(bo, true, false, NULL);
	if (ret)
		return ret;

	switch (bo->mem.mem_type) {
	case TTM_PL_SYSTEM:
		if (unlikely(bo->ttm->page_flags & TTM_PAGE_FLAG_SWAPPED)) {
			ret = ttm_tt_swapin(bo->ttm);
			if (unlikely(ret != 0))
				return ret;
		}
		/* fall through */
	case TTM_PL_TT:
		ret = ttm_bo_vm_access_kmap(bo, offset, buf, len, write);
		break;
	default:
		if (bo->bdev->driver->access_memory)
			ret = bo->bdev->driver->access_memory(
				bo, offset, buf, len, write);
		else
			ret = -EIO;
	}

	ttm_bo_unreserve(bo);

	return ret;
}