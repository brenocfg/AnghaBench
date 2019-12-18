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
struct drm_gem_vram_object {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_vram_mmap_offset (struct drm_gem_vram_object*) ; 
 struct drm_gem_vram_object* drm_gem_vram_of_gem (struct drm_gem_object*) ; 

int drm_gem_vram_driver_dumb_mmap_offset(struct drm_file *file,
					 struct drm_device *dev,
					 uint32_t handle, uint64_t *offset)
{
	struct drm_gem_object *gem;
	struct drm_gem_vram_object *gbo;

	gem = drm_gem_object_lookup(file, handle);
	if (!gem)
		return -ENOENT;

	gbo = drm_gem_vram_of_gem(gem);
	*offset = drm_gem_vram_mmap_offset(gbo);

	drm_gem_object_put_unlocked(gem);

	return 0;
}