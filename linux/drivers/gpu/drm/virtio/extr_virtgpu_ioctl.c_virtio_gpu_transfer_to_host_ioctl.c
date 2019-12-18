#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  resv; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct virtio_gpu_object {TYPE_2__ tbo; int /*<<< orphan*/  placement; } ;
struct virtio_gpu_fpriv {int /*<<< orphan*/  ctx_id; } ;
struct virtio_gpu_fence {int /*<<< orphan*/  f; } ;
struct virtio_gpu_device {int /*<<< orphan*/  has_virgl_3d; } ;
struct virtio_gpu_box {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct drm_virtgpu_3d_transfer_to_host {int /*<<< orphan*/  level; int /*<<< orphan*/  box; int /*<<< orphan*/  bo_handle; int /*<<< orphan*/  offset; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {struct virtio_gpu_fpriv* driver_priv; } ;
struct drm_device {struct virtio_gpu_device* dev_private; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  convert_to_hw_box (struct virtio_gpu_box*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_resv_add_excl_fence (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct virtio_gpu_object* gem_to_virtio_gpu_obj (struct drm_gem_object*) ; 
 int ttm_bo_validate (TYPE_2__*,int /*<<< orphan*/ *,struct ttm_operation_ctx*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virtio_gpu_cmd_transfer_to_host_2d (struct virtio_gpu_device*,struct virtio_gpu_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_gpu_cmd_transfer_to_host_3d (struct virtio_gpu_device*,struct virtio_gpu_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct virtio_gpu_box*,struct virtio_gpu_fence*) ; 
 struct virtio_gpu_fence* virtio_gpu_fence_alloc (struct virtio_gpu_device*) ; 
 int virtio_gpu_object_reserve (struct virtio_gpu_object*,int) ; 
 int /*<<< orphan*/  virtio_gpu_object_unreserve (struct virtio_gpu_object*) ; 

__attribute__((used)) static int virtio_gpu_transfer_to_host_ioctl(struct drm_device *dev, void *data,
					     struct drm_file *file)
{
	struct virtio_gpu_device *vgdev = dev->dev_private;
	struct virtio_gpu_fpriv *vfpriv = file->driver_priv;
	struct drm_virtgpu_3d_transfer_to_host *args = data;
	struct ttm_operation_ctx ctx = { true, false };
	struct drm_gem_object *gobj = NULL;
	struct virtio_gpu_object *qobj = NULL;
	struct virtio_gpu_fence *fence;
	struct virtio_gpu_box box;
	int ret;
	u32 offset = args->offset;

	gobj = drm_gem_object_lookup(file, args->bo_handle);
	if (gobj == NULL)
		return -ENOENT;

	qobj = gem_to_virtio_gpu_obj(gobj);

	ret = virtio_gpu_object_reserve(qobj, false);
	if (ret)
		goto out;

	ret = ttm_bo_validate(&qobj->tbo, &qobj->placement, &ctx);
	if (unlikely(ret))
		goto out_unres;

	convert_to_hw_box(&box, &args->box);
	if (!vgdev->has_virgl_3d) {
		virtio_gpu_cmd_transfer_to_host_2d
			(vgdev, qobj, offset,
			 box.w, box.h, box.x, box.y, NULL);
	} else {
		fence = virtio_gpu_fence_alloc(vgdev);
		if (!fence) {
			ret = -ENOMEM;
			goto out_unres;
		}
		virtio_gpu_cmd_transfer_to_host_3d
			(vgdev, qobj,
			 vfpriv ? vfpriv->ctx_id : 0, offset,
			 args->level, &box, fence);
		dma_resv_add_excl_fence(qobj->tbo.base.resv,
						  &fence->f);
		dma_fence_put(&fence->f);
	}

out_unres:
	virtio_gpu_object_unreserve(qobj);
out:
	drm_gem_object_put_unlocked(gobj);
	return ret;
}