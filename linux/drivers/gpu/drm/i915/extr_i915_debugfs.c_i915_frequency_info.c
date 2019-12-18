#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct seq_file {int /*<<< orphan*/  private; } ;
struct intel_uncore {int dummy; } ;
struct TYPE_5__ {int up_threshold; int down_threshold; } ;
struct intel_rps {int cur_freq; int max_freq; int min_freq; int idle_freq; int efficient_freq; int pm_intrmsk_mbz; int boost_freq; TYPE_1__ power; } ;
struct TYPE_6__ {int cdclk; } ;
struct TYPE_7__ {TYPE_2__ hw; } ;
struct TYPE_8__ {struct intel_rps rps; } ;
struct drm_i915_private {int mem_freq; int max_cdclk_freq; int max_dotclk_freq; int /*<<< orphan*/  runtime_pm; TYPE_3__ cdclk; struct intel_uncore uncore; TYPE_4__ gt_pm; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 int /*<<< orphan*/  BXT_GT_PERF_STATUS ; 
 int /*<<< orphan*/  BXT_RP_STATE_CAP ; 
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GEN11_GPM_WGBOXPERF_INTR_ENABLE ; 
 int /*<<< orphan*/  GEN11_GPM_WGBOXPERF_INTR_MASK ; 
 int GEN6_CURBSYTAVG_MASK ; 
 int GEN6_CURIAVG_MASK ; 
 int GEN6_CURICONT_MASK ; 
 int /*<<< orphan*/  GEN6_GT_PERF_STATUS ; 
 int /*<<< orphan*/  GEN6_PMIER ; 
 int /*<<< orphan*/  GEN6_PMIIR ; 
 int /*<<< orphan*/  GEN6_PMIMR ; 
 int /*<<< orphan*/  GEN6_PMINTRMSK ; 
 int /*<<< orphan*/  GEN6_PMISR ; 
 int /*<<< orphan*/  GEN6_RPNSWREQ ; 
 int /*<<< orphan*/  GEN6_RPSTAT1 ; 
 int /*<<< orphan*/  GEN6_RP_CONTROL ; 
 int /*<<< orphan*/  GEN6_RP_CUR_DOWN ; 
 int /*<<< orphan*/  GEN6_RP_CUR_DOWN_EI ; 
 int /*<<< orphan*/  GEN6_RP_CUR_UP ; 
 int /*<<< orphan*/  GEN6_RP_CUR_UP_EI ; 
 int /*<<< orphan*/  GEN6_RP_DOWN_THRESHOLD ; 
 int GEN6_RP_ENABLE ; 
 int GEN6_RP_MEDIA_MODE_MASK ; 
 int GEN6_RP_MEDIA_SW_MODE ; 
 int GEN6_RP_MEDIA_TURBO ; 
 int /*<<< orphan*/  GEN6_RP_PREV_DOWN ; 
 int /*<<< orphan*/  GEN6_RP_PREV_UP ; 
 int /*<<< orphan*/  GEN6_RP_STATE_CAP ; 
 int /*<<< orphan*/  GEN6_RP_STATE_LIMITS ; 
 int /*<<< orphan*/  GEN6_RP_UP_THRESHOLD ; 
 int GEN6_TURBO_DISABLE ; 
 int /*<<< orphan*/  GEN8_GT_IER (int) ; 
 int /*<<< orphan*/  GEN8_GT_IIR (int) ; 
 int /*<<< orphan*/  GEN8_GT_IMR (int) ; 
 int /*<<< orphan*/  GEN8_GT_ISR (int) ; 
 int GEN9_FREQ_SCALER ; 
 int /*<<< orphan*/  GT_PM_INTERVAL_TO_US (struct drm_i915_private*,int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MEMSTAT_ILK ; 
 int MEMSTAT_PSTATE_MASK ; 
 int MEMSTAT_PSTATE_SHIFT ; 
 int MEMSTAT_VID_MASK ; 
 int MEMSTAT_VID_SHIFT ; 
 int /*<<< orphan*/  MEMSWCTL ; 
 int /*<<< orphan*/  PUNIT_REG_GPU_FREQ_STS ; 
 int intel_get_cagf (struct drm_i915_private*,int) ; 
 int intel_gpu_freq (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int intel_uncore_read16 (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  vlv_punit_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_punit_put (struct drm_i915_private*) ; 
 int vlv_punit_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int yesno (int) ; 

__attribute__((used)) static int i915_frequency_info(struct seq_file *m, void *unused)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	struct intel_uncore *uncore = &dev_priv->uncore;
	struct intel_rps *rps = &dev_priv->gt_pm.rps;
	intel_wakeref_t wakeref;
	int ret = 0;

	wakeref = intel_runtime_pm_get(&dev_priv->runtime_pm);

	if (IS_GEN(dev_priv, 5)) {
		u16 rgvswctl = intel_uncore_read16(uncore, MEMSWCTL);
		u16 rgvstat = intel_uncore_read16(uncore, MEMSTAT_ILK);

		seq_printf(m, "Requested P-state: %d\n", (rgvswctl >> 8) & 0xf);
		seq_printf(m, "Requested VID: %d\n", rgvswctl & 0x3f);
		seq_printf(m, "Current VID: %d\n", (rgvstat & MEMSTAT_VID_MASK) >>
			   MEMSTAT_VID_SHIFT);
		seq_printf(m, "Current P-state: %d\n",
			   (rgvstat & MEMSTAT_PSTATE_MASK) >> MEMSTAT_PSTATE_SHIFT);
	} else if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		u32 rpmodectl, freq_sts;

		rpmodectl = I915_READ(GEN6_RP_CONTROL);
		seq_printf(m, "Video Turbo Mode: %s\n",
			   yesno(rpmodectl & GEN6_RP_MEDIA_TURBO));
		seq_printf(m, "HW control enabled: %s\n",
			   yesno(rpmodectl & GEN6_RP_ENABLE));
		seq_printf(m, "SW control enabled: %s\n",
			   yesno((rpmodectl & GEN6_RP_MEDIA_MODE_MASK) ==
				  GEN6_RP_MEDIA_SW_MODE));

		vlv_punit_get(dev_priv);
		freq_sts = vlv_punit_read(dev_priv, PUNIT_REG_GPU_FREQ_STS);
		vlv_punit_put(dev_priv);

		seq_printf(m, "PUNIT_REG_GPU_FREQ_STS: 0x%08x\n", freq_sts);
		seq_printf(m, "DDR freq: %d MHz\n", dev_priv->mem_freq);

		seq_printf(m, "actual GPU freq: %d MHz\n",
			   intel_gpu_freq(dev_priv, (freq_sts >> 8) & 0xff));

		seq_printf(m, "current GPU freq: %d MHz\n",
			   intel_gpu_freq(dev_priv, rps->cur_freq));

		seq_printf(m, "max GPU freq: %d MHz\n",
			   intel_gpu_freq(dev_priv, rps->max_freq));

		seq_printf(m, "min GPU freq: %d MHz\n",
			   intel_gpu_freq(dev_priv, rps->min_freq));

		seq_printf(m, "idle GPU freq: %d MHz\n",
			   intel_gpu_freq(dev_priv, rps->idle_freq));

		seq_printf(m,
			   "efficient (RPe) frequency: %d MHz\n",
			   intel_gpu_freq(dev_priv, rps->efficient_freq));
	} else if (INTEL_GEN(dev_priv) >= 6) {
		u32 rp_state_limits;
		u32 gt_perf_status;
		u32 rp_state_cap;
		u32 rpmodectl, rpinclimit, rpdeclimit;
		u32 rpstat, cagf, reqf;
		u32 rpupei, rpcurup, rpprevup;
		u32 rpdownei, rpcurdown, rpprevdown;
		u32 pm_ier, pm_imr, pm_isr, pm_iir, pm_mask;
		int max_freq;

		rp_state_limits = I915_READ(GEN6_RP_STATE_LIMITS);
		if (IS_GEN9_LP(dev_priv)) {
			rp_state_cap = I915_READ(BXT_RP_STATE_CAP);
			gt_perf_status = I915_READ(BXT_GT_PERF_STATUS);
		} else {
			rp_state_cap = I915_READ(GEN6_RP_STATE_CAP);
			gt_perf_status = I915_READ(GEN6_GT_PERF_STATUS);
		}

		/* RPSTAT1 is in the GT power well */
		intel_uncore_forcewake_get(&dev_priv->uncore, FORCEWAKE_ALL);

		reqf = I915_READ(GEN6_RPNSWREQ);
		if (INTEL_GEN(dev_priv) >= 9)
			reqf >>= 23;
		else {
			reqf &= ~GEN6_TURBO_DISABLE;
			if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
				reqf >>= 24;
			else
				reqf >>= 25;
		}
		reqf = intel_gpu_freq(dev_priv, reqf);

		rpmodectl = I915_READ(GEN6_RP_CONTROL);
		rpinclimit = I915_READ(GEN6_RP_UP_THRESHOLD);
		rpdeclimit = I915_READ(GEN6_RP_DOWN_THRESHOLD);

		rpstat = I915_READ(GEN6_RPSTAT1);
		rpupei = I915_READ(GEN6_RP_CUR_UP_EI) & GEN6_CURICONT_MASK;
		rpcurup = I915_READ(GEN6_RP_CUR_UP) & GEN6_CURBSYTAVG_MASK;
		rpprevup = I915_READ(GEN6_RP_PREV_UP) & GEN6_CURBSYTAVG_MASK;
		rpdownei = I915_READ(GEN6_RP_CUR_DOWN_EI) & GEN6_CURIAVG_MASK;
		rpcurdown = I915_READ(GEN6_RP_CUR_DOWN) & GEN6_CURBSYTAVG_MASK;
		rpprevdown = I915_READ(GEN6_RP_PREV_DOWN) & GEN6_CURBSYTAVG_MASK;
		cagf = intel_gpu_freq(dev_priv,
				      intel_get_cagf(dev_priv, rpstat));

		intel_uncore_forcewake_put(&dev_priv->uncore, FORCEWAKE_ALL);

		if (INTEL_GEN(dev_priv) >= 11) {
			pm_ier = I915_READ(GEN11_GPM_WGBOXPERF_INTR_ENABLE);
			pm_imr = I915_READ(GEN11_GPM_WGBOXPERF_INTR_MASK);
			/*
			 * The equivalent to the PM ISR & IIR cannot be read
			 * without affecting the current state of the system
			 */
			pm_isr = 0;
			pm_iir = 0;
		} else if (INTEL_GEN(dev_priv) >= 8) {
			pm_ier = I915_READ(GEN8_GT_IER(2));
			pm_imr = I915_READ(GEN8_GT_IMR(2));
			pm_isr = I915_READ(GEN8_GT_ISR(2));
			pm_iir = I915_READ(GEN8_GT_IIR(2));
		} else {
			pm_ier = I915_READ(GEN6_PMIER);
			pm_imr = I915_READ(GEN6_PMIMR);
			pm_isr = I915_READ(GEN6_PMISR);
			pm_iir = I915_READ(GEN6_PMIIR);
		}
		pm_mask = I915_READ(GEN6_PMINTRMSK);

		seq_printf(m, "Video Turbo Mode: %s\n",
			   yesno(rpmodectl & GEN6_RP_MEDIA_TURBO));
		seq_printf(m, "HW control enabled: %s\n",
			   yesno(rpmodectl & GEN6_RP_ENABLE));
		seq_printf(m, "SW control enabled: %s\n",
			   yesno((rpmodectl & GEN6_RP_MEDIA_MODE_MASK) ==
				  GEN6_RP_MEDIA_SW_MODE));

		seq_printf(m, "PM IER=0x%08x IMR=0x%08x, MASK=0x%08x\n",
			   pm_ier, pm_imr, pm_mask);
		if (INTEL_GEN(dev_priv) <= 10)
			seq_printf(m, "PM ISR=0x%08x IIR=0x%08x\n",
				   pm_isr, pm_iir);
		seq_printf(m, "pm_intrmsk_mbz: 0x%08x\n",
			   rps->pm_intrmsk_mbz);
		seq_printf(m, "GT_PERF_STATUS: 0x%08x\n", gt_perf_status);
		seq_printf(m, "Render p-state ratio: %d\n",
			   (gt_perf_status & (INTEL_GEN(dev_priv) >= 9 ? 0x1ff00 : 0xff00)) >> 8);
		seq_printf(m, "Render p-state VID: %d\n",
			   gt_perf_status & 0xff);
		seq_printf(m, "Render p-state limit: %d\n",
			   rp_state_limits & 0xff);
		seq_printf(m, "RPSTAT1: 0x%08x\n", rpstat);
		seq_printf(m, "RPMODECTL: 0x%08x\n", rpmodectl);
		seq_printf(m, "RPINCLIMIT: 0x%08x\n", rpinclimit);
		seq_printf(m, "RPDECLIMIT: 0x%08x\n", rpdeclimit);
		seq_printf(m, "RPNSWREQ: %dMHz\n", reqf);
		seq_printf(m, "CAGF: %dMHz\n", cagf);
		seq_printf(m, "RP CUR UP EI: %d (%dus)\n",
			   rpupei, GT_PM_INTERVAL_TO_US(dev_priv, rpupei));
		seq_printf(m, "RP CUR UP: %d (%dus)\n",
			   rpcurup, GT_PM_INTERVAL_TO_US(dev_priv, rpcurup));
		seq_printf(m, "RP PREV UP: %d (%dus)\n",
			   rpprevup, GT_PM_INTERVAL_TO_US(dev_priv, rpprevup));
		seq_printf(m, "Up threshold: %d%%\n",
			   rps->power.up_threshold);

		seq_printf(m, "RP CUR DOWN EI: %d (%dus)\n",
			   rpdownei, GT_PM_INTERVAL_TO_US(dev_priv, rpdownei));
		seq_printf(m, "RP CUR DOWN: %d (%dus)\n",
			   rpcurdown, GT_PM_INTERVAL_TO_US(dev_priv, rpcurdown));
		seq_printf(m, "RP PREV DOWN: %d (%dus)\n",
			   rpprevdown, GT_PM_INTERVAL_TO_US(dev_priv, rpprevdown));
		seq_printf(m, "Down threshold: %d%%\n",
			   rps->power.down_threshold);

		max_freq = (IS_GEN9_LP(dev_priv) ? rp_state_cap >> 0 :
			    rp_state_cap >> 16) & 0xff;
		max_freq *= (IS_GEN9_BC(dev_priv) ||
			     INTEL_GEN(dev_priv) >= 10 ? GEN9_FREQ_SCALER : 1);
		seq_printf(m, "Lowest (RPN) frequency: %dMHz\n",
			   intel_gpu_freq(dev_priv, max_freq));

		max_freq = (rp_state_cap & 0xff00) >> 8;
		max_freq *= (IS_GEN9_BC(dev_priv) ||
			     INTEL_GEN(dev_priv) >= 10 ? GEN9_FREQ_SCALER : 1);
		seq_printf(m, "Nominal (RP1) frequency: %dMHz\n",
			   intel_gpu_freq(dev_priv, max_freq));

		max_freq = (IS_GEN9_LP(dev_priv) ? rp_state_cap >> 16 :
			    rp_state_cap >> 0) & 0xff;
		max_freq *= (IS_GEN9_BC(dev_priv) ||
			     INTEL_GEN(dev_priv) >= 10 ? GEN9_FREQ_SCALER : 1);
		seq_printf(m, "Max non-overclocked (RP0) frequency: %dMHz\n",
			   intel_gpu_freq(dev_priv, max_freq));
		seq_printf(m, "Max overclocked frequency: %dMHz\n",
			   intel_gpu_freq(dev_priv, rps->max_freq));

		seq_printf(m, "Current freq: %d MHz\n",
			   intel_gpu_freq(dev_priv, rps->cur_freq));
		seq_printf(m, "Actual freq: %d MHz\n", cagf);
		seq_printf(m, "Idle freq: %d MHz\n",
			   intel_gpu_freq(dev_priv, rps->idle_freq));
		seq_printf(m, "Min freq: %d MHz\n",
			   intel_gpu_freq(dev_priv, rps->min_freq));
		seq_printf(m, "Boost freq: %d MHz\n",
			   intel_gpu_freq(dev_priv, rps->boost_freq));
		seq_printf(m, "Max freq: %d MHz\n",
			   intel_gpu_freq(dev_priv, rps->max_freq));
		seq_printf(m,
			   "efficient (RPe) frequency: %d MHz\n",
			   intel_gpu_freq(dev_priv, rps->efficient_freq));
	} else {
		seq_puts(m, "no P-state info available\n");
	}

	seq_printf(m, "Current CD clock frequency: %d kHz\n", dev_priv->cdclk.hw.cdclk);
	seq_printf(m, "Max CD clock frequency: %d kHz\n", dev_priv->max_cdclk_freq);
	seq_printf(m, "Max pixel clock frequency: %d kHz\n", dev_priv->max_dotclk_freq);

	intel_runtime_pm_put(&dev_priv->runtime_pm, wakeref);
	return ret;
}