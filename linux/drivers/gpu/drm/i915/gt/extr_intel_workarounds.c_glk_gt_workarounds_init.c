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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen9_gt_workarounds_init (struct drm_i915_private*,struct i915_wa_list*) ; 

__attribute__((used)) static void
glk_gt_workarounds_init(struct drm_i915_private *i915, struct i915_wa_list *wal)
{
	gen9_gt_workarounds_init(i915, wal);
}