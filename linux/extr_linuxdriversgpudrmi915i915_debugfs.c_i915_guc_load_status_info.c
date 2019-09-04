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
typedef  int u32 ;
struct seq_file {int /*<<< orphan*/  private; } ;
struct drm_printer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fw; } ;
struct drm_i915_private {TYPE_1__ guc; } ;

/* Variables and functions */
 int ENODEV ; 
 int GS_BOOTROM_MASK ; 
 int GS_BOOTROM_SHIFT ; 
 int GS_MIA_MASK ; 
 int GS_MIA_SHIFT ; 
 int GS_UKERNEL_MASK ; 
 int GS_UKERNEL_SHIFT ; 
 int /*<<< orphan*/  GUC_STATUS ; 
 int /*<<< orphan*/  HAS_GUC (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOFT_SCRATCH (int) ; 
 struct drm_printer drm_seq_file_printer (struct seq_file*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_fw_dump (int /*<<< orphan*/ *,struct drm_printer*) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int i915_guc_load_status_info(struct seq_file *m, void *data)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	struct drm_printer p;
	u32 tmp, i;

	if (!HAS_GUC(dev_priv))
		return -ENODEV;

	p = drm_seq_file_printer(m);
	intel_uc_fw_dump(&dev_priv->guc.fw, &p);

	intel_runtime_pm_get(dev_priv);

	tmp = I915_READ(GUC_STATUS);

	seq_printf(m, "\nGuC status 0x%08x:\n", tmp);
	seq_printf(m, "\tBootrom status = 0x%x\n",
		(tmp & GS_BOOTROM_MASK) >> GS_BOOTROM_SHIFT);
	seq_printf(m, "\tuKernel status = 0x%x\n",
		(tmp & GS_UKERNEL_MASK) >> GS_UKERNEL_SHIFT);
	seq_printf(m, "\tMIA Core status = 0x%x\n",
		(tmp & GS_MIA_MASK) >> GS_MIA_SHIFT);
	seq_puts(m, "\nScratch registers:\n");
	for (i = 0; i < 16; i++)
		seq_printf(m, "\t%2d: \t0x%x\n", i, I915_READ(SOFT_SCRATCH(i)));

	intel_runtime_pm_put(dev_priv);

	return 0;
}