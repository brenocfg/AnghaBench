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
struct TYPE_3__ {int /*<<< orphan*/  start; } ;
struct i915_vma {int /*<<< orphan*/  size; TYPE_1__ node; TYPE_2__* vm; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* clear_range ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct drm_i915_private* i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ggtt_unbind_vma(struct i915_vma *vma)
{
	struct drm_i915_private *i915 = vma->vm->i915;

	intel_runtime_pm_get(i915);
	vma->vm->clear_range(vma->vm, vma->node.start, vma->size);
	intel_runtime_pm_put(i915);
}