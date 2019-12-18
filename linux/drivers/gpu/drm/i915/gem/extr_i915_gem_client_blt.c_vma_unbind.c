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
struct i915_vma {TYPE_2__* vm; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* unbind_vma ) (struct i915_vma*) ;} ;
struct TYPE_4__ {TYPE_1__ vma_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct i915_vma*) ; 

__attribute__((used)) static void vma_unbind(struct i915_vma *vma)
{
	vma->vm->vma_ops.unbind_vma(vma);
}