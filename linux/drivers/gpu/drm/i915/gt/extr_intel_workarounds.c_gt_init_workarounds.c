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
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_COFFEELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_KABYLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  bxt_gt_workarounds_init (struct drm_i915_private*,struct i915_wa_list*) ; 
 int /*<<< orphan*/  cfl_gt_workarounds_init (struct drm_i915_private*,struct i915_wa_list*) ; 
 int /*<<< orphan*/  cnl_gt_workarounds_init (struct drm_i915_private*,struct i915_wa_list*) ; 
 int /*<<< orphan*/  glk_gt_workarounds_init (struct drm_i915_private*,struct i915_wa_list*) ; 
 int /*<<< orphan*/  icl_gt_workarounds_init (struct drm_i915_private*,struct i915_wa_list*) ; 
 int /*<<< orphan*/  kbl_gt_workarounds_init (struct drm_i915_private*,struct i915_wa_list*) ; 
 int /*<<< orphan*/  skl_gt_workarounds_init (struct drm_i915_private*,struct i915_wa_list*) ; 
 int /*<<< orphan*/  tgl_gt_workarounds_init (struct drm_i915_private*,struct i915_wa_list*) ; 

__attribute__((used)) static void
gt_init_workarounds(struct drm_i915_private *i915, struct i915_wa_list *wal)
{
	if (IS_GEN(i915, 12))
		tgl_gt_workarounds_init(i915, wal);
	else if (IS_GEN(i915, 11))
		icl_gt_workarounds_init(i915, wal);
	else if (IS_CANNONLAKE(i915))
		cnl_gt_workarounds_init(i915, wal);
	else if (IS_COFFEELAKE(i915))
		cfl_gt_workarounds_init(i915, wal);
	else if (IS_GEMINILAKE(i915))
		glk_gt_workarounds_init(i915, wal);
	else if (IS_KABYLAKE(i915))
		kbl_gt_workarounds_init(i915, wal);
	else if (IS_BROXTON(i915))
		bxt_gt_workarounds_init(i915, wal);
	else if (IS_SKYLAKE(i915))
		skl_gt_workarounds_init(i915, wal);
	else if (INTEL_GEN(i915) <= 8)
		return;
	else
		MISSING_CASE(INTEL_GEN(i915));
}