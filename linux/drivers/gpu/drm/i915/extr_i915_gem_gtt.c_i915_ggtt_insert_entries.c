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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int start; } ;
struct i915_vma {TYPE_1__ node; int /*<<< orphan*/  pages; } ;
struct i915_address_space {int dummy; } ;
typedef  enum i915_cache_level { ____Placeholder_i915_cache_level } i915_cache_level ;

/* Variables and functions */
 unsigned int AGP_USER_CACHED_MEMORY ; 
 unsigned int AGP_USER_MEMORY ; 
 int I915_CACHE_NONE ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  intel_gtt_insert_sg_entries (int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static void i915_ggtt_insert_entries(struct i915_address_space *vm,
				     struct i915_vma *vma,
				     enum i915_cache_level cache_level,
				     u32 unused)
{
	unsigned int flags = (cache_level == I915_CACHE_NONE) ?
		AGP_USER_MEMORY : AGP_USER_CACHED_MEMORY;

	intel_gtt_insert_sg_entries(vma->pages, vma->node.start >> PAGE_SHIFT,
				    flags);
}