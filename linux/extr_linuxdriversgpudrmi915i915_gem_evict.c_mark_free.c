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
struct list_head {int dummy; } ;
struct i915_vma {int /*<<< orphan*/  node; int /*<<< orphan*/  evict_link; } ;
struct drm_mm_scan {int dummy; } ;

/* Variables and functions */
 unsigned int PIN_NONFAULT ; 
 int drm_mm_scan_add_block (struct drm_mm_scan*,int /*<<< orphan*/ *) ; 
 scalar_t__ i915_vma_has_userfault (struct i915_vma*) ; 
 scalar_t__ i915_vma_is_pinned (struct i915_vma*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static bool
mark_free(struct drm_mm_scan *scan,
	  struct i915_vma *vma,
	  unsigned int flags,
	  struct list_head *unwind)
{
	if (i915_vma_is_pinned(vma))
		return false;

	if (flags & PIN_NONFAULT && i915_vma_has_userfault(vma))
		return false;

	list_add(&vma->evict_link, unwind);
	return drm_mm_scan_add_block(scan, &vma->node);
}