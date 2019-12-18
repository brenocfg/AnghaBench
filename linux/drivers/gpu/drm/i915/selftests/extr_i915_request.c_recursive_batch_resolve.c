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
struct i915_vma {int /*<<< orphan*/  obj; TYPE_1__* vm; } ;
struct TYPE_2__ {int /*<<< orphan*/  gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_MAP_WC ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MI_BATCH_BUFFER_END ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * i915_gem_object_pin_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_gt_chipset_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int recursive_batch_resolve(struct i915_vma *batch)
{
	u32 *cmd;

	cmd = i915_gem_object_pin_map(batch->obj, I915_MAP_WC);
	if (IS_ERR(cmd))
		return PTR_ERR(cmd);

	*cmd = MI_BATCH_BUFFER_END;
	intel_gt_chipset_flush(batch->vm->gt);

	i915_gem_object_unpin_map(batch->obj);

	return 0;
}