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
typedef  int /*<<< orphan*/  u32 ;
struct psb_intel_mode_device {int dummy; } ;
struct drm_encoder {scalar_t__ doublescan_allowed; scalar_t__ interlace_allowed; int /*<<< orphan*/  polled; } ;
struct gma_encoder {struct drm_encoder base; int /*<<< orphan*/  type; int /*<<< orphan*/  ddc_bus; } ;
struct gma_connector {struct drm_encoder base; int /*<<< orphan*/  type; int /*<<< orphan*/  ddc_bus; } ;
struct drm_device {TYPE_1__* pdev; } ;
struct drm_connector {scalar_t__ doublescan_allowed; scalar_t__ interlace_allowed; int /*<<< orphan*/  polled; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VGA ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_DAC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOA ; 
 int /*<<< orphan*/  INTEL_OUTPUT_ANALOG ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  cdv_intel_crt_connector_funcs ; 
 int /*<<< orphan*/  cdv_intel_crt_connector_helper_funcs ; 
 int /*<<< orphan*/  cdv_intel_crt_enc_funcs ; 
 int /*<<< orphan*/  cdv_intel_crt_helper_funcs ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_register (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gma_connector_attach_encoder (struct gma_encoder*,struct gma_encoder*) ; 
 int /*<<< orphan*/  kfree (struct gma_encoder*) ; 
 struct gma_encoder* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psb_intel_i2c_create (struct drm_device*,int /*<<< orphan*/ ,char*) ; 

void cdv_intel_crt_init(struct drm_device *dev,
			struct psb_intel_mode_device *mode_dev)
{

	struct gma_connector *gma_connector;
	struct gma_encoder *gma_encoder;
	struct drm_connector *connector;
	struct drm_encoder *encoder;

	u32 i2c_reg;

	gma_encoder = kzalloc(sizeof(struct gma_encoder), GFP_KERNEL);
	if (!gma_encoder)
		return;

	gma_connector = kzalloc(sizeof(struct gma_connector), GFP_KERNEL);
	if (!gma_connector)
		goto failed_connector;

	connector = &gma_connector->base;
	connector->polled = DRM_CONNECTOR_POLL_HPD;
	drm_connector_init(dev, connector,
		&cdv_intel_crt_connector_funcs, DRM_MODE_CONNECTOR_VGA);

	encoder = &gma_encoder->base;
	drm_encoder_init(dev, encoder,
		&cdv_intel_crt_enc_funcs, DRM_MODE_ENCODER_DAC, NULL);

	gma_connector_attach_encoder(gma_connector, gma_encoder);

	/* Set up the DDC bus. */
	i2c_reg = GPIOA;
	/* Remove the following code for CDV */
	/*
	if (dev_priv->crt_ddc_bus != 0)
		i2c_reg = dev_priv->crt_ddc_bus;
	}*/
	gma_encoder->ddc_bus = psb_intel_i2c_create(dev,
							  i2c_reg, "CRTDDC_A");
	if (!gma_encoder->ddc_bus) {
		dev_printk(KERN_ERR, &dev->pdev->dev, "DDC bus registration "
			   "failed.\n");
		goto failed_ddc;
	}

	gma_encoder->type = INTEL_OUTPUT_ANALOG;
	/*
	psb_intel_output->clone_mask = (1 << INTEL_ANALOG_CLONE_BIT);
	psb_intel_output->crtc_mask = (1 << 0) | (1 << 1);
	*/
	connector->interlace_allowed = 0;
	connector->doublescan_allowed = 0;

	drm_encoder_helper_add(encoder, &cdv_intel_crt_helper_funcs);
	drm_connector_helper_add(connector,
					&cdv_intel_crt_connector_helper_funcs);

	drm_connector_register(connector);

	return;
failed_ddc:
	drm_encoder_cleanup(&gma_encoder->base);
	drm_connector_cleanup(&gma_connector->base);
	kfree(gma_connector);
failed_connector:
	kfree(gma_encoder);
	return;
}