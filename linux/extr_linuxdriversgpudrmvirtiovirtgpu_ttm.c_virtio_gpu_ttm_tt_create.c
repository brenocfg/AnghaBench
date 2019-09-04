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
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_tt {int /*<<< orphan*/ * func; } ;
struct TYPE_2__ {struct ttm_tt ttm; } ;
struct virtio_gpu_ttm_tt {TYPE_1__ ttm; struct virtio_gpu_device* vgdev; } ;
struct virtio_gpu_device {int dummy; } ;
struct ttm_buffer_object {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct virtio_gpu_ttm_tt*) ; 
 struct virtio_gpu_ttm_tt* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ttm_dma_tt_init (TYPE_1__*,struct ttm_buffer_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_gpu_backend_func ; 
 struct virtio_gpu_device* virtio_gpu_get_vgdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ttm_tt *virtio_gpu_ttm_tt_create(struct ttm_buffer_object *bo,
					       uint32_t page_flags)
{
	struct virtio_gpu_device *vgdev;
	struct virtio_gpu_ttm_tt *gtt;

	vgdev = virtio_gpu_get_vgdev(bo->bdev);
	gtt = kzalloc(sizeof(struct virtio_gpu_ttm_tt), GFP_KERNEL);
	if (gtt == NULL)
		return NULL;
	gtt->ttm.ttm.func = &virtio_gpu_backend_func;
	gtt->vgdev = vgdev;
	if (ttm_dma_tt_init(&gtt->ttm, bo, page_flags)) {
		kfree(gtt);
		return NULL;
	}
	return &gtt->ttm.ttm;
}