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
typedef  int u32 ;
struct i915_vma {int /*<<< orphan*/  flags; } ;
typedef  enum i915_cache_level { ____Placeholder_i915_cache_level } i915_cache_level ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int I915_VMA_GLOBAL_BIND ; 
 int /*<<< orphan*/  I915_VMA_LOCAL_BIND ; 

__attribute__((used)) static int mock_bind_ppgtt(struct i915_vma *vma,
			   enum i915_cache_level cache_level,
			   u32 flags)
{
	GEM_BUG_ON(flags & I915_VMA_GLOBAL_BIND);
	vma->flags |= I915_VMA_LOCAL_BIND;
	return 0;
}