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
struct seq_file {int /*<<< orphan*/  private; } ;
struct intel_csr {scalar_t__ version; int /*<<< orphan*/ * dmc_payload; int /*<<< orphan*/  fw_path; } ;
struct drm_i915_private {struct intel_csr csr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXT_CSR_DC3_DC5_COUNT ; 
 int /*<<< orphan*/  CSR_HTP_SKL ; 
 int /*<<< orphan*/  CSR_PROGRAM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_SSP_BASE ; 
 scalar_t__ CSR_VERSION (int,int) ; 
 int /*<<< orphan*/  CSR_VERSION_MAJOR (scalar_t__) ; 
 int /*<<< orphan*/  CSR_VERSION_MINOR (scalar_t__) ; 
 int ENODEV ; 
 int /*<<< orphan*/  HAS_CSR (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ IS_KABYLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  SKL_CSR_DC3_DC5_COUNT ; 
 int /*<<< orphan*/  SKL_CSR_DC5_DC6_COUNT ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  yesno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_dmc_info(struct seq_file *m, void *unused)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	struct intel_csr *csr;

	if (!HAS_CSR(dev_priv))
		return -ENODEV;

	csr = &dev_priv->csr;

	intel_runtime_pm_get(dev_priv);

	seq_printf(m, "fw loaded: %s\n", yesno(csr->dmc_payload != NULL));
	seq_printf(m, "path: %s\n", csr->fw_path);

	if (!csr->dmc_payload)
		goto out;

	seq_printf(m, "version: %d.%d\n", CSR_VERSION_MAJOR(csr->version),
		   CSR_VERSION_MINOR(csr->version));

	if (IS_KABYLAKE(dev_priv) ||
	    (IS_SKYLAKE(dev_priv) && csr->version >= CSR_VERSION(1, 6))) {
		seq_printf(m, "DC3 -> DC5 count: %d\n",
			   I915_READ(SKL_CSR_DC3_DC5_COUNT));
		seq_printf(m, "DC5 -> DC6 count: %d\n",
			   I915_READ(SKL_CSR_DC5_DC6_COUNT));
	} else if (IS_BROXTON(dev_priv) && csr->version >= CSR_VERSION(1, 4)) {
		seq_printf(m, "DC3 -> DC5 count: %d\n",
			   I915_READ(BXT_CSR_DC3_DC5_COUNT));
	}

out:
	seq_printf(m, "program base: 0x%08x\n", I915_READ(CSR_PROGRAM(0)));
	seq_printf(m, "ssp base: 0x%08x\n", I915_READ(CSR_SSP_BASE));
	seq_printf(m, "htp: 0x%08x\n", I915_READ(CSR_HTP_SKL));

	intel_runtime_pm_put(dev_priv);

	return 0;
}