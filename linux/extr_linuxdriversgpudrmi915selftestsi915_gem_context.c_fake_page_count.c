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
struct drm_i915_gem_object {int dummy; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned long huge_gem_object_dma_size (struct drm_i915_gem_object*) ; 

__attribute__((used)) static unsigned long fake_page_count(struct drm_i915_gem_object *obj)
{
	return huge_gem_object_dma_size(obj) >> PAGE_SHIFT;
}