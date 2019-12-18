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
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct virtio_gpu_object {int /*<<< orphan*/  hw_res_handle; TYPE_1__ gem_base; } ;
struct drm_virtgpu_resource_info {int /*<<< orphan*/  res_handle; int /*<<< orphan*/  size; int /*<<< orphan*/  bo_handle; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct virtio_gpu_object* gem_to_virtio_gpu_obj (struct drm_gem_object*) ; 

__attribute__((used)) static int virtio_gpu_resource_info_ioctl(struct drm_device *dev, void *data,
					  struct drm_file *file_priv)
{
	struct drm_virtgpu_resource_info *ri = data;
	struct drm_gem_object *gobj = NULL;
	struct virtio_gpu_object *qobj = NULL;

	gobj = drm_gem_object_lookup(file_priv, ri->bo_handle);
	if (gobj == NULL)
		return -ENOENT;

	qobj = gem_to_virtio_gpu_obj(gobj);

	ri->size = qobj->gem_base.size;
	ri->res_handle = qobj->hw_res_handle;
	drm_gem_object_put_unlocked(gobj);
	return 0;
}