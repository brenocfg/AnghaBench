#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct intel_hdmi {int /*<<< orphan*/  ddc_bus; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_5__ base; } ;
struct i2c_adapter {int dummy; } ;
struct drm_scrambling {int /*<<< orphan*/  supported; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {struct drm_scrambling scrambling; } ;
struct TYPE_7__ {TYPE_1__ scdc; } ;
struct TYPE_8__ {TYPE_2__ hdmi; } ;
struct drm_connector {int /*<<< orphan*/  name; TYPE_4__ base; TYPE_3__ display_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ drm_scdc_set_high_tmds_clock_ratio (struct i2c_adapter*,int) ; 
 scalar_t__ drm_scdc_set_scrambling (struct i2c_adapter*,int) ; 
 struct intel_hdmi* enc_to_intel_hdmi (TYPE_5__*) ; 
 struct i2c_adapter* intel_gmbus_get_adapter (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yesno (int) ; 

bool intel_hdmi_handle_sink_scrambling(struct intel_encoder *encoder,
				       struct drm_connector *connector,
				       bool high_tmds_clock_ratio,
				       bool scrambling)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_hdmi *intel_hdmi = enc_to_intel_hdmi(&encoder->base);
	struct drm_scrambling *sink_scrambling =
		&connector->display_info.hdmi.scdc.scrambling;
	struct i2c_adapter *adapter =
		intel_gmbus_get_adapter(dev_priv, intel_hdmi->ddc_bus);

	if (!sink_scrambling->supported)
		return true;

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s] scrambling=%s, TMDS bit clock ratio=1/%d\n",
		      connector->base.id, connector->name,
		      yesno(scrambling), high_tmds_clock_ratio ? 40 : 10);

	/* Set TMDS bit clock ratio to 1/40 or 1/10, and enable/disable scrambling */
	return drm_scdc_set_high_tmds_clock_ratio(adapter,
						  high_tmds_clock_ratio) &&
		drm_scdc_set_scrambling(adapter, scrambling);
}