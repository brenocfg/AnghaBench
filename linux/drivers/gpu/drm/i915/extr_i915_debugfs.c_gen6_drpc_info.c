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
typedef  int u32 ;
struct seq_file {int /*<<< orphan*/  private; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int GEN6_CORE_CPD_STATE_MASK ; 
 char* GEN6_DECODE_RC6_VID (int) ; 
 int /*<<< orphan*/  GEN6_GT_CORE_STATUS ; 
 int /*<<< orphan*/  GEN6_GT_GFX_RC6 ; 
 int /*<<< orphan*/  GEN6_GT_GFX_RC6_LOCKED ; 
 int /*<<< orphan*/  GEN6_GT_GFX_RC6p ; 
 int /*<<< orphan*/  GEN6_GT_GFX_RC6pp ; 
 int /*<<< orphan*/  GEN6_PCODE_READ_RC6VIDS ; 
#define  GEN6_RC0 131 
#define  GEN6_RC3 130 
#define  GEN6_RC6 129 
#define  GEN6_RC7 128 
 int /*<<< orphan*/  GEN6_RC_CONTROL ; 
 int GEN6_RC_CTL_RC1e_ENABLE ; 
 int GEN6_RC_CTL_RC6_ENABLE ; 
 int GEN6_RC_CTL_RC6p_ENABLE ; 
 int GEN6_RC_CTL_RC6pp_ENABLE ; 
 int GEN6_RCn_MASK ; 
 int GEN9_MEDIA_PG_ENABLE ; 
 int /*<<< orphan*/  GEN9_PG_ENABLE ; 
 int /*<<< orphan*/  GEN9_PWRGT_DOMAIN_STATUS ; 
 int GEN9_PWRGT_MEDIA_STATUS_MASK ; 
 int GEN9_PWRGT_RENDER_STATUS_MASK ; 
 int GEN9_RENDER_PG_ENABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int I915_READ_FW (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int i915_forcewake_domains (struct seq_file*,int /*<<< orphan*/ *) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_rc6_res (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sandybridge_pcode_read (struct drm_i915_private*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  trace_i915_reg_rw (int,int /*<<< orphan*/ ,int,int,int) ; 
 char* yesno (int) ; 

__attribute__((used)) static int gen6_drpc_info(struct seq_file *m)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	u32 gt_core_status, rcctl1, rc6vids = 0;
	u32 gen9_powergate_enable = 0, gen9_powergate_status = 0;

	gt_core_status = I915_READ_FW(GEN6_GT_CORE_STATUS);
	trace_i915_reg_rw(false, GEN6_GT_CORE_STATUS, gt_core_status, 4, true);

	rcctl1 = I915_READ(GEN6_RC_CONTROL);
	if (INTEL_GEN(dev_priv) >= 9) {
		gen9_powergate_enable = I915_READ(GEN9_PG_ENABLE);
		gen9_powergate_status = I915_READ(GEN9_PWRGT_DOMAIN_STATUS);
	}

	if (INTEL_GEN(dev_priv) <= 7)
		sandybridge_pcode_read(dev_priv, GEN6_PCODE_READ_RC6VIDS,
				       &rc6vids, NULL);

	seq_printf(m, "RC1e Enabled: %s\n",
		   yesno(rcctl1 & GEN6_RC_CTL_RC1e_ENABLE));
	seq_printf(m, "RC6 Enabled: %s\n",
		   yesno(rcctl1 & GEN6_RC_CTL_RC6_ENABLE));
	if (INTEL_GEN(dev_priv) >= 9) {
		seq_printf(m, "Render Well Gating Enabled: %s\n",
			yesno(gen9_powergate_enable & GEN9_RENDER_PG_ENABLE));
		seq_printf(m, "Media Well Gating Enabled: %s\n",
			yesno(gen9_powergate_enable & GEN9_MEDIA_PG_ENABLE));
	}
	seq_printf(m, "Deep RC6 Enabled: %s\n",
		   yesno(rcctl1 & GEN6_RC_CTL_RC6p_ENABLE));
	seq_printf(m, "Deepest RC6 Enabled: %s\n",
		   yesno(rcctl1 & GEN6_RC_CTL_RC6pp_ENABLE));
	seq_puts(m, "Current RC state: ");
	switch (gt_core_status & GEN6_RCn_MASK) {
	case GEN6_RC0:
		if (gt_core_status & GEN6_CORE_CPD_STATE_MASK)
			seq_puts(m, "Core Power Down\n");
		else
			seq_puts(m, "on\n");
		break;
	case GEN6_RC3:
		seq_puts(m, "RC3\n");
		break;
	case GEN6_RC6:
		seq_puts(m, "RC6\n");
		break;
	case GEN6_RC7:
		seq_puts(m, "RC7\n");
		break;
	default:
		seq_puts(m, "Unknown\n");
		break;
	}

	seq_printf(m, "Core Power Down: %s\n",
		   yesno(gt_core_status & GEN6_CORE_CPD_STATE_MASK));
	if (INTEL_GEN(dev_priv) >= 9) {
		seq_printf(m, "Render Power Well: %s\n",
			(gen9_powergate_status &
			 GEN9_PWRGT_RENDER_STATUS_MASK) ? "Up" : "Down");
		seq_printf(m, "Media Power Well: %s\n",
			(gen9_powergate_status &
			 GEN9_PWRGT_MEDIA_STATUS_MASK) ? "Up" : "Down");
	}

	/* Not exactly sure what this is */
	print_rc6_res(m, "RC6 \"Locked to RPn\" residency since boot:",
		      GEN6_GT_GFX_RC6_LOCKED);
	print_rc6_res(m, "RC6 residency since boot:", GEN6_GT_GFX_RC6);
	print_rc6_res(m, "RC6+ residency since boot:", GEN6_GT_GFX_RC6p);
	print_rc6_res(m, "RC6++ residency since boot:", GEN6_GT_GFX_RC6pp);

	if (INTEL_GEN(dev_priv) <= 7) {
		seq_printf(m, "RC6   voltage: %dmV\n",
			   GEN6_DECODE_RC6_VID(((rc6vids >> 0) & 0xff)));
		seq_printf(m, "RC6+  voltage: %dmV\n",
			   GEN6_DECODE_RC6_VID(((rc6vids >> 8) & 0xff)));
		seq_printf(m, "RC6++ voltage: %dmV\n",
			   GEN6_DECODE_RC6_VID(((rc6vids >> 16) & 0xff)));
	}

	return i915_forcewake_domains(m, NULL);
}