#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct i915_vma {TYPE_2__* vm; } ;
typedef  enum i915_cache_level { ____Placeholder_i915_cache_level } i915_cache_level ;
struct TYPE_3__ {int (* bind_vma ) (struct i915_vma*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ vma_ops; } ;

/* Variables and functions */
 int stub1 (struct i915_vma*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vma_bind(struct i915_vma *vma,
		    enum i915_cache_level cache_level,
		    u32 flags)
{
	return vma->vm->vma_ops.bind_vma(vma, cache_level, flags);
}