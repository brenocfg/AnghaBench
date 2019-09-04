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
struct drm_printer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fw; } ;
struct drm_i915_private {TYPE_1__ huc; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HAS_HUC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HUC_STATUS2 ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 struct drm_printer drm_seq_file_printer (struct seq_file*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_fw_dump (int /*<<< orphan*/ *,struct drm_printer*) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_huc_load_status_info(struct seq_file *m, void *data)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	struct drm_printer p;

	if (!HAS_HUC(dev_priv))
		return -ENODEV;

	p = drm_seq_file_printer(m);
	intel_uc_fw_dump(&dev_priv->huc.fw, &p);

	intel_runtime_pm_get(dev_priv);
	seq_printf(m, "\nHuC status 0x%08x:\n", I915_READ(HUC_STATUS2));
	intel_runtime_pm_put(dev_priv);

	return 0;
}