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
struct i915_wa_list {int dummy; } ;
struct drm_i915_private {struct i915_wa_list gt_wa_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  gt_init_workarounds (struct drm_i915_private*,struct i915_wa_list*) ; 
 int /*<<< orphan*/  wa_init_finish (struct i915_wa_list*) ; 
 int /*<<< orphan*/  wa_init_start (struct i915_wa_list*,char*,char*) ; 

void intel_gt_init_workarounds(struct drm_i915_private *i915)
{
	struct i915_wa_list *wal = &i915->gt_wa_list;

	wa_init_start(wal, "GT", "global");
	gt_init_workarounds(i915, wal);
	wa_init_finish(wal);
}