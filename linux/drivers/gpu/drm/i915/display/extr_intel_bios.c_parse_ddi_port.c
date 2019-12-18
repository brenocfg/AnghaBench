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
typedef  int u8 ;
struct TYPE_2__ {struct ddi_vbt_port_info* ddi_port_info; } ;
struct drm_i915_private {TYPE_1__ vbt; } ;
struct ddi_vbt_port_info {int supports_dvi; int supports_hdmi; int supports_dp; int supports_edp; int alternate_ddc_pin; int hdmi_level_shift; int max_tmds_clock; int dp_boost_level; int hdmi_boost_level; int dp_max_link_rate; struct child_device_config const* child; int /*<<< orphan*/  alternate_aux_channel; int /*<<< orphan*/  supports_tbt; int /*<<< orphan*/  supports_typec_usb; } ;
struct child_device_config {int device_type; int hdmi_level_shifter_value; int hdmi_max_data_rate; int dp_max_link_rate; int /*<<< orphan*/  hdmi_iboost_level; int /*<<< orphan*/  dp_iboost_level; scalar_t__ iboost; int /*<<< orphan*/  aux_channel; int /*<<< orphan*/  ddc_pin; scalar_t__ lspcon; int /*<<< orphan*/  tbt; int /*<<< orphan*/  dp_usb_type_c; int /*<<< orphan*/  dvo_port; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int DEVICE_TYPE_ANALOG_OUTPUT ; 
 int DEVICE_TYPE_DISPLAYPORT_OUTPUT ; 
 int DEVICE_TYPE_INTERNAL_CONNECTOR ; 
 int DEVICE_TYPE_NOT_HDMI_OUTPUT ; 
 int DEVICE_TYPE_TMDS_DVI_SIGNALING ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,char*,...) ; 
 scalar_t__ HAS_LSPCON (struct drm_i915_private*) ; 
#define  HDMI_MAX_DATA_RATE_165 134 
#define  HDMI_MAX_DATA_RATE_297 133 
#define  HDMI_MAX_DATA_RATE_PLATFORM 132 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int PORT_A ; 
 int PORT_B ; 
 int PORT_C ; 
 int PORT_E ; 
 int PORT_NONE ; 
#define  VBT_DP_MAX_LINK_RATE_HBR 131 
#define  VBT_DP_MAX_LINK_RATE_HBR2 130 
#define  VBT_DP_MAX_LINK_RATE_HBR3 129 
#define  VBT_DP_MAX_LINK_RATE_LBR 128 
 int dvo_port_to_port (int /*<<< orphan*/ ) ; 
 scalar_t__ intel_gmbus_is_valid_pin (struct drm_i915_private*,int) ; 
 int map_ddc_pin (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_name (int) ; 
 int /*<<< orphan*/  sanitize_aux_ch (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  sanitize_ddc_pin (struct drm_i915_private*,int) ; 
 void* translate_iboost (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_ddi_port(struct drm_i915_private *dev_priv,
			   const struct child_device_config *child,
			   u8 bdb_version)
{
	struct ddi_vbt_port_info *info;
	bool is_dvi, is_hdmi, is_dp, is_edp, is_crt;
	enum port port;

	port = dvo_port_to_port(child->dvo_port);
	if (port == PORT_NONE)
		return;

	info = &dev_priv->vbt.ddi_port_info[port];

	if (info->child) {
		DRM_DEBUG_KMS("More than one child device for port %c in VBT, using the first.\n",
			      port_name(port));
		return;
	}

	is_dvi = child->device_type & DEVICE_TYPE_TMDS_DVI_SIGNALING;
	is_dp = child->device_type & DEVICE_TYPE_DISPLAYPORT_OUTPUT;
	is_crt = child->device_type & DEVICE_TYPE_ANALOG_OUTPUT;
	is_hdmi = is_dvi && (child->device_type & DEVICE_TYPE_NOT_HDMI_OUTPUT) == 0;
	is_edp = is_dp && (child->device_type & DEVICE_TYPE_INTERNAL_CONNECTOR);

	if (port == PORT_A && is_dvi) {
		DRM_DEBUG_KMS("VBT claims port A supports DVI%s, ignoring\n",
			      is_hdmi ? "/HDMI" : "");
		is_dvi = false;
		is_hdmi = false;
	}

	info->supports_dvi = is_dvi;
	info->supports_hdmi = is_hdmi;
	info->supports_dp = is_dp;
	info->supports_edp = is_edp;

	if (bdb_version >= 195)
		info->supports_typec_usb = child->dp_usb_type_c;

	if (bdb_version >= 209)
		info->supports_tbt = child->tbt;

	DRM_DEBUG_KMS("Port %c VBT info: CRT:%d DVI:%d HDMI:%d DP:%d eDP:%d LSPCON:%d USB-Type-C:%d TBT:%d\n",
		      port_name(port), is_crt, is_dvi, is_hdmi, is_dp, is_edp,
		      HAS_LSPCON(dev_priv) && child->lspcon,
		      info->supports_typec_usb, info->supports_tbt);

	if (is_edp && is_dvi)
		DRM_DEBUG_KMS("Internal DP port %c is TMDS compatible\n",
			      port_name(port));
	if (is_crt && port != PORT_E)
		DRM_DEBUG_KMS("Port %c is analog\n", port_name(port));
	if (is_crt && (is_dvi || is_dp))
		DRM_DEBUG_KMS("Analog port %c is also DP or TMDS compatible\n",
			      port_name(port));
	if (is_dvi && (port == PORT_A || port == PORT_E))
		DRM_DEBUG_KMS("Port %c is TMDS compatible\n", port_name(port));
	if (!is_dvi && !is_dp && !is_crt)
		DRM_DEBUG_KMS("Port %c is not DP/TMDS/CRT compatible\n",
			      port_name(port));
	if (is_edp && (port == PORT_B || port == PORT_C || port == PORT_E))
		DRM_DEBUG_KMS("Port %c is internal DP\n", port_name(port));

	if (is_dvi) {
		u8 ddc_pin;

		ddc_pin = map_ddc_pin(dev_priv, child->ddc_pin);
		if (intel_gmbus_is_valid_pin(dev_priv, ddc_pin)) {
			info->alternate_ddc_pin = ddc_pin;
			sanitize_ddc_pin(dev_priv, port);
		} else {
			DRM_DEBUG_KMS("Port %c has invalid DDC pin %d, "
				      "sticking to defaults\n",
				      port_name(port), ddc_pin);
		}
	}

	if (is_dp) {
		info->alternate_aux_channel = child->aux_channel;

		sanitize_aux_ch(dev_priv, port);
	}

	if (bdb_version >= 158) {
		/* The VBT HDMI level shift values match the table we have. */
		u8 hdmi_level_shift = child->hdmi_level_shifter_value;
		DRM_DEBUG_KMS("VBT HDMI level shift for port %c: %d\n",
			      port_name(port),
			      hdmi_level_shift);
		info->hdmi_level_shift = hdmi_level_shift;
	}

	if (bdb_version >= 204) {
		int max_tmds_clock;

		switch (child->hdmi_max_data_rate) {
		default:
			MISSING_CASE(child->hdmi_max_data_rate);
			/* fall through */
		case HDMI_MAX_DATA_RATE_PLATFORM:
			max_tmds_clock = 0;
			break;
		case HDMI_MAX_DATA_RATE_297:
			max_tmds_clock = 297000;
			break;
		case HDMI_MAX_DATA_RATE_165:
			max_tmds_clock = 165000;
			break;
		}

		if (max_tmds_clock)
			DRM_DEBUG_KMS("VBT HDMI max TMDS clock for port %c: %d kHz\n",
				      port_name(port), max_tmds_clock);
		info->max_tmds_clock = max_tmds_clock;
	}

	/* Parse the I_boost config for SKL and above */
	if (bdb_version >= 196 && child->iboost) {
		info->dp_boost_level = translate_iboost(child->dp_iboost_level);
		DRM_DEBUG_KMS("VBT (e)DP boost level for port %c: %d\n",
			      port_name(port), info->dp_boost_level);
		info->hdmi_boost_level = translate_iboost(child->hdmi_iboost_level);
		DRM_DEBUG_KMS("VBT HDMI boost level for port %c: %d\n",
			      port_name(port), info->hdmi_boost_level);
	}

	/* DP max link rate for CNL+ */
	if (bdb_version >= 216) {
		switch (child->dp_max_link_rate) {
		default:
		case VBT_DP_MAX_LINK_RATE_HBR3:
			info->dp_max_link_rate = 810000;
			break;
		case VBT_DP_MAX_LINK_RATE_HBR2:
			info->dp_max_link_rate = 540000;
			break;
		case VBT_DP_MAX_LINK_RATE_HBR:
			info->dp_max_link_rate = 270000;
			break;
		case VBT_DP_MAX_LINK_RATE_LBR:
			info->dp_max_link_rate = 162000;
			break;
		}
		DRM_DEBUG_KMS("VBT DP max link rate for port %c: %d\n",
			      port_name(port), info->dp_max_link_rate);
	}

	info->child = child;
}