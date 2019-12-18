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
typedef  int /*<<< orphan*/  u64 ;
struct intel_uc_fw {struct drm_i915_gem_object* obj; } ;
struct intel_gt {struct i915_ggtt* ggtt; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* clear_range ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct i915_ggtt {TYPE_2__ vm; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uc_fw_ggtt_offset (struct intel_uc_fw*,struct i915_ggtt*) ; 

__attribute__((used)) static void intel_uc_fw_ggtt_unbind(struct intel_uc_fw *uc_fw,
				    struct intel_gt *gt)
{
	struct drm_i915_gem_object *obj = uc_fw->obj;
	struct i915_ggtt *ggtt = gt->ggtt;
	u64 start = uc_fw_ggtt_offset(uc_fw, ggtt);

	ggtt->vm.clear_range(&ggtt->vm, start, obj->base.size);
}