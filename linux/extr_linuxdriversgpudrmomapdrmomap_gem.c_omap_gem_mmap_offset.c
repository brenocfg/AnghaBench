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
struct drm_gem_object {int /*<<< orphan*/  vma_node; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int drm_gem_create_mmap_offset_size (struct drm_gem_object*,size_t) ; 
 int /*<<< orphan*/  drm_vma_node_offset_addr (int /*<<< orphan*/ *) ; 
 size_t omap_gem_mmap_size (struct drm_gem_object*) ; 

u64 omap_gem_mmap_offset(struct drm_gem_object *obj)
{
	struct drm_device *dev = obj->dev;
	int ret;
	size_t size;

	/* Make it mmapable */
	size = omap_gem_mmap_size(obj);
	ret = drm_gem_create_mmap_offset_size(obj, size);
	if (ret) {
		dev_err(dev->dev, "could not allocate mmap offset\n");
		return 0;
	}

	return drm_vma_node_offset_addr(&obj->vma_node);
}