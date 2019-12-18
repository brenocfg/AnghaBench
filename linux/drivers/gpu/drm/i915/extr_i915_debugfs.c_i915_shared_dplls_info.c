#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int /*<<< orphan*/  private; } ;
struct TYPE_5__ {int /*<<< orphan*/  mg_pll_tdc_coldst_bias; int /*<<< orphan*/  mg_pll_bias; int /*<<< orphan*/  mg_pll_ssc; int /*<<< orphan*/  mg_pll_frac_lock; int /*<<< orphan*/  mg_pll_lf; int /*<<< orphan*/  mg_pll_div1; int /*<<< orphan*/  mg_pll_div0; int /*<<< orphan*/  mg_clktop2_hsclkctl; int /*<<< orphan*/  mg_clktop2_coreclkctl1; int /*<<< orphan*/  mg_refclkin_ctl; int /*<<< orphan*/  cfgcr1; int /*<<< orphan*/  cfgcr0; int /*<<< orphan*/  wrpll; int /*<<< orphan*/  fp1; int /*<<< orphan*/  fp0; int /*<<< orphan*/  dpll_md; int /*<<< orphan*/  dpll; } ;
struct TYPE_6__ {TYPE_2__ hw_state; int /*<<< orphan*/  crtc_mask; } ;
struct intel_shared_dpll {TYPE_3__ state; int /*<<< orphan*/  on; int /*<<< orphan*/  active_mask; TYPE_1__* info; } ;
struct drm_device {int dummy; } ;
struct drm_i915_private {int num_shared_dpll; struct intel_shared_dpll* shared_dplls; struct drm_device drm; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  yesno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_shared_dplls_info(struct seq_file *m, void *unused)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	struct drm_device *dev = &dev_priv->drm;
	int i;

	drm_modeset_lock_all(dev);
	for (i = 0; i < dev_priv->num_shared_dpll; i++) {
		struct intel_shared_dpll *pll = &dev_priv->shared_dplls[i];

		seq_printf(m, "DPLL%i: %s, id: %i\n", i, pll->info->name,
			   pll->info->id);
		seq_printf(m, " crtc_mask: 0x%08x, active: 0x%x, on: %s\n",
			   pll->state.crtc_mask, pll->active_mask, yesno(pll->on));
		seq_printf(m, " tracked hardware state:\n");
		seq_printf(m, " dpll:    0x%08x\n", pll->state.hw_state.dpll);
		seq_printf(m, " dpll_md: 0x%08x\n",
			   pll->state.hw_state.dpll_md);
		seq_printf(m, " fp0:     0x%08x\n", pll->state.hw_state.fp0);
		seq_printf(m, " fp1:     0x%08x\n", pll->state.hw_state.fp1);
		seq_printf(m, " wrpll:   0x%08x\n", pll->state.hw_state.wrpll);
		seq_printf(m, " cfgcr0:  0x%08x\n", pll->state.hw_state.cfgcr0);
		seq_printf(m, " cfgcr1:  0x%08x\n", pll->state.hw_state.cfgcr1);
		seq_printf(m, " mg_refclkin_ctl:        0x%08x\n",
			   pll->state.hw_state.mg_refclkin_ctl);
		seq_printf(m, " mg_clktop2_coreclkctl1: 0x%08x\n",
			   pll->state.hw_state.mg_clktop2_coreclkctl1);
		seq_printf(m, " mg_clktop2_hsclkctl:    0x%08x\n",
			   pll->state.hw_state.mg_clktop2_hsclkctl);
		seq_printf(m, " mg_pll_div0:  0x%08x\n",
			   pll->state.hw_state.mg_pll_div0);
		seq_printf(m, " mg_pll_div1:  0x%08x\n",
			   pll->state.hw_state.mg_pll_div1);
		seq_printf(m, " mg_pll_lf:    0x%08x\n",
			   pll->state.hw_state.mg_pll_lf);
		seq_printf(m, " mg_pll_frac_lock: 0x%08x\n",
			   pll->state.hw_state.mg_pll_frac_lock);
		seq_printf(m, " mg_pll_ssc:   0x%08x\n",
			   pll->state.hw_state.mg_pll_ssc);
		seq_printf(m, " mg_pll_bias:  0x%08x\n",
			   pll->state.hw_state.mg_pll_bias);
		seq_printf(m, " mg_pll_tdc_coldst_bias: 0x%08x\n",
			   pll->state.hw_state.mg_pll_tdc_coldst_bias);
	}
	drm_modeset_unlock_all(dev);

	return 0;
}