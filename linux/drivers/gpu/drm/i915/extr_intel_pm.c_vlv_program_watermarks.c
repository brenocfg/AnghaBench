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
struct vlv_wm_values {int /*<<< orphan*/  level; int /*<<< orphan*/  cxsr; } ;
struct TYPE_2__ {struct vlv_wm_values vlv; } ;
struct drm_i915_private {TYPE_1__ wm; } ;
typedef  int /*<<< orphan*/  new_wm ;

/* Variables and functions */
 int VLV_WM_LEVEL_DDR_DVFS ; 
 int VLV_WM_LEVEL_PM5 ; 
 int /*<<< orphan*/  _intel_set_memory_cxsr (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  chv_set_memory_dvfs (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  chv_set_memory_pm5 (struct drm_i915_private*,int) ; 
 scalar_t__ is_disabling (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_enabling (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ memcmp (struct vlv_wm_values*,struct vlv_wm_values*,int) ; 
 int /*<<< orphan*/  vlv_merge_wm (struct drm_i915_private*,struct vlv_wm_values*) ; 
 int /*<<< orphan*/  vlv_write_wm_values (struct drm_i915_private*,struct vlv_wm_values*) ; 

__attribute__((used)) static void vlv_program_watermarks(struct drm_i915_private *dev_priv)
{
	struct vlv_wm_values *old_wm = &dev_priv->wm.vlv;
	struct vlv_wm_values new_wm = {};

	vlv_merge_wm(dev_priv, &new_wm);

	if (memcmp(old_wm, &new_wm, sizeof(new_wm)) == 0)
		return;

	if (is_disabling(old_wm->level, new_wm.level, VLV_WM_LEVEL_DDR_DVFS))
		chv_set_memory_dvfs(dev_priv, false);

	if (is_disabling(old_wm->level, new_wm.level, VLV_WM_LEVEL_PM5))
		chv_set_memory_pm5(dev_priv, false);

	if (is_disabling(old_wm->cxsr, new_wm.cxsr, true))
		_intel_set_memory_cxsr(dev_priv, false);

	vlv_write_wm_values(dev_priv, &new_wm);

	if (is_enabling(old_wm->cxsr, new_wm.cxsr, true))
		_intel_set_memory_cxsr(dev_priv, true);

	if (is_enabling(old_wm->level, new_wm.level, VLV_WM_LEVEL_PM5))
		chv_set_memory_pm5(dev_priv, true);

	if (is_enabling(old_wm->level, new_wm.level, VLV_WM_LEVEL_DDR_DVFS))
		chv_set_memory_dvfs(dev_priv, true);

	*old_wm = new_wm;
}