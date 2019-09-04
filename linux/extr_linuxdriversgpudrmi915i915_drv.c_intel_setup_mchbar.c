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
typedef  int u32 ;
struct drm_i915_private {int mchbar_need_disable; int /*<<< orphan*/  bridge_dev; } ;

/* Variables and functions */
 int DEVEN ; 
 int DEVEN_MCHBAR_EN ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_I915G (struct drm_i915_private*) ; 
 scalar_t__ IS_I915GM (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int MCHBAR_I915 ; 
 int MCHBAR_I965 ; 
 scalar_t__ intel_alloc_mchbar_resource (struct drm_i915_private*) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
intel_setup_mchbar(struct drm_i915_private *dev_priv)
{
	int mchbar_reg = INTEL_GEN(dev_priv) >= 4 ? MCHBAR_I965 : MCHBAR_I915;
	u32 temp;
	bool enabled;

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		return;

	dev_priv->mchbar_need_disable = false;

	if (IS_I915G(dev_priv) || IS_I915GM(dev_priv)) {
		pci_read_config_dword(dev_priv->bridge_dev, DEVEN, &temp);
		enabled = !!(temp & DEVEN_MCHBAR_EN);
	} else {
		pci_read_config_dword(dev_priv->bridge_dev, mchbar_reg, &temp);
		enabled = temp & 1;
	}

	/* If it's already enabled, don't have to do anything */
	if (enabled)
		return;

	if (intel_alloc_mchbar_resource(dev_priv))
		return;

	dev_priv->mchbar_need_disable = true;

	/* Space is allocated or reserved, so enable it. */
	if (IS_I915G(dev_priv) || IS_I915GM(dev_priv)) {
		pci_write_config_dword(dev_priv->bridge_dev, DEVEN,
				       temp | DEVEN_MCHBAR_EN);
	} else {
		pci_read_config_dword(dev_priv->bridge_dev, mchbar_reg, &temp);
		pci_write_config_dword(dev_priv->bridge_dev, mchbar_reg, temp | 1);
	}
}