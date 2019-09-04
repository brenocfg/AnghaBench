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
struct virtio_gpu_object {int dumb; int /*<<< orphan*/  placement; int /*<<< orphan*/  tbo; int /*<<< orphan*/  gem_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;
struct virtio_gpu_device {TYPE_1__ mman; int /*<<< orphan*/  ddev; } ;
typedef  enum ttm_bo_type { ____Placeholder_ttm_bo_type } ttm_bo_type ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int drm_gem_object_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  kfree (struct virtio_gpu_object*) ; 
 struct virtio_gpu_object* kzalloc (int,int /*<<< orphan*/ ) ; 
 unsigned long roundup (unsigned long,int /*<<< orphan*/ ) ; 
 size_t ttm_bo_dma_acc_size (int /*<<< orphan*/ *,unsigned long,int) ; 
 int ttm_bo_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ttm_bo_type_device ; 
 int ttm_bo_type_kernel ; 
 int /*<<< orphan*/  virtio_gpu_init_ttm_placement (struct virtio_gpu_object*,int) ; 
 int /*<<< orphan*/  virtio_gpu_ttm_bo_destroy ; 

int virtio_gpu_object_create(struct virtio_gpu_device *vgdev,
			     unsigned long size, bool kernel, bool pinned,
			     struct virtio_gpu_object **bo_ptr)
{
	struct virtio_gpu_object *bo;
	enum ttm_bo_type type;
	size_t acc_size;
	int ret;

	if (kernel)
		type = ttm_bo_type_kernel;
	else
		type = ttm_bo_type_device;
	*bo_ptr = NULL;

	acc_size = ttm_bo_dma_acc_size(&vgdev->mman.bdev, size,
				       sizeof(struct virtio_gpu_object));

	bo = kzalloc(sizeof(struct virtio_gpu_object), GFP_KERNEL);
	if (bo == NULL)
		return -ENOMEM;
	size = roundup(size, PAGE_SIZE);
	ret = drm_gem_object_init(vgdev->ddev, &bo->gem_base, size);
	if (ret != 0) {
		kfree(bo);
		return ret;
	}
	bo->dumb = false;
	virtio_gpu_init_ttm_placement(bo, pinned);

	ret = ttm_bo_init(&vgdev->mman.bdev, &bo->tbo, size, type,
			  &bo->placement, 0, !kernel, acc_size,
			  NULL, NULL, &virtio_gpu_ttm_bo_destroy);
	/* ttm_bo_init failure will call the destroy */
	if (ret != 0)
		return ret;

	*bo_ptr = bo;
	return 0;
}