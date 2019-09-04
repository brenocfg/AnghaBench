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
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct bochs_bo {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  bochs_bo_mmap_offset (struct bochs_bo*) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (struct drm_gem_object*) ; 
 struct bochs_bo* gem_to_bochs_bo (struct drm_gem_object*) ; 

int bochs_dumb_mmap_offset(struct drm_file *file, struct drm_device *dev,
			   uint32_t handle, uint64_t *offset)
{
	struct drm_gem_object *obj;
	struct bochs_bo *bo;

	obj = drm_gem_object_lookup(file, handle);
	if (obj == NULL)
		return -ENOENT;

	bo = gem_to_bochs_bo(obj);
	*offset = bochs_bo_mmap_offset(bo);

	drm_gem_object_unreference_unlocked(obj);
	return 0;
}