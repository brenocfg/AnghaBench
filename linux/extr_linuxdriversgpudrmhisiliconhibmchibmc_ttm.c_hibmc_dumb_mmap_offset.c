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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hibmc_bo {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct hibmc_bo* gem_to_hibmc_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  hibmc_bo_mmap_offset (struct hibmc_bo*) ; 

int hibmc_dumb_mmap_offset(struct drm_file *file, struct drm_device *dev,
			   u32 handle, u64 *offset)
{
	struct drm_gem_object *obj;
	struct hibmc_bo *bo;

	obj = drm_gem_object_lookup(file, handle);
	if (!obj)
		return -ENOENT;

	bo = gem_to_hibmc_bo(obj);
	*offset = hibmc_bo_mmap_offset(bo);

	drm_gem_object_put_unlocked(obj);
	return 0;
}