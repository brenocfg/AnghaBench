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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct TYPE_6__ {TYPE_2__* ddi_port_info; } ;
struct drm_i915_private {TYPE_3__ vbt; } ;
struct ddi_buf_trans {int trans1; int trans2; } ;
typedef  enum port { ____Placeholder_port } port ;
struct TYPE_5__ {scalar_t__ dp_boost_level; } ;

/* Variables and functions */
 int DDI_BUF_BALANCE_LEG_ENABLE ; 
 int /*<<< orphan*/  DDI_BUF_TRANS_HI (int,int) ; 
 int /*<<< orphan*/  DDI_BUF_TRANS_LO (int,int) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_ANALOG ; 
 int /*<<< orphan*/  INTEL_OUTPUT_EDP ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state const*,int /*<<< orphan*/ ) ; 
 struct ddi_buf_trans* intel_ddi_get_buf_trans_dp (struct drm_i915_private*,int,int*) ; 
 struct ddi_buf_trans* intel_ddi_get_buf_trans_edp (struct drm_i915_private*,int,int*) ; 
 struct ddi_buf_trans* intel_ddi_get_buf_trans_fdi (struct drm_i915_private*,int*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_prepare_dp_ddi_buffers(struct intel_encoder *encoder,
					 const struct intel_crtc_state *crtc_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	u32 iboost_bit = 0;
	int i, n_entries;
	enum port port = encoder->port;
	const struct ddi_buf_trans *ddi_translations;

	if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_ANALOG))
		ddi_translations = intel_ddi_get_buf_trans_fdi(dev_priv,
							       &n_entries);
	else if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_EDP))
		ddi_translations = intel_ddi_get_buf_trans_edp(dev_priv, port,
							       &n_entries);
	else
		ddi_translations = intel_ddi_get_buf_trans_dp(dev_priv, port,
							      &n_entries);

	/* If we're boosting the current, set bit 31 of trans1 */
	if (IS_GEN9_BC(dev_priv) &&
	    dev_priv->vbt.ddi_port_info[port].dp_boost_level)
		iboost_bit = DDI_BUF_BALANCE_LEG_ENABLE;

	for (i = 0; i < n_entries; i++) {
		I915_WRITE(DDI_BUF_TRANS_LO(port, i),
			   ddi_translations[i].trans1 | iboost_bit);
		I915_WRITE(DDI_BUF_TRANS_HI(port, i),
			   ddi_translations[i].trans2);
	}
}