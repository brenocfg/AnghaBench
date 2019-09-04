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
struct seq_file {int /*<<< orphan*/  private; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned long long I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MCH_SECP_NRG_STTS ; 
 int /*<<< orphan*/  MSR_RAPL_POWER_UNIT ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 scalar_t__ rdmsrl_safe (int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long long) ; 

__attribute__((used)) static int i915_energy_uJ(struct seq_file *m, void *data)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	unsigned long long power;
	u32 units;

	if (INTEL_GEN(dev_priv) < 6)
		return -ENODEV;

	intel_runtime_pm_get(dev_priv);

	if (rdmsrl_safe(MSR_RAPL_POWER_UNIT, &power)) {
		intel_runtime_pm_put(dev_priv);
		return -ENODEV;
	}

	units = (power & 0x1f00) >> 8;
	power = I915_READ(MCH_SECP_NRG_STTS);
	power = (1000000 * power) >> units; /* convert to uJ */

	intel_runtime_pm_put(dev_priv);

	seq_printf(m, "%llu", power);

	return 0;
}