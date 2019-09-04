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
struct drm_i915_private {int /*<<< orphan*/  bridge_dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  i915_gem_init_mmio (struct drm_i915_private*) ; 
 scalar_t__ i915_get_bridge_dev (struct drm_i915_private*) ; 
 scalar_t__ i915_inject_load_failure () ; 
 int i915_mmio_setup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_device_info_init_mmio (struct drm_i915_private*) ; 
 int intel_engines_init_mmio (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_init_mmio (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_fini (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_prune (struct drm_i915_private*) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_driver_init_mmio(struct drm_i915_private *dev_priv)
{
	int ret;

	if (i915_inject_load_failure())
		return -ENODEV;

	if (i915_get_bridge_dev(dev_priv))
		return -EIO;

	ret = i915_mmio_setup(dev_priv);
	if (ret < 0)
		goto err_bridge;

	intel_uncore_init(dev_priv);

	intel_device_info_init_mmio(dev_priv);

	intel_uncore_prune(dev_priv);

	intel_uc_init_mmio(dev_priv);

	ret = intel_engines_init_mmio(dev_priv);
	if (ret)
		goto err_uncore;

	i915_gem_init_mmio(dev_priv);

	return 0;

err_uncore:
	intel_uncore_fini(dev_priv);
err_bridge:
	pci_dev_put(dev_priv->bridge_dev);

	return ret;
}