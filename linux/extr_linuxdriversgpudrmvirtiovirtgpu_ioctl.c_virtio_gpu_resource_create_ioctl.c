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
typedef  scalar_t__ uint32_t ;
struct ww_acquire_ctx {int dummy; } ;
struct virtio_gpu_resource_create_3d {void* flags; void* nr_samples; void* last_level; void* array_size; void* depth; void* height; void* width; void* bind; void* format; void* target; void* resource_id; } ;
struct drm_gem_object {int dummy; } ;
struct virtio_gpu_object {scalar_t__ hw_res_handle; int /*<<< orphan*/  tbo; struct drm_gem_object gem_base; } ;
struct virtio_gpu_fence {int /*<<< orphan*/  f; } ;
struct virtio_gpu_device {int has_virgl_3d; } ;
struct ttm_validate_buffer {int /*<<< orphan*/  head; int /*<<< orphan*/ * bo; } ;
struct list_head {int dummy; } ;
struct drm_virtgpu_resource_create {int depth; int nr_samples; int last_level; int target; int array_size; scalar_t__ size; scalar_t__ format; scalar_t__ width; scalar_t__ height; scalar_t__ bind; scalar_t__ flags; scalar_t__ bo_handle; scalar_t__ res_handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct virtio_gpu_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 scalar_t__ IS_ERR (struct virtio_gpu_object*) ; 
 scalar_t__ PAGE_SIZE ; 
 int PTR_ERR (struct virtio_gpu_object*) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ *) ; 
 int drm_gem_handle_create (struct drm_file*,struct drm_gem_object*,scalar_t__*) ; 
 int /*<<< orphan*/  drm_gem_object_get (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_object_release (struct drm_gem_object*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  memset (struct ttm_validate_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ttm_eu_backoff_reservation (struct ww_acquire_ctx*,struct list_head*) ; 
 int /*<<< orphan*/  ttm_eu_fence_buffer_objects (struct ww_acquire_ctx*,struct list_head*,int /*<<< orphan*/ *) ; 
 struct virtio_gpu_object* virtio_gpu_alloc_object (struct drm_device*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  virtio_gpu_cmd_create_resource (struct virtio_gpu_device*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  virtio_gpu_cmd_resource_create_3d (struct virtio_gpu_device*,struct virtio_gpu_resource_create_3d*,int /*<<< orphan*/ *) ; 
 int virtio_gpu_object_attach (struct virtio_gpu_device*,struct virtio_gpu_object*,scalar_t__,struct virtio_gpu_fence**) ; 
 int virtio_gpu_object_list_validate (struct ww_acquire_ctx*,struct list_head*) ; 
 int /*<<< orphan*/  virtio_gpu_resource_id_get (struct virtio_gpu_device*,scalar_t__*) ; 
 int /*<<< orphan*/  virtio_gpu_resource_id_put (struct virtio_gpu_device*,scalar_t__) ; 
 int /*<<< orphan*/  virtio_gpu_unref_list (struct list_head*) ; 

__attribute__((used)) static int virtio_gpu_resource_create_ioctl(struct drm_device *dev, void *data,
					    struct drm_file *file_priv)
{
	struct virtio_gpu_device *vgdev = dev->dev_private;
	struct drm_virtgpu_resource_create *rc = data;
	int ret;
	uint32_t res_id;
	struct virtio_gpu_object *qobj;
	struct drm_gem_object *obj;
	uint32_t handle = 0;
	uint32_t size;
	struct list_head validate_list;
	struct ttm_validate_buffer mainbuf;
	struct virtio_gpu_fence *fence = NULL;
	struct ww_acquire_ctx ticket;
	struct virtio_gpu_resource_create_3d rc_3d;

	if (vgdev->has_virgl_3d == false) {
		if (rc->depth > 1)
			return -EINVAL;
		if (rc->nr_samples > 1)
			return -EINVAL;
		if (rc->last_level > 1)
			return -EINVAL;
		if (rc->target != 2)
			return -EINVAL;
		if (rc->array_size > 1)
			return -EINVAL;
	}

	INIT_LIST_HEAD(&validate_list);
	memset(&mainbuf, 0, sizeof(struct ttm_validate_buffer));

	virtio_gpu_resource_id_get(vgdev, &res_id);

	size = rc->size;

	/* allocate a single page size object */
	if (size == 0)
		size = PAGE_SIZE;

	qobj = virtio_gpu_alloc_object(dev, size, false, false);
	if (IS_ERR(qobj)) {
		ret = PTR_ERR(qobj);
		goto fail_id;
	}
	obj = &qobj->gem_base;

	if (!vgdev->has_virgl_3d) {
		virtio_gpu_cmd_create_resource(vgdev, res_id, rc->format,
					       rc->width, rc->height);

		ret = virtio_gpu_object_attach(vgdev, qobj, res_id, NULL);
	} else {
		/* use a gem reference since unref list undoes them */
		drm_gem_object_get(&qobj->gem_base);
		mainbuf.bo = &qobj->tbo;
		list_add(&mainbuf.head, &validate_list);

		ret = virtio_gpu_object_list_validate(&ticket, &validate_list);
		if (ret) {
			DRM_DEBUG("failed to validate\n");
			goto fail_unref;
		}

		rc_3d.resource_id = cpu_to_le32(res_id);
		rc_3d.target = cpu_to_le32(rc->target);
		rc_3d.format = cpu_to_le32(rc->format);
		rc_3d.bind = cpu_to_le32(rc->bind);
		rc_3d.width = cpu_to_le32(rc->width);
		rc_3d.height = cpu_to_le32(rc->height);
		rc_3d.depth = cpu_to_le32(rc->depth);
		rc_3d.array_size = cpu_to_le32(rc->array_size);
		rc_3d.last_level = cpu_to_le32(rc->last_level);
		rc_3d.nr_samples = cpu_to_le32(rc->nr_samples);
		rc_3d.flags = cpu_to_le32(rc->flags);

		virtio_gpu_cmd_resource_create_3d(vgdev, &rc_3d, NULL);
		ret = virtio_gpu_object_attach(vgdev, qobj, res_id, &fence);
		if (ret) {
			ttm_eu_backoff_reservation(&ticket, &validate_list);
			goto fail_unref;
		}
		ttm_eu_fence_buffer_objects(&ticket, &validate_list, &fence->f);
	}

	qobj->hw_res_handle = res_id;

	ret = drm_gem_handle_create(file_priv, obj, &handle);
	if (ret) {

		drm_gem_object_release(obj);
		if (vgdev->has_virgl_3d) {
			virtio_gpu_unref_list(&validate_list);
			dma_fence_put(&fence->f);
		}
		return ret;
	}
	drm_gem_object_put_unlocked(obj);

	rc->res_handle = res_id; /* similiar to a VM address */
	rc->bo_handle = handle;

	if (vgdev->has_virgl_3d) {
		virtio_gpu_unref_list(&validate_list);
		dma_fence_put(&fence->f);
	}
	return 0;
fail_unref:
	if (vgdev->has_virgl_3d) {
		virtio_gpu_unref_list(&validate_list);
		dma_fence_put(&fence->f);
	}
//fail_obj:
//	drm_gem_object_handle_unreference_unlocked(obj);
fail_id:
	virtio_gpu_resource_id_put(vgdev, res_id);
	return ret;
}