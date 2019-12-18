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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ start; } ;
struct drm_i915_private {TYPE_1__ mch_res; int /*<<< orphan*/  bridge_dev; scalar_t__ mchbar_need_disable; } ;

/* Variables and functions */
 int DEVEN ; 
 int DEVEN_MCHBAR_EN ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_I915G (struct drm_i915_private*) ; 
 scalar_t__ IS_I915GM (struct drm_i915_private*) ; 
 int MCHBAR_I915 ; 
 int MCHBAR_I965 ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  release_resource (TYPE_1__*) ; 

__attribute__((used)) static void
intel_teardown_mchbar(struct drm_i915_private *dev_priv)
{
	int mchbar_reg = INTEL_GEN(dev_priv) >= 4 ? MCHBAR_I965 : MCHBAR_I915;

	if (dev_priv->mchbar_need_disable) {
		if (IS_I915G(dev_priv) || IS_I915GM(dev_priv)) {
			u32 deven_val;

			pci_read_config_dword(dev_priv->bridge_dev, DEVEN,
					      &deven_val);
			deven_val &= ~DEVEN_MCHBAR_EN;
			pci_write_config_dword(dev_priv->bridge_dev, DEVEN,
					       deven_val);
		} else {
			u32 mchbar_val;

			pci_read_config_dword(dev_priv->bridge_dev, mchbar_reg,
					      &mchbar_val);
			mchbar_val &= ~1;
			pci_write_config_dword(dev_priv->bridge_dev, mchbar_reg,
					       mchbar_val);
		}
	}

	if (dev_priv->mch_res.start)
		release_resource(&dev_priv->mch_res);
}