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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int gen6_drpc_info (struct seq_file*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int ironlake_drpc_info (struct seq_file*) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int vlv_drpc_info (struct seq_file*) ; 

__attribute__((used)) static int i915_drpc_info(struct seq_file *m, void *unused)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	int err;

	intel_runtime_pm_get(dev_priv);

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		err = vlv_drpc_info(m);
	else if (INTEL_GEN(dev_priv) >= 6)
		err = gen6_drpc_info(m);
	else
		err = ironlake_drpc_info(m);

	intel_runtime_pm_put(dev_priv);

	return err;
}