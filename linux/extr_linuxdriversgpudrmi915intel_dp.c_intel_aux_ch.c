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
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; TYPE_1__ base; } ;
struct intel_dp {int dummy; } ;
struct TYPE_5__ {struct ddi_vbt_port_info* ddi_port_info; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;
struct ddi_vbt_port_info {int alternate_aux_channel; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum aux_ch { ____Placeholder_aux_ch } aux_ch ;
struct TYPE_6__ {struct intel_encoder base; } ;

/* Variables and functions */
 int AUX_CH_A ; 
 int AUX_CH_B ; 
 int AUX_CH_C ; 
 int AUX_CH_D ; 
 int AUX_CH_E ; 
 int AUX_CH_F ; 
#define  DP_AUX_A 133 
#define  DP_AUX_B 132 
#define  DP_AUX_C 131 
#define  DP_AUX_D 130 
#define  DP_AUX_E 129 
#define  DP_AUX_F 128 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  aux_ch_name (int) ; 
 TYPE_3__* dp_to_dig_port (struct intel_dp*) ; 
 int /*<<< orphan*/  port_name (int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum aux_ch intel_aux_ch(struct intel_dp *intel_dp)
{
	struct intel_encoder *encoder = &dp_to_dig_port(intel_dp)->base;
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	enum port port = encoder->port;
	const struct ddi_vbt_port_info *info =
		&dev_priv->vbt.ddi_port_info[port];
	enum aux_ch aux_ch;

	if (!info->alternate_aux_channel) {
		aux_ch = (enum aux_ch) port;

		DRM_DEBUG_KMS("using AUX %c for port %c (platform default)\n",
			      aux_ch_name(aux_ch), port_name(port));
		return aux_ch;
	}

	switch (info->alternate_aux_channel) {
	case DP_AUX_A:
		aux_ch = AUX_CH_A;
		break;
	case DP_AUX_B:
		aux_ch = AUX_CH_B;
		break;
	case DP_AUX_C:
		aux_ch = AUX_CH_C;
		break;
	case DP_AUX_D:
		aux_ch = AUX_CH_D;
		break;
	case DP_AUX_E:
		aux_ch = AUX_CH_E;
		break;
	case DP_AUX_F:
		aux_ch = AUX_CH_F;
		break;
	default:
		MISSING_CASE(info->alternate_aux_channel);
		aux_ch = AUX_CH_A;
		break;
	}

	DRM_DEBUG_KMS("using AUX %c for port %c (VBT)\n",
		      aux_ch_name(aux_ch), port_name(port));

	return aux_ch;
}