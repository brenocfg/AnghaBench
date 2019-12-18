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
struct intel_vgpu {TYPE_1__* gvt; } ;
struct drm_i915_private {int /*<<< orphan*/  uncore; } ;
struct TYPE_2__ {struct drm_i915_private* dev_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  gvt_dbg_render (char*,int,char*,char*) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switch_mmio (struct intel_vgpu*,struct intel_vgpu*,int) ; 

void intel_gvt_switch_mmio(struct intel_vgpu *pre,
			   struct intel_vgpu *next, int ring_id)
{
	struct drm_i915_private *dev_priv;

	if (WARN_ON(!pre && !next))
		return;

	gvt_dbg_render("switch ring %d from %s to %s\n", ring_id,
		       pre ? "vGPU" : "host", next ? "vGPU" : "HOST");

	dev_priv = pre ? pre->gvt->dev_priv : next->gvt->dev_priv;

	/**
	 * We are using raw mmio access wrapper to improve the
	 * performace for batch mmio read/write, so we need
	 * handle forcewake mannually.
	 */
	intel_uncore_forcewake_get(&dev_priv->uncore, FORCEWAKE_ALL);
	switch_mmio(pre, next, ring_id);
	intel_uncore_forcewake_put(&dev_priv->uncore, FORCEWAKE_ALL);
}