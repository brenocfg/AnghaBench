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
struct intel_fbc {int /*<<< orphan*/  lock; int /*<<< orphan*/  no_fbc_reason; } ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; struct intel_fbc fbc; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 int BDW_FBC_COMP_SEG_MASK ; 
 int DPFC_COMP_SEG_MASK ; 
 int /*<<< orphan*/  DPFC_STATUS ; 
 int ENODEV ; 
 int /*<<< orphan*/  FBC_STATUS ; 
 int FBC_STAT_COMPRESSED ; 
 int FBC_STAT_COMPRESSING ; 
 int /*<<< orphan*/  HAS_FBC (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int ILK_DPFC_COMP_SEG_MASK ; 
 int /*<<< orphan*/  ILK_DPFC_STATUS ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 int IVB_FBC_COMP_SEG_MASK ; 
 int /*<<< orphan*/  IVB_FBC_STATUS2 ; 
 scalar_t__ intel_fbc_is_active (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  yesno (int) ; 

__attribute__((used)) static int i915_fbc_status(struct seq_file *m, void *unused)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	struct intel_fbc *fbc = &dev_priv->fbc;
	intel_wakeref_t wakeref;

	if (!HAS_FBC(dev_priv))
		return -ENODEV;

	wakeref = intel_runtime_pm_get(&dev_priv->runtime_pm);
	mutex_lock(&fbc->lock);

	if (intel_fbc_is_active(dev_priv))
		seq_puts(m, "FBC enabled\n");
	else
		seq_printf(m, "FBC disabled: %s\n", fbc->no_fbc_reason);

	if (intel_fbc_is_active(dev_priv)) {
		u32 mask;

		if (INTEL_GEN(dev_priv) >= 8)
			mask = I915_READ(IVB_FBC_STATUS2) & BDW_FBC_COMP_SEG_MASK;
		else if (INTEL_GEN(dev_priv) >= 7)
			mask = I915_READ(IVB_FBC_STATUS2) & IVB_FBC_COMP_SEG_MASK;
		else if (INTEL_GEN(dev_priv) >= 5)
			mask = I915_READ(ILK_DPFC_STATUS) & ILK_DPFC_COMP_SEG_MASK;
		else if (IS_G4X(dev_priv))
			mask = I915_READ(DPFC_STATUS) & DPFC_COMP_SEG_MASK;
		else
			mask = I915_READ(FBC_STATUS) & (FBC_STAT_COMPRESSING |
							FBC_STAT_COMPRESSED);

		seq_printf(m, "Compressing: %s\n", yesno(mask));
	}

	mutex_unlock(&fbc->lock);
	intel_runtime_pm_put(&dev_priv->runtime_pm, wakeref);

	return 0;
}