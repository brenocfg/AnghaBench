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
struct g4x_wm_values {int /*<<< orphan*/  cxsr; } ;
struct TYPE_2__ {struct g4x_wm_values g4x; } ;
struct drm_i915_private {TYPE_1__ wm; } ;
typedef  int /*<<< orphan*/  new_wm ;

/* Variables and functions */
 int /*<<< orphan*/  _intel_set_memory_cxsr (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  g4x_merge_wm (struct drm_i915_private*,struct g4x_wm_values*) ; 
 int /*<<< orphan*/  g4x_write_wm_values (struct drm_i915_private*,struct g4x_wm_values*) ; 
 scalar_t__ is_disabling (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_enabling (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ memcmp (struct g4x_wm_values*,struct g4x_wm_values*,int) ; 

__attribute__((used)) static void g4x_program_watermarks(struct drm_i915_private *dev_priv)
{
	struct g4x_wm_values *old_wm = &dev_priv->wm.g4x;
	struct g4x_wm_values new_wm = {};

	g4x_merge_wm(dev_priv, &new_wm);

	if (memcmp(old_wm, &new_wm, sizeof(new_wm)) == 0)
		return;

	if (is_disabling(old_wm->cxsr, new_wm.cxsr, true))
		_intel_set_memory_cxsr(dev_priv, false);

	g4x_write_wm_values(dev_priv, &new_wm);

	if (is_enabling(old_wm->cxsr, new_wm.cxsr, true))
		_intel_set_memory_cxsr(dev_priv, true);

	*old_wm = new_wm;
}