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
struct msm_gem_object {int /*<<< orphan*/  lock; } ;
struct drm_gem_object {int /*<<< orphan*/  vma_node; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int drm_gem_create_mmap_offset (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_vma_node_offset_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 

__attribute__((used)) static uint64_t mmap_offset(struct drm_gem_object *obj)
{
	struct drm_device *dev = obj->dev;
	struct msm_gem_object *msm_obj = to_msm_bo(obj);
	int ret;

	WARN_ON(!mutex_is_locked(&msm_obj->lock));

	/* Make it mmapable */
	ret = drm_gem_create_mmap_offset(obj);

	if (ret) {
		dev_err(dev->dev, "could not allocate mmap offset\n");
		return 0;
	}

	return drm_vma_node_offset_addr(&obj->vma_node);
}