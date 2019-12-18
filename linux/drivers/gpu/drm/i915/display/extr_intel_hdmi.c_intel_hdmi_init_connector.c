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
typedef  int u32 ;
struct intel_hdmi {int /*<<< orphan*/  cec_notifier; struct intel_connector* attached_connector; int /*<<< orphan*/  ddc_bus; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct intel_encoder {int port; int /*<<< orphan*/  hpd_pin; TYPE_1__ base; } ;
struct intel_digital_port {int max_lanes; struct intel_encoder base; struct intel_hdmi hdmi; } ;
struct drm_connector {int interlace_allowed; int stereo_allowed; int ycbcr_420_allowed; scalar_t__ doublescan_allowed; } ;
struct intel_connector {int /*<<< orphan*/  get_hw_state; struct drm_connector base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_HDMIA ; 
 scalar_t__ HAS_DDI (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_G45 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PEG_BAND_GAP_DATA ; 
 int PORT_A ; 
 scalar_t__ WARN (int,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cec_notifier_get_conn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_connector_attach_encoder (struct intel_connector*,struct intel_encoder*) ; 
 int /*<<< orphan*/  intel_connector_get_hw_state ; 
 int /*<<< orphan*/  intel_ddi_connector_get_hw_state ; 
 int intel_hdcp_init (struct intel_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_hdmi_add_properties (struct intel_hdmi*,struct drm_connector*) ; 
 int /*<<< orphan*/  intel_hdmi_connector_funcs ; 
 int /*<<< orphan*/  intel_hdmi_connector_helper_funcs ; 
 int /*<<< orphan*/  intel_hdmi_ddc_pin (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_hdmi_hdcp_shim ; 
 int /*<<< orphan*/  intel_hpd_pin_default (struct drm_i915_private*,int) ; 
 scalar_t__ is_hdcp_supported (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  port_identifier (int) ; 
 int /*<<< orphan*/  port_name (int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

void intel_hdmi_init_connector(struct intel_digital_port *intel_dig_port,
			       struct intel_connector *intel_connector)
{
	struct drm_connector *connector = &intel_connector->base;
	struct intel_hdmi *intel_hdmi = &intel_dig_port->hdmi;
	struct intel_encoder *intel_encoder = &intel_dig_port->base;
	struct drm_device *dev = intel_encoder->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	enum port port = intel_encoder->port;

	DRM_DEBUG_KMS("Adding HDMI connector on port %c\n",
		      port_name(port));

	if (WARN(intel_dig_port->max_lanes < 4,
		 "Not enough lanes (%d) for HDMI on port %c\n",
		 intel_dig_port->max_lanes, port_name(port)))
		return;

	drm_connector_init(dev, connector, &intel_hdmi_connector_funcs,
			   DRM_MODE_CONNECTOR_HDMIA);
	drm_connector_helper_add(connector, &intel_hdmi_connector_helper_funcs);

	connector->interlace_allowed = 1;
	connector->doublescan_allowed = 0;
	connector->stereo_allowed = 1;

	if (INTEL_GEN(dev_priv) >= 10 || IS_GEMINILAKE(dev_priv))
		connector->ycbcr_420_allowed = true;

	intel_hdmi->ddc_bus = intel_hdmi_ddc_pin(dev_priv, port);

	if (WARN_ON(port == PORT_A))
		return;
	intel_encoder->hpd_pin = intel_hpd_pin_default(dev_priv, port);

	if (HAS_DDI(dev_priv))
		intel_connector->get_hw_state = intel_ddi_connector_get_hw_state;
	else
		intel_connector->get_hw_state = intel_connector_get_hw_state;

	intel_hdmi_add_properties(intel_hdmi, connector);

	intel_connector_attach_encoder(intel_connector, intel_encoder);
	intel_hdmi->attached_connector = intel_connector;

	if (is_hdcp_supported(dev_priv, port)) {
		int ret = intel_hdcp_init(intel_connector,
					  &intel_hdmi_hdcp_shim);
		if (ret)
			DRM_DEBUG_KMS("HDCP init failed, skipping.\n");
	}

	/* For G4X desktop chip, PEG_BAND_GAP_DATA 3:0 must first be written
	 * 0xd.  Failure to do so will result in spurious interrupts being
	 * generated on the port when a cable is not attached.
	 */
	if (IS_G45(dev_priv)) {
		u32 temp = I915_READ(PEG_BAND_GAP_DATA);
		I915_WRITE(PEG_BAND_GAP_DATA, (temp & ~0xf) | 0xd);
	}

	intel_hdmi->cec_notifier = cec_notifier_get_conn(dev->dev,
							 port_identifier(port));
	if (!intel_hdmi->cec_notifier)
		DRM_DEBUG_KMS("CEC notifier get failed\n");
}