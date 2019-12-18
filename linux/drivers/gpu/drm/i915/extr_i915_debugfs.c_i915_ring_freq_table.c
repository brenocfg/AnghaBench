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
struct intel_rps {unsigned int min_freq; unsigned int max_freq; } ;
struct TYPE_2__ {struct intel_rps rps; } ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; TYPE_1__ gt_pm; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GEN6_PCODE_READ_MIN_FREQ_TABLE ; 
 unsigned int GEN9_FREQ_SCALER ; 
 int /*<<< orphan*/  HAS_LLC (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gpu_freq (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sandybridge_pcode_read (struct drm_i915_private*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int i915_ring_freq_table(struct seq_file *m, void *unused)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	struct intel_rps *rps = &dev_priv->gt_pm.rps;
	unsigned int max_gpu_freq, min_gpu_freq;
	intel_wakeref_t wakeref;
	int gpu_freq, ia_freq;

	if (!HAS_LLC(dev_priv))
		return -ENODEV;

	min_gpu_freq = rps->min_freq;
	max_gpu_freq = rps->max_freq;
	if (IS_GEN9_BC(dev_priv) || INTEL_GEN(dev_priv) >= 10) {
		/* Convert GT frequency to 50 HZ units */
		min_gpu_freq /= GEN9_FREQ_SCALER;
		max_gpu_freq /= GEN9_FREQ_SCALER;
	}

	seq_puts(m, "GPU freq (MHz)\tEffective CPU freq (MHz)\tEffective Ring freq (MHz)\n");

	wakeref = intel_runtime_pm_get(&dev_priv->runtime_pm);
	for (gpu_freq = min_gpu_freq; gpu_freq <= max_gpu_freq; gpu_freq++) {
		ia_freq = gpu_freq;
		sandybridge_pcode_read(dev_priv,
				       GEN6_PCODE_READ_MIN_FREQ_TABLE,
				       &ia_freq, NULL);
		seq_printf(m, "%d\t\t%d\t\t\t\t%d\n",
			   intel_gpu_freq(dev_priv, (gpu_freq *
						     (IS_GEN9_BC(dev_priv) ||
						      INTEL_GEN(dev_priv) >= 10 ?
						      GEN9_FREQ_SCALER : 1))),
			   ((ia_freq >> 0) & 0xff) * 100,
			   ((ia_freq >> 8) & 0xff) * 100);
	}
	intel_runtime_pm_put(&dev_priv->runtime_pm, wakeref);

	return 0;
}