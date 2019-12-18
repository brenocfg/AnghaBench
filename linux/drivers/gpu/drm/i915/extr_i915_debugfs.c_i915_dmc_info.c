#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int /*<<< orphan*/  private; } ;
struct intel_csr {int /*<<< orphan*/  version; int /*<<< orphan*/ * dmc_payload; int /*<<< orphan*/  fw_path; } ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; struct intel_csr csr; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;
struct TYPE_11__ {scalar_t__ reg; } ;
typedef  TYPE_1__ i915_reg_t ;

/* Variables and functions */
 TYPE_1__ BXT_CSR_DC3_DC5_COUNT ; 
 TYPE_1__ CSR_HTP_SKL ; 
 TYPE_1__ CSR_PROGRAM (int /*<<< orphan*/ ) ; 
 TYPE_1__ CSR_SSP_BASE ; 
 int /*<<< orphan*/  CSR_VERSION_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_VERSION_MINOR (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  HAS_CSR (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_READ (TYPE_1__) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_GEN9_LP (struct drm_i915_private*) ; 
 TYPE_1__ SKL_CSR_DC3_DC5_COUNT ; 
 TYPE_1__ SKL_CSR_DC5_DC6_COUNT ; 
 TYPE_1__ TGL_DMC_DEBUG_DC5_COUNT ; 
 TYPE_1__ TGL_DMC_DEBUG_DC6_COUNT ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  yesno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_dmc_info(struct seq_file *m, void *unused)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	intel_wakeref_t wakeref;
	struct intel_csr *csr;
	i915_reg_t dc5_reg, dc6_reg = {};

	if (!HAS_CSR(dev_priv))
		return -ENODEV;

	csr = &dev_priv->csr;

	wakeref = intel_runtime_pm_get(&dev_priv->runtime_pm);

	seq_printf(m, "fw loaded: %s\n", yesno(csr->dmc_payload != NULL));
	seq_printf(m, "path: %s\n", csr->fw_path);

	if (!csr->dmc_payload)
		goto out;

	seq_printf(m, "version: %d.%d\n", CSR_VERSION_MAJOR(csr->version),
		   CSR_VERSION_MINOR(csr->version));

	if (INTEL_GEN(dev_priv) >= 12) {
		dc5_reg = TGL_DMC_DEBUG_DC5_COUNT;
		dc6_reg = TGL_DMC_DEBUG_DC6_COUNT;
	} else {
		dc5_reg = IS_BROXTON(dev_priv) ? BXT_CSR_DC3_DC5_COUNT :
						 SKL_CSR_DC3_DC5_COUNT;
		if (!IS_GEN9_LP(dev_priv))
			dc6_reg = SKL_CSR_DC5_DC6_COUNT;
	}

	seq_printf(m, "DC3 -> DC5 count: %d\n", I915_READ(dc5_reg));
	if (dc6_reg.reg)
		seq_printf(m, "DC5 -> DC6 count: %d\n", I915_READ(dc6_reg));

out:
	seq_printf(m, "program base: 0x%08x\n", I915_READ(CSR_PROGRAM(0)));
	seq_printf(m, "ssp base: 0x%08x\n", I915_READ(CSR_SSP_BASE));
	seq_printf(m, "htp: 0x%08x\n", I915_READ(CSR_HTP_SKL));

	intel_runtime_pm_put(&dev_priv->runtime_pm, wakeref);

	return 0;
}