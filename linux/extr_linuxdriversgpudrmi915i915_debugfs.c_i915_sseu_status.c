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
struct sseu_dev_info {int /*<<< orphan*/  max_eus_per_subslice; int /*<<< orphan*/  max_subslices; int /*<<< orphan*/  max_slices; } ;
struct seq_file {int /*<<< orphan*/  private; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  sseu ;
struct TYPE_2__ {struct sseu_dev_info sseu; } ;

/* Variables and functions */
 int ENODEV ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 TYPE_1__* INTEL_INFO (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  broadwell_sseu_device_status (struct drm_i915_private*,struct sseu_dev_info*) ; 
 int /*<<< orphan*/  cherryview_sseu_device_status (struct drm_i915_private*,struct sseu_dev_info*) ; 
 int /*<<< orphan*/  gen10_sseu_device_status (struct drm_i915_private*,struct sseu_dev_info*) ; 
 int /*<<< orphan*/  gen9_sseu_device_status (struct drm_i915_private*,struct sseu_dev_info*) ; 
 int /*<<< orphan*/  i915_print_sseu_info (struct seq_file*,int,struct sseu_dev_info*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  memset (struct sseu_dev_info*,int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int i915_sseu_status(struct seq_file *m, void *unused)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	struct sseu_dev_info sseu;

	if (INTEL_GEN(dev_priv) < 8)
		return -ENODEV;

	seq_puts(m, "SSEU Device Info\n");
	i915_print_sseu_info(m, true, &INTEL_INFO(dev_priv)->sseu);

	seq_puts(m, "SSEU Device Status\n");
	memset(&sseu, 0, sizeof(sseu));
	sseu.max_slices = INTEL_INFO(dev_priv)->sseu.max_slices;
	sseu.max_subslices = INTEL_INFO(dev_priv)->sseu.max_subslices;
	sseu.max_eus_per_subslice =
		INTEL_INFO(dev_priv)->sseu.max_eus_per_subslice;

	intel_runtime_pm_get(dev_priv);

	if (IS_CHERRYVIEW(dev_priv)) {
		cherryview_sseu_device_status(dev_priv, &sseu);
	} else if (IS_BROADWELL(dev_priv)) {
		broadwell_sseu_device_status(dev_priv, &sseu);
	} else if (IS_GEN9(dev_priv)) {
		gen9_sseu_device_status(dev_priv, &sseu);
	} else if (INTEL_GEN(dev_priv) >= 10) {
		gen10_sseu_device_status(dev_priv, &sseu);
	}

	intel_runtime_pm_put(dev_priv);

	i915_print_sseu_info(m, false, &sseu);

	return 0;
}