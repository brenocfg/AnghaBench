#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ttm_mem_type_manager {int flags; } ;
struct TYPE_2__ {int size; int is_iomem; scalar_t__ base; scalar_t__ offset; int /*<<< orphan*/ * addr; } ;
struct ttm_mem_reg {size_t mem_type; int num_pages; TYPE_1__ bus; } ;
struct ttm_bo_device {struct ttm_mem_type_manager* man; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SHIFT ; 
 int TTM_MEMTYPE_FLAG_MAPPABLE ; 
#define  TTM_PL_SYSTEM 129 
#define  TTM_PL_TT 128 

__attribute__((used)) static int virtio_gpu_ttm_io_mem_reserve(struct ttm_bo_device *bdev,
					 struct ttm_mem_reg *mem)
{
	struct ttm_mem_type_manager *man = &bdev->man[mem->mem_type];

	mem->bus.addr = NULL;
	mem->bus.offset = 0;
	mem->bus.size = mem->num_pages << PAGE_SHIFT;
	mem->bus.base = 0;
	mem->bus.is_iomem = false;
	if (!(man->flags & TTM_MEMTYPE_FLAG_MAPPABLE))
		return -EINVAL;
	switch (mem->mem_type) {
	case TTM_PL_SYSTEM:
	case TTM_PL_TT:
		/* system memory */
		return 0;
	default:
		return -EINVAL;
	}
	return 0;
}