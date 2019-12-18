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
 int /*<<< orphan*/  GEN6_RC_CONTROL ; 
 int GEN6_RC_CTL_EI_MODE (int) ; 
 int GEN7_RC_CTL_TO_MODE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int VLV_GTLC_PW_MEDIA_STATUS_MASK ; 
 int VLV_GTLC_PW_RENDER_STATUS_MASK ; 
 int /*<<< orphan*/  VLV_GTLC_PW_STATUS ; 
 int /*<<< orphan*/  VLV_GT_MEDIA_RC6 ; 
 int /*<<< orphan*/  VLV_GT_RENDER_RC6 ; 
 int i915_forcewake_domains (struct seq_file*,int /*<<< orphan*/ *) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_rc6_res (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 
 char* yesno (int) ; 

__attribute__((used)) static int vlv_drpc_info(struct seq_file *m)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	u32 rcctl1, pw_status;

	pw_status = I915_READ(VLV_GTLC_PW_STATUS);
	rcctl1 = I915_READ(GEN6_RC_CONTROL);

	seq_printf(m, "RC6 Enabled: %s\n",
		   yesno(rcctl1 & (GEN7_RC_CTL_TO_MODE |
					GEN6_RC_CTL_EI_MODE(1))));
	seq_printf(m, "Render Power Well: %s\n",
		   (pw_status & VLV_GTLC_PW_RENDER_STATUS_MASK) ? "Up" : "Down");
	seq_printf(m, "Media Power Well: %s\n",
		   (pw_status & VLV_GTLC_PW_MEDIA_STATUS_MASK) ? "Up" : "Down");

	print_rc6_res(m, "Render RC6 residency since boot:", VLV_GT_RENDER_RC6);
	print_rc6_res(m, "Media RC6 residency since boot:", VLV_GT_MEDIA_RC6);

	return i915_forcewake_domains(m, NULL);
}