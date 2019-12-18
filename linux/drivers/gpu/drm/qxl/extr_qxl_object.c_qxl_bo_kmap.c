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
struct TYPE_2__ {int /*<<< orphan*/  num_pages; } ;
struct qxl_bo {int map_count; void* kptr; int /*<<< orphan*/  kmap; TYPE_1__ tbo; } ;

/* Variables and functions */
 int ttm_bo_kmap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* ttm_kmap_obj_virtual (int /*<<< orphan*/ *,int*) ; 

int qxl_bo_kmap(struct qxl_bo *bo, void **ptr)
{
	bool is_iomem;
	int r;

	if (bo->kptr) {
		if (ptr)
			*ptr = bo->kptr;
		bo->map_count++;
		return 0;
	}
	r = ttm_bo_kmap(&bo->tbo, 0, bo->tbo.num_pages, &bo->kmap);
	if (r)
		return r;
	bo->kptr = ttm_kmap_obj_virtual(&bo->kmap, &is_iomem);
	if (ptr)
		*ptr = bo->kptr;
	bo->map_count = 1;
	return 0;
}