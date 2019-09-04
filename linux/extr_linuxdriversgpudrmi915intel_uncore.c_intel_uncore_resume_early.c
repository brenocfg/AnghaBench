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
struct TYPE_2__ {int /*<<< orphan*/  pmic_bus_access_nb; int /*<<< orphan*/  fw_domains_saved; } ;
struct drm_i915_private {TYPE_1__ uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  __intel_uncore_early_sanitize (struct drm_i915_private*,unsigned int) ; 
 unsigned int fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_check_and_clear_faults (struct drm_i915_private*) ; 
 int /*<<< orphan*/  iosf_mbi_register_pmic_bus_access_notifier (int /*<<< orphan*/ *) ; 

void intel_uncore_resume_early(struct drm_i915_private *dev_priv)
{
	unsigned int restore_forcewake;

	restore_forcewake = fetch_and_zero(&dev_priv->uncore.fw_domains_saved);
	__intel_uncore_early_sanitize(dev_priv, restore_forcewake);

	iosf_mbi_register_pmic_bus_access_notifier(
		&dev_priv->uncore.pmic_bus_access_nb);
	i915_check_and_clear_faults(dev_priv);
}