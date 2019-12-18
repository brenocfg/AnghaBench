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
struct ww_acquire_ctx {int dummy; } ;
struct virtio_gpu_object_params {int /*<<< orphan*/  size; scalar_t__ virgl; int /*<<< orphan*/  dumb; } ;
struct virtio_gpu_object {int /*<<< orphan*/  tbo; int /*<<< orphan*/  gem_base; int /*<<< orphan*/  placement; int /*<<< orphan*/  dumb; int /*<<< orphan*/  hw_res_handle; } ;
struct virtio_gpu_fence_driver {int /*<<< orphan*/  lock; } ;
struct virtio_gpu_fence {int /*<<< orphan*/  f; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;
struct virtio_gpu_device {struct virtio_gpu_fence_driver fence_drv; TYPE_1__ mman; int /*<<< orphan*/  ddev; } ;
struct ttm_validate_buffer {int /*<<< orphan*/  head; int /*<<< orphan*/ * bo; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  drm_gem_object_get (int /*<<< orphan*/ *) ; 
 int drm_gem_object_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct virtio_gpu_object*) ; 
 struct virtio_gpu_object* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  memset (struct ttm_validate_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 size_t ttm_bo_dma_acc_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ttm_bo_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_type_device ; 
 int /*<<< orphan*/  ttm_eu_backoff_reservation (struct ww_acquire_ctx*,struct list_head*) ; 
 int /*<<< orphan*/  ttm_eu_fence_buffer_objects (struct ww_acquire_ctx*,struct list_head*,int /*<<< orphan*/ *) ; 
 int virtio_fence_signaled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_gpu_cmd_create_resource (struct virtio_gpu_device*,struct virtio_gpu_object*,struct virtio_gpu_object_params*,struct virtio_gpu_fence*) ; 
 int /*<<< orphan*/  virtio_gpu_cmd_resource_create_3d (struct virtio_gpu_device*,struct virtio_gpu_object*,struct virtio_gpu_object_params*,struct virtio_gpu_fence*) ; 
 int /*<<< orphan*/  virtio_gpu_init_ttm_placement (struct virtio_gpu_object*) ; 
 int virtio_gpu_object_list_validate (struct ww_acquire_ctx*,struct list_head*) ; 
 int virtio_gpu_resource_id_get (struct virtio_gpu_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_gpu_resource_id_put (struct virtio_gpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_gpu_ttm_bo_destroy ; 
 int /*<<< orphan*/  virtio_gpu_unref_list (struct list_head*) ; 

int virtio_gpu_object_create(struct virtio_gpu_device *vgdev,
			     struct virtio_gpu_object_params *params,
			     struct virtio_gpu_object **bo_ptr,
			     struct virtio_gpu_fence *fence)
{
	struct virtio_gpu_object *bo;
	size_t acc_size;
	int ret;

	*bo_ptr = NULL;

	acc_size = ttm_bo_dma_acc_size(&vgdev->mman.bdev, params->size,
				       sizeof(struct virtio_gpu_object));

	bo = kzalloc(sizeof(struct virtio_gpu_object), GFP_KERNEL);
	if (bo == NULL)
		return -ENOMEM;
	ret = virtio_gpu_resource_id_get(vgdev, &bo->hw_res_handle);
	if (ret < 0) {
		kfree(bo);
		return ret;
	}
	params->size = roundup(params->size, PAGE_SIZE);
	ret = drm_gem_object_init(vgdev->ddev, &bo->gem_base, params->size);
	if (ret != 0) {
		virtio_gpu_resource_id_put(vgdev, bo->hw_res_handle);
		kfree(bo);
		return ret;
	}
	bo->dumb = params->dumb;

	if (params->virgl) {
		virtio_gpu_cmd_resource_create_3d(vgdev, bo, params, fence);
	} else {
		virtio_gpu_cmd_create_resource(vgdev, bo, params, fence);
	}

	virtio_gpu_init_ttm_placement(bo);
	ret = ttm_bo_init(&vgdev->mman.bdev, &bo->tbo, params->size,
			  ttm_bo_type_device, &bo->placement, 0,
			  true, acc_size, NULL, NULL,
			  &virtio_gpu_ttm_bo_destroy);
	/* ttm_bo_init failure will call the destroy */
	if (ret != 0)
		return ret;

	if (fence) {
		struct virtio_gpu_fence_driver *drv = &vgdev->fence_drv;
		struct list_head validate_list;
		struct ttm_validate_buffer mainbuf;
		struct ww_acquire_ctx ticket;
		unsigned long irq_flags;
		bool signaled;

		INIT_LIST_HEAD(&validate_list);
		memset(&mainbuf, 0, sizeof(struct ttm_validate_buffer));

		/* use a gem reference since unref list undoes them */
		drm_gem_object_get(&bo->gem_base);
		mainbuf.bo = &bo->tbo;
		list_add(&mainbuf.head, &validate_list);

		ret = virtio_gpu_object_list_validate(&ticket, &validate_list);
		if (ret == 0) {
			spin_lock_irqsave(&drv->lock, irq_flags);
			signaled = virtio_fence_signaled(&fence->f);
			if (!signaled)
				/* virtio create command still in flight */
				ttm_eu_fence_buffer_objects(&ticket, &validate_list,
							    &fence->f);
			spin_unlock_irqrestore(&drv->lock, irq_flags);
			if (signaled)
				/* virtio create command finished */
				ttm_eu_backoff_reservation(&ticket, &validate_list);
		}
		virtio_gpu_unref_list(&validate_list);
	}

	*bo_ptr = bo;
	return 0;
}