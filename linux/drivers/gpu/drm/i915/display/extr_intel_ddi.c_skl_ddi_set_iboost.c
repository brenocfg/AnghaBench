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
typedef  int u8 ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; TYPE_3__ base; } ;
struct intel_digital_port {int max_lanes; } ;
struct TYPE_5__ {TYPE_1__* ddi_port_info; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;
struct ddi_buf_trans {int i_boost; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum intel_output_type { ____Placeholder_intel_output_type } intel_output_type ;
struct TYPE_4__ {int hdmi_boost_level; int dp_boost_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int INTEL_OUTPUT_EDP ; 
 int INTEL_OUTPUT_HDMI ; 
 int PORT_A ; 
 int PORT_E ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  _skl_ddi_set_iboost (struct drm_i915_private*,int,int) ; 
 struct intel_digital_port* enc_to_dig_port (TYPE_3__*) ; 
 struct ddi_buf_trans* intel_ddi_get_buf_trans_dp (struct drm_i915_private*,int,int*) ; 
 struct ddi_buf_trans* intel_ddi_get_buf_trans_edp (struct drm_i915_private*,int,int*) ; 
 struct ddi_buf_trans* intel_ddi_get_buf_trans_hdmi (struct drm_i915_private*,int*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skl_ddi_set_iboost(struct intel_encoder *encoder,
			       int level, enum intel_output_type type)
{
	struct intel_digital_port *intel_dig_port = enc_to_dig_port(&encoder->base);
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	enum port port = encoder->port;
	u8 iboost;

	if (type == INTEL_OUTPUT_HDMI)
		iboost = dev_priv->vbt.ddi_port_info[port].hdmi_boost_level;
	else
		iboost = dev_priv->vbt.ddi_port_info[port].dp_boost_level;

	if (iboost == 0) {
		const struct ddi_buf_trans *ddi_translations;
		int n_entries;

		if (type == INTEL_OUTPUT_HDMI)
			ddi_translations = intel_ddi_get_buf_trans_hdmi(dev_priv, &n_entries);
		else if (type == INTEL_OUTPUT_EDP)
			ddi_translations = intel_ddi_get_buf_trans_edp(dev_priv, port, &n_entries);
		else
			ddi_translations = intel_ddi_get_buf_trans_dp(dev_priv, port, &n_entries);

		if (WARN_ON_ONCE(!ddi_translations))
			return;
		if (WARN_ON_ONCE(level >= n_entries))
			level = n_entries - 1;

		iboost = ddi_translations[level].i_boost;
	}

	/* Make sure that the requested I_boost is valid */
	if (iboost && iboost != 0x1 && iboost != 0x3 && iboost != 0x7) {
		DRM_ERROR("Invalid I_boost value %u\n", iboost);
		return;
	}

	_skl_ddi_set_iboost(dev_priv, port, iboost);

	if (port == PORT_A && intel_dig_port->max_lanes == 4)
		_skl_ddi_set_iboost(dev_priv, PORT_E, iboost);
}