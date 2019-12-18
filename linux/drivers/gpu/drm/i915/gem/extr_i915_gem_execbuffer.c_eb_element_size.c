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
struct i915_vma {int dummy; } ;
struct drm_i915_gem_exec_object2 {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static size_t eb_element_size(void)
{
	return (sizeof(struct drm_i915_gem_exec_object2) +
		sizeof(struct i915_vma *) +
		sizeof(unsigned int));
}