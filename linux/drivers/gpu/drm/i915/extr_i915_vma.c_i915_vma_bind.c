#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ size; int /*<<< orphan*/  start; } ;
struct i915_vma {scalar_t__ size; int flags; TYPE_2__* ops; int /*<<< orphan*/  pages; TYPE_1__* vm; TYPE_3__ node; } ;
typedef  enum i915_cache_level { ____Placeholder_i915_cache_level } i915_cache_level ;
struct TYPE_5__ {int (* bind_vma ) (struct i915_vma*,int,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  total; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ GEM_DEBUG_WARN_ON (int) ; 
 int I915_VMA_GLOBAL_BIND ; 
 int I915_VMA_LOCAL_BIND ; 
 int PIN_GLOBAL ; 
 int PIN_UPDATE ; 
 int PIN_USER ; 
 int /*<<< orphan*/  drm_mm_node_allocated (TYPE_3__*) ; 
 int range_overflows (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int stub1 (struct i915_vma*,int,int) ; 
 int /*<<< orphan*/  trace_i915_vma_bind (struct i915_vma*,int) ; 

int i915_vma_bind(struct i915_vma *vma, enum i915_cache_level cache_level,
		  u32 flags)
{
	u32 bind_flags;
	u32 vma_flags;
	int ret;

	GEM_BUG_ON(!drm_mm_node_allocated(&vma->node));
	GEM_BUG_ON(vma->size > vma->node.size);

	if (GEM_DEBUG_WARN_ON(range_overflows(vma->node.start,
					      vma->node.size,
					      vma->vm->total)))
		return -ENODEV;

	if (GEM_DEBUG_WARN_ON(!flags))
		return -EINVAL;

	bind_flags = 0;
	if (flags & PIN_GLOBAL)
		bind_flags |= I915_VMA_GLOBAL_BIND;
	if (flags & PIN_USER)
		bind_flags |= I915_VMA_LOCAL_BIND;

	vma_flags = vma->flags & (I915_VMA_GLOBAL_BIND | I915_VMA_LOCAL_BIND);
	if (flags & PIN_UPDATE)
		bind_flags |= vma_flags;
	else
		bind_flags &= ~vma_flags;
	if (bind_flags == 0)
		return 0;

	GEM_BUG_ON(!vma->pages);

	trace_i915_vma_bind(vma, bind_flags);
	ret = vma->ops->bind_vma(vma, cache_level, bind_flags);
	if (ret)
		return ret;

	vma->flags |= bind_flags;
	return 0;
}