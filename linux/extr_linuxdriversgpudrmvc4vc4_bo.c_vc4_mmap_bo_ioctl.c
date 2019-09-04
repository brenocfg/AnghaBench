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
struct drm_vc4_mmap_bo {int /*<<< orphan*/  offset; int /*<<< orphan*/  handle; } ;
struct drm_gem_object {int /*<<< orphan*/  vma_node; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_vma_node_offset_addr (int /*<<< orphan*/ *) ; 

int vc4_mmap_bo_ioctl(struct drm_device *dev, void *data,
		      struct drm_file *file_priv)
{
	struct drm_vc4_mmap_bo *args = data;
	struct drm_gem_object *gem_obj;

	gem_obj = drm_gem_object_lookup(file_priv, args->handle);
	if (!gem_obj) {
		DRM_DEBUG("Failed to look up GEM BO %d\n", args->handle);
		return -EINVAL;
	}

	/* The mmap offset was set up at BO allocation time. */
	args->offset = drm_vma_node_offset_addr(&gem_obj->vma_node);

	drm_gem_object_put_unlocked(gem_obj);
	return 0;
}