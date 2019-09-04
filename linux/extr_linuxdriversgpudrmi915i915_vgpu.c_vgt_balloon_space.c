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
struct TYPE_2__ {unsigned long reserved; } ;
struct i915_ggtt {TYPE_1__ vm; } ;
struct drm_mm_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,unsigned long,unsigned long,unsigned long) ; 
 int EINVAL ; 
 int /*<<< orphan*/  I915_COLOR_UNEVICTABLE ; 
 int i915_gem_gtt_reserve (TYPE_1__*,struct drm_mm_node*,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vgt_balloon_space(struct i915_ggtt *ggtt,
			     struct drm_mm_node *node,
			     unsigned long start, unsigned long end)
{
	unsigned long size = end - start;
	int ret;

	if (start >= end)
		return -EINVAL;

	DRM_INFO("balloon space: range [ 0x%lx - 0x%lx ] %lu KiB.\n",
		 start, end, size / 1024);
	ret = i915_gem_gtt_reserve(&ggtt->vm, node,
				   size, start, I915_COLOR_UNEVICTABLE,
				   0);
	if (!ret)
		ggtt->vm.reserved += size;

	return ret;
}