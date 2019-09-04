#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_3__ {int unclaimed_mmio_check; TYPE_2__ pmic_bus_access_nb; } ;
struct drm_i915_private {TYPE_1__ uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN_FW_DOMAINS_TABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSIGN_READ_MMIO_VFUNCS (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSIGN_WRITE_MMIO_VFUNCS (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int,int) ; 
 scalar_t__ IS_GEN5 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN8 (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  __chv_fw_ranges ; 
 int /*<<< orphan*/  __gen11_fw_ranges ; 
 int /*<<< orphan*/  __gen9_fw_ranges ; 
 int /*<<< orphan*/  __intel_uncore_early_sanitize (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __vlv_fw_ranges ; 
 int /*<<< orphan*/  fwtable ; 
 int /*<<< orphan*/  gen11_fwtable ; 
 int /*<<< orphan*/  gen2 ; 
 int /*<<< orphan*/  gen5 ; 
 int /*<<< orphan*/  gen6 ; 
 int /*<<< orphan*/  gen8 ; 
 int /*<<< orphan*/  i915_check_vgpu (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_pmic_bus_access_notifier ; 
 int /*<<< orphan*/  intel_uncore_edram_detect (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_fw_domains_init (struct drm_i915_private*) ; 
 scalar_t__ intel_vgpu_active (struct drm_i915_private*) ; 
 int /*<<< orphan*/  iosf_mbi_register_pmic_bus_access_notifier (TYPE_2__*) ; 

void intel_uncore_init(struct drm_i915_private *dev_priv)
{
	i915_check_vgpu(dev_priv);

	intel_uncore_edram_detect(dev_priv);
	intel_uncore_fw_domains_init(dev_priv);
	__intel_uncore_early_sanitize(dev_priv, 0);

	dev_priv->uncore.unclaimed_mmio_check = 1;
	dev_priv->uncore.pmic_bus_access_nb.notifier_call =
		i915_pmic_bus_access_notifier;

	if (IS_GEN(dev_priv, 2, 4) || intel_vgpu_active(dev_priv)) {
		ASSIGN_WRITE_MMIO_VFUNCS(dev_priv, gen2);
		ASSIGN_READ_MMIO_VFUNCS(dev_priv, gen2);
	} else if (IS_GEN5(dev_priv)) {
		ASSIGN_WRITE_MMIO_VFUNCS(dev_priv, gen5);
		ASSIGN_READ_MMIO_VFUNCS(dev_priv, gen5);
	} else if (IS_GEN(dev_priv, 6, 7)) {
		ASSIGN_WRITE_MMIO_VFUNCS(dev_priv, gen6);

		if (IS_VALLEYVIEW(dev_priv)) {
			ASSIGN_FW_DOMAINS_TABLE(__vlv_fw_ranges);
			ASSIGN_READ_MMIO_VFUNCS(dev_priv, fwtable);
		} else {
			ASSIGN_READ_MMIO_VFUNCS(dev_priv, gen6);
		}
	} else if (IS_GEN8(dev_priv)) {
		if (IS_CHERRYVIEW(dev_priv)) {
			ASSIGN_FW_DOMAINS_TABLE(__chv_fw_ranges);
			ASSIGN_WRITE_MMIO_VFUNCS(dev_priv, fwtable);
			ASSIGN_READ_MMIO_VFUNCS(dev_priv, fwtable);

		} else {
			ASSIGN_WRITE_MMIO_VFUNCS(dev_priv, gen8);
			ASSIGN_READ_MMIO_VFUNCS(dev_priv, gen6);
		}
	} else if (IS_GEN(dev_priv, 9, 10)) {
		ASSIGN_FW_DOMAINS_TABLE(__gen9_fw_ranges);
		ASSIGN_WRITE_MMIO_VFUNCS(dev_priv, fwtable);
		ASSIGN_READ_MMIO_VFUNCS(dev_priv, fwtable);
	} else {
		ASSIGN_FW_DOMAINS_TABLE(__gen11_fw_ranges);
		ASSIGN_WRITE_MMIO_VFUNCS(dev_priv, gen11_fwtable);
		ASSIGN_READ_MMIO_VFUNCS(dev_priv, gen11_fwtable);
	}

	iosf_mbi_register_pmic_bus_access_notifier(
		&dev_priv->uncore.pmic_bus_access_nb);
}