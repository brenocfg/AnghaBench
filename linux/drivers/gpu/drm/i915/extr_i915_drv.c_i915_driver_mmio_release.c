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
struct drm_i915_private {int /*<<< orphan*/  bridge_dev; int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_engines_cleanup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_teardown_mchbar (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_fini_mmio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i915_driver_mmio_release(struct drm_i915_private *dev_priv)
{
	intel_engines_cleanup(dev_priv);
	intel_teardown_mchbar(dev_priv);
	intel_uncore_fini_mmio(&dev_priv->uncore);
	pci_dev_put(dev_priv->bridge_dev);
}