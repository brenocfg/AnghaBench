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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int fw_domains; } ;
struct drm_i915_private {TYPE_1__ uncore; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum forcewake_domains { ____Placeholder_forcewake_domains } forcewake_domains ;

/* Variables and functions */
 int FORCEWAKE_RENDER ; 
 scalar_t__ HAS_FWTABLE (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int,int) ; 
 scalar_t__ IS_GEN8 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __fwtable_reg_write_fw_domains (int /*<<< orphan*/ ) ; 
 int __gen11_fwtable_reg_write_fw_domains (int /*<<< orphan*/ ) ; 
 int __gen8_reg_write_fw_domains (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum forcewake_domains
intel_uncore_forcewake_for_write(struct drm_i915_private *dev_priv,
				 i915_reg_t reg)
{
	u32 offset = i915_mmio_reg_offset(reg);
	enum forcewake_domains fw_domains;

	if (INTEL_GEN(dev_priv) >= 11) {
		fw_domains = __gen11_fwtable_reg_write_fw_domains(offset);
	} else if (HAS_FWTABLE(dev_priv) && !IS_VALLEYVIEW(dev_priv)) {
		fw_domains = __fwtable_reg_write_fw_domains(offset);
	} else if (IS_GEN8(dev_priv)) {
		fw_domains = __gen8_reg_write_fw_domains(offset);
	} else if (IS_GEN(dev_priv, 6, 7)) {
		fw_domains = FORCEWAKE_RENDER;
	} else {
		WARN_ON(!IS_GEN(dev_priv, 2, 5));
		fw_domains = 0;
	}

	WARN_ON(fw_domains & ~dev_priv->uncore.fw_domains);

	return fw_domains;
}