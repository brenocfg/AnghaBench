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
struct virtio_gpu_object {int /*<<< orphan*/  kmap; int /*<<< orphan*/  vmap; TYPE_1__ tbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int ttm_bo_kmap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_kmap_obj_virtual (int /*<<< orphan*/ *,int*) ; 

int virtio_gpu_object_kmap(struct virtio_gpu_object *bo)
{
	bool is_iomem;
	int r;

	WARN_ON(bo->vmap);

	r = ttm_bo_kmap(&bo->tbo, 0, bo->tbo.num_pages, &bo->kmap);
	if (r)
		return r;
	bo->vmap = ttm_kmap_obj_virtual(&bo->kmap, &is_iomem);
	return 0;
}