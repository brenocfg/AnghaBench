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
struct psb_intel_mode_device {int dummy; } ;
struct drm_encoder {int dummy; } ;
struct gma_encoder {int /*<<< orphan*/  type; struct drm_encoder base; } ;
struct TYPE_2__ {int /*<<< orphan*/  subpixel_order; } ;
struct drm_connector {int interlace_allowed; int doublescan_allowed; TYPE_1__ display_info; } ;
struct gma_connector {struct drm_connector base; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DVID ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_TMDS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 int /*<<< orphan*/  SubPixelHorizontalRGB ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_register (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gma_connector_attach_encoder (struct gma_connector*,struct gma_encoder*) ; 
 int /*<<< orphan*/  kfree (struct gma_encoder*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oaktrail_hdmi_connector_funcs ; 
 int /*<<< orphan*/  oaktrail_hdmi_connector_helper_funcs ; 
 int /*<<< orphan*/  oaktrail_hdmi_enc_funcs ; 
 int /*<<< orphan*/  oaktrail_hdmi_helper_funcs ; 

void oaktrail_hdmi_init(struct drm_device *dev,
					struct psb_intel_mode_device *mode_dev)
{
	struct gma_encoder *gma_encoder;
	struct gma_connector *gma_connector;
	struct drm_connector *connector;
	struct drm_encoder *encoder;

	gma_encoder = kzalloc(sizeof(struct gma_encoder), GFP_KERNEL);
	if (!gma_encoder)
		return;

	gma_connector = kzalloc(sizeof(struct gma_connector), GFP_KERNEL);
	if (!gma_connector)
		goto failed_connector;

	connector = &gma_connector->base;
	encoder = &gma_encoder->base;
	drm_connector_init(dev, connector,
			   &oaktrail_hdmi_connector_funcs,
			   DRM_MODE_CONNECTOR_DVID);

	drm_encoder_init(dev, encoder,
			 &oaktrail_hdmi_enc_funcs,
			 DRM_MODE_ENCODER_TMDS, NULL);

	gma_connector_attach_encoder(gma_connector, gma_encoder);

	gma_encoder->type = INTEL_OUTPUT_HDMI;
	drm_encoder_helper_add(encoder, &oaktrail_hdmi_helper_funcs);
	drm_connector_helper_add(connector, &oaktrail_hdmi_connector_helper_funcs);

	connector->display_info.subpixel_order = SubPixelHorizontalRGB;
	connector->interlace_allowed = false;
	connector->doublescan_allowed = false;
	drm_connector_register(connector);
	dev_info(dev->dev, "HDMI initialised.\n");

	return;

failed_connector:
	kfree(gma_encoder);
}