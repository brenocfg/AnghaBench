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
struct intel_hdmi {struct intel_connector* attached_connector; } ;
struct intel_digital_port {int /*<<< orphan*/  base; struct intel_hdmi hdmi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_connector {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,char*,int) ; 
 scalar_t__ IS_KABYLAKE (struct drm_i915_private*) ; 
 int intel_ddi_toggle_hdcp_signalling (int /*<<< orphan*/ *,int) ; 
 int kbl_repositioning_enc_en_signal (struct intel_connector*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static
int intel_hdmi_hdcp_toggle_signalling(struct intel_digital_port *intel_dig_port,
				      bool enable)
{
	struct intel_hdmi *hdmi = &intel_dig_port->hdmi;
	struct intel_connector *connector = hdmi->attached_connector;
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	int ret;

	if (!enable)
		usleep_range(6, 60); /* Bspec says >= 6us */

	ret = intel_ddi_toggle_hdcp_signalling(&intel_dig_port->base, enable);
	if (ret) {
		DRM_ERROR("%s HDCP signalling failed (%d)\n",
			  enable ? "Enable" : "Disable", ret);
		return ret;
	}

	/*
	 * WA: To fix incorrect positioning of the window of
	 * opportunity and enc_en signalling in KABYLAKE.
	 */
	if (IS_KABYLAKE(dev_priv) && enable)
		return kbl_repositioning_enc_en_signal(connector);

	return 0;
}