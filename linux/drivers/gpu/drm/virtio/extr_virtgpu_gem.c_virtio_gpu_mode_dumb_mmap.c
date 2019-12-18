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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct virtio_gpu_object {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOENT ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct virtio_gpu_object* gem_to_virtio_gpu_obj (struct drm_gem_object*) ; 
 int /*<<< orphan*/  virtio_gpu_object_mmap_offset (struct virtio_gpu_object*) ; 

int virtio_gpu_mode_dumb_mmap(struct drm_file *file_priv,
			      struct drm_device *dev,
			      uint32_t handle, uint64_t *offset_p)
{
	struct drm_gem_object *gobj;
	struct virtio_gpu_object *obj;

	BUG_ON(!offset_p);
	gobj = drm_gem_object_lookup(file_priv, handle);
	if (gobj == NULL)
		return -ENOENT;
	obj = gem_to_virtio_gpu_obj(gobj);
	*offset_p = virtio_gpu_object_mmap_offset(obj);
	drm_gem_object_put_unlocked(gobj);
	return 0;
}