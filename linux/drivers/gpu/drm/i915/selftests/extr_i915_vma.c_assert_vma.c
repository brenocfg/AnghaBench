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
struct TYPE_3__ {scalar_t__ type; } ;
struct i915_vma {scalar_t__ vm; scalar_t__ size; TYPE_1__ ggtt_view; } ;
struct i915_gem_context {scalar_t__ vm; } ;
struct TYPE_4__ {scalar_t__ size; } ;
struct drm_i915_gem_object {TYPE_2__ base; } ;

/* Variables and functions */
 scalar_t__ I915_GGTT_VIEW_NORMAL ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static bool assert_vma(struct i915_vma *vma,
		       struct drm_i915_gem_object *obj,
		       struct i915_gem_context *ctx)
{
	bool ok = true;

	if (vma->vm != ctx->vm) {
		pr_err("VMA created with wrong VM\n");
		ok = false;
	}

	if (vma->size != obj->base.size) {
		pr_err("VMA created with wrong size, found %llu, expected %zu\n",
		       vma->size, obj->base.size);
		ok = false;
	}

	if (vma->ggtt_view.type != I915_GGTT_VIEW_NORMAL) {
		pr_err("VMA created with wrong type [%d]\n",
		       vma->ggtt_view.type);
		ok = false;
	}

	return ok;
}