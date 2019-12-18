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
struct TYPE_2__ {int /*<<< orphan*/  dmc_payload; } ;
struct drm_i915_private {TYPE_1__ csr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_CSR (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_csr_runtime_pm_get (struct drm_i915_private*) ; 

void intel_csr_ucode_resume(struct drm_i915_private *dev_priv)
{
	if (!HAS_CSR(dev_priv))
		return;

	/*
	 * Reacquire the reference to keep RPM disabled in case DMC isn't
	 * loaded.
	 */
	if (!dev_priv->csr.dmc_payload)
		intel_csr_runtime_pm_get(dev_priv);
}