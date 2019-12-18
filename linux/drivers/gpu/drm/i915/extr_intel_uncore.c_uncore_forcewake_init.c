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
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct intel_uncore {TYPE_1__ pmic_bus_access_nb; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN_FW_DOMAINS_TABLE (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSIGN_READ_MMIO_VFUNCS (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSIGN_WRITE_MMIO_VFUNCS (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_GEN_RANGE (struct drm_i915_private*,int,int) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  __chv_fw_ranges ; 
 int /*<<< orphan*/  __gen11_fw_ranges ; 
 int /*<<< orphan*/  __gen9_fw_ranges ; 
 int /*<<< orphan*/  __vlv_fw_ranges ; 
 int /*<<< orphan*/  forcewake_early_sanitize (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwtable ; 
 int /*<<< orphan*/  gen11_fwtable ; 
 int /*<<< orphan*/  gen6 ; 
 int /*<<< orphan*/  gen8 ; 
 int /*<<< orphan*/  i915_pmic_bus_access_notifier ; 
 int intel_uncore_fw_domains_init (struct intel_uncore*) ; 
 int /*<<< orphan*/  intel_uncore_has_forcewake (struct intel_uncore*) ; 
 int /*<<< orphan*/  iosf_mbi_register_pmic_bus_access_notifier (TYPE_1__*) ; 

__attribute__((used)) static int uncore_forcewake_init(struct intel_uncore *uncore)
{
	struct drm_i915_private *i915 = uncore->i915;
	int ret;

	GEM_BUG_ON(!intel_uncore_has_forcewake(uncore));

	ret = intel_uncore_fw_domains_init(uncore);
	if (ret)
		return ret;
	forcewake_early_sanitize(uncore, 0);

	if (IS_GEN_RANGE(i915, 6, 7)) {
		ASSIGN_WRITE_MMIO_VFUNCS(uncore, gen6);

		if (IS_VALLEYVIEW(i915)) {
			ASSIGN_FW_DOMAINS_TABLE(uncore, __vlv_fw_ranges);
			ASSIGN_READ_MMIO_VFUNCS(uncore, fwtable);
		} else {
			ASSIGN_READ_MMIO_VFUNCS(uncore, gen6);
		}
	} else if (IS_GEN(i915, 8)) {
		if (IS_CHERRYVIEW(i915)) {
			ASSIGN_FW_DOMAINS_TABLE(uncore, __chv_fw_ranges);
			ASSIGN_WRITE_MMIO_VFUNCS(uncore, fwtable);
			ASSIGN_READ_MMIO_VFUNCS(uncore, fwtable);
		} else {
			ASSIGN_WRITE_MMIO_VFUNCS(uncore, gen8);
			ASSIGN_READ_MMIO_VFUNCS(uncore, gen6);
		}
	} else if (IS_GEN_RANGE(i915, 9, 10)) {
		ASSIGN_FW_DOMAINS_TABLE(uncore, __gen9_fw_ranges);
		ASSIGN_WRITE_MMIO_VFUNCS(uncore, fwtable);
		ASSIGN_READ_MMIO_VFUNCS(uncore, fwtable);
	} else {
		ASSIGN_FW_DOMAINS_TABLE(uncore, __gen11_fw_ranges);
		ASSIGN_WRITE_MMIO_VFUNCS(uncore, gen11_fwtable);
		ASSIGN_READ_MMIO_VFUNCS(uncore, gen11_fwtable);
	}

	uncore->pmic_bus_access_nb.notifier_call = i915_pmic_bus_access_notifier;
	iosf_mbi_register_pmic_bus_access_notifier(&uncore->pmic_bus_access_nb);

	return 0;
}