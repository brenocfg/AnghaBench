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
struct intel_fbc {int /*<<< orphan*/ * compressed_llb; int /*<<< orphan*/  compressed_fb; } ;
struct drm_i915_private {struct intel_fbc fbc; } ;

/* Variables and functions */
 scalar_t__ drm_mm_node_allocated (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_stolen_remove_node (struct drm_i915_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __intel_fbc_cleanup_cfb(struct drm_i915_private *dev_priv)
{
	struct intel_fbc *fbc = &dev_priv->fbc;

	if (drm_mm_node_allocated(&fbc->compressed_fb))
		i915_gem_stolen_remove_node(dev_priv, &fbc->compressed_fb);

	if (fbc->compressed_llb) {
		i915_gem_stolen_remove_node(dev_priv, fbc->compressed_llb);
		kfree(fbc->compressed_llb);
	}
}