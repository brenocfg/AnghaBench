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
struct TYPE_2__ {int /*<<< orphan*/  fw_domains_saved; int /*<<< orphan*/  pmic_bus_access_nb; } ;
struct drm_i915_private {TYPE_1__ uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_uncore_forcewake_reset (struct drm_i915_private*) ; 
 int /*<<< orphan*/  iosf_mbi_punit_acquire () ; 
 int /*<<< orphan*/  iosf_mbi_punit_release () ; 
 int /*<<< orphan*/  iosf_mbi_unregister_pmic_bus_access_notifier_unlocked (int /*<<< orphan*/ *) ; 

void intel_uncore_suspend(struct drm_i915_private *dev_priv)
{
	iosf_mbi_punit_acquire();
	iosf_mbi_unregister_pmic_bus_access_notifier_unlocked(
		&dev_priv->uncore.pmic_bus_access_nb);
	dev_priv->uncore.fw_domains_saved =
		intel_uncore_forcewake_reset(dev_priv);
	iosf_mbi_punit_release();
}