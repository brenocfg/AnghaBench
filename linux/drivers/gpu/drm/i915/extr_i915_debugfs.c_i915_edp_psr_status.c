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
struct i915_psr {int debug; int /*<<< orphan*/  lock; scalar_t__ psr2_enabled; int /*<<< orphan*/  last_exit; int /*<<< orphan*/  last_entry_attempt; int /*<<< orphan*/  busy_frontbuffer_bits; scalar_t__ enabled; int /*<<< orphan*/  sink_support; TYPE_1__* dp; } ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; struct i915_psr psr; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;
struct TYPE_2__ {int /*<<< orphan*/ * psr_dpcd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDP_PSR2_CTL ; 
 int EDP_PSR2_ENABLE ; 
 int /*<<< orphan*/  EDP_PSR_CTL ; 
 int EDP_PSR_ENABLE ; 
 int /*<<< orphan*/  EDP_PSR_PERF_CNT ; 
 int EDP_PSR_PERF_CNT_MASK ; 
 int ENODEV ; 
 int /*<<< orphan*/  HAS_PSR (struct drm_i915_private*) ; 
 int I915_PSR_DEBUG_IRQ ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PSR2_SU_STATUS (int) ; 
 int PSR2_SU_STATUS_FRAMES ; 
 int PSR2_SU_STATUS_MASK (int) ; 
 int PSR2_SU_STATUS_SHIFT (int) ; 
 int enableddisabled (int) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psr_source_status (struct drm_i915_private*,struct seq_file*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  yesno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_edp_psr_status(struct seq_file *m, void *data)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	struct i915_psr *psr = &dev_priv->psr;
	intel_wakeref_t wakeref;
	const char *status;
	bool enabled;
	u32 val;

	if (!HAS_PSR(dev_priv))
		return -ENODEV;

	seq_printf(m, "Sink support: %s", yesno(psr->sink_support));
	if (psr->dp)
		seq_printf(m, " [0x%02x]", psr->dp->psr_dpcd[0]);
	seq_puts(m, "\n");

	if (!psr->sink_support)
		return 0;

	wakeref = intel_runtime_pm_get(&dev_priv->runtime_pm);
	mutex_lock(&psr->lock);

	if (psr->enabled)
		status = psr->psr2_enabled ? "PSR2 enabled" : "PSR1 enabled";
	else
		status = "disabled";
	seq_printf(m, "PSR mode: %s\n", status);

	if (!psr->enabled)
		goto unlock;

	if (psr->psr2_enabled) {
		val = I915_READ(EDP_PSR2_CTL);
		enabled = val & EDP_PSR2_ENABLE;
	} else {
		val = I915_READ(EDP_PSR_CTL);
		enabled = val & EDP_PSR_ENABLE;
	}
	seq_printf(m, "Source PSR ctl: %s [0x%08x]\n",
		   enableddisabled(enabled), val);
	psr_source_status(dev_priv, m);
	seq_printf(m, "Busy frontbuffer bits: 0x%08x\n",
		   psr->busy_frontbuffer_bits);

	/*
	 * SKL+ Perf counter is reset to 0 everytime DC state is entered
	 */
	if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) {
		val = I915_READ(EDP_PSR_PERF_CNT) & EDP_PSR_PERF_CNT_MASK;
		seq_printf(m, "Performance counter: %u\n", val);
	}

	if (psr->debug & I915_PSR_DEBUG_IRQ) {
		seq_printf(m, "Last attempted entry at: %lld\n",
			   psr->last_entry_attempt);
		seq_printf(m, "Last exit at: %lld\n", psr->last_exit);
	}

	if (psr->psr2_enabled) {
		u32 su_frames_val[3];
		int frame;

		/*
		 * Reading all 3 registers before hand to minimize crossing a
		 * frame boundary between register reads
		 */
		for (frame = 0; frame < PSR2_SU_STATUS_FRAMES; frame += 3)
			su_frames_val[frame / 3] = I915_READ(PSR2_SU_STATUS(frame));

		seq_puts(m, "Frame:\tPSR2 SU blocks:\n");

		for (frame = 0; frame < PSR2_SU_STATUS_FRAMES; frame++) {
			u32 su_blocks;

			su_blocks = su_frames_val[frame / 3] &
				    PSR2_SU_STATUS_MASK(frame);
			su_blocks = su_blocks >> PSR2_SU_STATUS_SHIFT(frame);
			seq_printf(m, "%d\t%d\n", frame, su_blocks);
		}
	}

unlock:
	mutex_unlock(&psr->lock);
	intel_runtime_pm_put(&dev_priv->runtime_pm, wakeref);

	return 0;
}