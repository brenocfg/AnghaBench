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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ total; int /*<<< orphan*/  i915; } ;
struct i915_ggtt {int /*<<< orphan*/  uc_fw; TYPE_1__ vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ GUC_GGTT_TOP ; 
 int /*<<< orphan*/  I915_COLOR_UNEVICTABLE ; 
 int /*<<< orphan*/  PIN_NOEVICT ; 
 int /*<<< orphan*/  USES_GUC (int /*<<< orphan*/ ) ; 
 int i915_gem_gtt_reserve (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ggtt_reserve_guc_top(struct i915_ggtt *ggtt)
{
	u64 size;
	int ret;

	if (!USES_GUC(ggtt->vm.i915))
		return 0;

	GEM_BUG_ON(ggtt->vm.total <= GUC_GGTT_TOP);
	size = ggtt->vm.total - GUC_GGTT_TOP;

	ret = i915_gem_gtt_reserve(&ggtt->vm, &ggtt->uc_fw, size,
				   GUC_GGTT_TOP, I915_COLOR_UNEVICTABLE,
				   PIN_NOEVICT);
	if (ret)
		DRM_DEBUG_DRIVER("Failed to reserve top of GGTT for GuC\n");

	return ret;
}