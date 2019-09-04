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
struct i915_vma {TYPE_1__* vm; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {struct drm_i915_private* i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUC_STATUS ; 
 int /*<<< orphan*/  POSTING_READ_FW (int /*<<< orphan*/ ) ; 
 scalar_t__ i915_vma_is_map_and_fenceable (struct i915_vma*) ; 

__attribute__((used)) static void flush_ggtt_writes(struct i915_vma *vma)
{
	struct drm_i915_private *dev_priv = vma->vm->i915;

	if (i915_vma_is_map_and_fenceable(vma))
		POSTING_READ_FW(GUC_STATUS);
}