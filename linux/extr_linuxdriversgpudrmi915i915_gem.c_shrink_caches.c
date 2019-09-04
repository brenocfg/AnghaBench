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
struct drm_i915_private {int /*<<< orphan*/  objects; int /*<<< orphan*/  vmas; int /*<<< orphan*/  luts; int /*<<< orphan*/  requests; int /*<<< orphan*/  dependencies; int /*<<< orphan*/  priorities; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_shrink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shrink_caches(struct drm_i915_private *i915)
{
	/*
	 * kmem_cache_shrink() discards empty slabs and reorders partially
	 * filled slabs to prioritise allocating from the mostly full slabs,
	 * with the aim of reducing fragmentation.
	 */
	kmem_cache_shrink(i915->priorities);
	kmem_cache_shrink(i915->dependencies);
	kmem_cache_shrink(i915->requests);
	kmem_cache_shrink(i915->luts);
	kmem_cache_shrink(i915->vmas);
	kmem_cache_shrink(i915->objects);
}