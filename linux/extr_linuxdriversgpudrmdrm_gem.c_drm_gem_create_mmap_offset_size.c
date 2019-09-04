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
struct drm_gem_object {int /*<<< orphan*/  vma_node; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  vma_offset_manager; } ;

/* Variables and functions */
 size_t PAGE_SIZE ; 
 int drm_vma_offset_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

int
drm_gem_create_mmap_offset_size(struct drm_gem_object *obj, size_t size)
{
	struct drm_device *dev = obj->dev;

	return drm_vma_offset_add(dev->vma_offset_manager, &obj->vma_node,
				  size / PAGE_SIZE);
}