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
struct TYPE_2__ {int /*<<< orphan*/  uc; } ;
struct drm_i915_private {int /*<<< orphan*/  bridge_dev; int /*<<< orphan*/  uncore; TYPE_1__ gt; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  i915_gem_init_mmio (struct drm_i915_private*) ; 
 scalar_t__ i915_get_bridge_dev (struct drm_i915_private*) ; 
 scalar_t__ i915_inject_probe_failure (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_device_info_init_mmio (struct drm_i915_private*) ; 
 int intel_engines_init_mmio (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_setup_mchbar (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_teardown_mchbar (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_init_mmio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uncore_fini_mmio (int /*<<< orphan*/ *) ; 
 int intel_uncore_init_mmio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uncore_prune_mmio_domains (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_driver_mmio_probe(struct drm_i915_private *dev_priv)
{
	int ret;

	if (i915_inject_probe_failure(dev_priv))
		return -ENODEV;

	if (i915_get_bridge_dev(dev_priv))
		return -EIO;

	ret = intel_uncore_init_mmio(&dev_priv->uncore);
	if (ret < 0)
		goto err_bridge;

	/* Try to make sure MCHBAR is enabled before poking at it */
	intel_setup_mchbar(dev_priv);

	intel_device_info_init_mmio(dev_priv);

	intel_uncore_prune_mmio_domains(&dev_priv->uncore);

	intel_uc_init_mmio(&dev_priv->gt.uc);

	ret = intel_engines_init_mmio(dev_priv);
	if (ret)
		goto err_uncore;

	i915_gem_init_mmio(dev_priv);

	return 0;

err_uncore:
	intel_teardown_mchbar(dev_priv);
	intel_uncore_fini_mmio(&dev_priv->uncore);
err_bridge:
	pci_dev_put(dev_priv->bridge_dev);

	return ret;
}