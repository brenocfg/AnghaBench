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
struct TYPE_2__ {int /*<<< orphan*/  vma_node; } ;
struct ttm_buffer_object {TYPE_1__ base; struct ttm_bo_device* bdev; } ;
struct ttm_bo_device {int /*<<< orphan*/  dev_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_vma_node_unmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_mem_io_free_vm (struct ttm_buffer_object*) ; 

void ttm_bo_unmap_virtual_locked(struct ttm_buffer_object *bo)
{
	struct ttm_bo_device *bdev = bo->bdev;

	drm_vma_node_unmap(&bo->base.vma_node, bdev->dev_mapping);
	ttm_mem_io_free_vm(bo);
}