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
struct seq_file {int /*<<< orphan*/  private; } ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;
struct TYPE_2__ {int /*<<< orphan*/  enable_ips; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HAS_IPS (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IPS_CTL ; 
 int IPS_ENABLE ; 
 TYPE_1__ i915_modparams ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  yesno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_ips_status(struct seq_file *m, void *unused)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	intel_wakeref_t wakeref;

	if (!HAS_IPS(dev_priv))
		return -ENODEV;

	wakeref = intel_runtime_pm_get(&dev_priv->runtime_pm);

	seq_printf(m, "Enabled by kernel parameter: %s\n",
		   yesno(i915_modparams.enable_ips));

	if (INTEL_GEN(dev_priv) >= 8) {
		seq_puts(m, "Currently: unknown\n");
	} else {
		if (I915_READ(IPS_CTL) & IPS_ENABLE)
			seq_puts(m, "Currently: enabled\n");
		else
			seq_puts(m, "Currently: disabled\n");
	}

	intel_runtime_pm_put(&dev_priv->runtime_pm, wakeref);

	return 0;
}