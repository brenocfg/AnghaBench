#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct panel_info {void* height_mm; void* width_mm; } ;
struct panel_funcs {scalar_t__ (* get_panel_info ) (struct drm_device*,int,struct panel_info*) ;struct mdfld_dsi_connector* (* get_config_mode ) (struct drm_device*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  type; } ;
struct mdfld_dsi_encoder {TYPE_4__ base; struct mdfld_dsi_connector* private; } ;
struct TYPE_6__ {void* height_mm; void* width_mm; int /*<<< orphan*/  subpixel_order; } ;
struct drm_connector {int interlace_allowed; int doublescan_allowed; int /*<<< orphan*/  base; TYPE_2__ display_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  restore; int /*<<< orphan*/  save; struct drm_connector base; } ;
struct mdfld_dsi_connector {int pipe; int changed; int dvr_ic_inited; struct mdfld_dsi_connector* fixed_mode; int /*<<< orphan*/  pkg_sender; struct mdfld_dsi_encoder* encoder; TYPE_1__ base; struct mdfld_dsi_connector* connector; struct mdfld_dsi_connector* mode; struct drm_device* dev; struct mdfld_dsi_connector* private; } ;
struct mdfld_dsi_config {int pipe; int changed; int dvr_ic_inited; struct mdfld_dsi_config* fixed_mode; int /*<<< orphan*/  pkg_sender; struct mdfld_dsi_encoder* encoder; TYPE_1__ base; struct mdfld_dsi_config* connector; struct mdfld_dsi_config* mode; struct drm_device* dev; struct mdfld_dsi_config* private; } ;
struct drm_psb_private {int /*<<< orphan*/  backlight_property; struct mdfld_dsi_connector** dsi_configs; } ;
struct TYPE_7__ {int /*<<< orphan*/  scaling_mode_property; } ;
struct drm_device {TYPE_3__ mode_config; int /*<<< orphan*/  dev; struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_LVDS ; 
 int /*<<< orphan*/  DRM_MODE_SCALE_FULLSCREEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INTEL_OUTPUT_MIPI ; 
 int /*<<< orphan*/  INTEL_OUTPUT_MIPI2 ; 
 int /*<<< orphan*/  MDFLD_DSI_BRIGHTNESS_MAX_LEVEL ; 
 int /*<<< orphan*/  SubPixelHorizontalRGB ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_register (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mdfld_dsi_connector*) ; 
 struct mdfld_dsi_connector* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdfld_dsi_connector_funcs ; 
 int /*<<< orphan*/  mdfld_dsi_connector_helper_funcs ; 
 int /*<<< orphan*/  mdfld_dsi_connector_restore ; 
 int /*<<< orphan*/  mdfld_dsi_connector_save ; 
 struct mdfld_dsi_encoder* mdfld_dsi_dpi_init (struct drm_device*,struct mdfld_dsi_connector*,struct panel_funcs const*) ; 
 int /*<<< orphan*/  mdfld_dsi_get_default_config (struct drm_device*,struct mdfld_dsi_connector*,int) ; 
 int /*<<< orphan*/  mdfld_dsi_pkg_sender_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ mdfld_dsi_pkg_sender_init (struct mdfld_dsi_connector*,int) ; 
 struct mdfld_dsi_connector* stub1 (struct drm_device*) ; 
 scalar_t__ stub2 (struct drm_device*,int,struct panel_info*) ; 

void mdfld_dsi_output_init(struct drm_device *dev,
			   int pipe,
			   const struct panel_funcs *p_vid_funcs)
{
	struct mdfld_dsi_config *dsi_config;
	struct mdfld_dsi_connector *dsi_connector;
	struct drm_connector *connector;
	struct mdfld_dsi_encoder *encoder;
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct panel_info dsi_panel_info;
	u32 width_mm, height_mm;

	dev_dbg(dev->dev, "init DSI output on pipe %d\n", pipe);

	if (pipe != 0 && pipe != 2) {
		DRM_ERROR("Invalid parameter\n");
		return;
	}

	/*create a new connetor*/
	dsi_connector = kzalloc(sizeof(struct mdfld_dsi_connector), GFP_KERNEL);
	if (!dsi_connector) {
		DRM_ERROR("No memory");
		return;
	}

	dsi_connector->pipe =  pipe;

	dsi_config = kzalloc(sizeof(struct mdfld_dsi_config),
			GFP_KERNEL);
	if (!dsi_config) {
		DRM_ERROR("cannot allocate memory for DSI config\n");
		goto dsi_init_err0;
	}
	mdfld_dsi_get_default_config(dev, dsi_config, pipe);

	dsi_connector->private = dsi_config;

	dsi_config->changed = 1;
	dsi_config->dev = dev;

	dsi_config->fixed_mode = p_vid_funcs->get_config_mode(dev);
	if (p_vid_funcs->get_panel_info(dev, pipe, &dsi_panel_info))
			goto dsi_init_err0;

	width_mm = dsi_panel_info.width_mm;
	height_mm = dsi_panel_info.height_mm;

	dsi_config->mode = dsi_config->fixed_mode;
	dsi_config->connector = dsi_connector;

	if (!dsi_config->fixed_mode) {
		DRM_ERROR("No pannel fixed mode was found\n");
		goto dsi_init_err0;
	}

	if (pipe && dev_priv->dsi_configs[0]) {
		dsi_config->dvr_ic_inited = 0;
		dev_priv->dsi_configs[1] = dsi_config;
	} else if (pipe == 0) {
		dsi_config->dvr_ic_inited = 1;
		dev_priv->dsi_configs[0] = dsi_config;
	} else {
		DRM_ERROR("Trying to init MIPI1 before MIPI0\n");
		goto dsi_init_err0;
	}


	connector = &dsi_connector->base.base;
	dsi_connector->base.save = mdfld_dsi_connector_save;
	dsi_connector->base.restore = mdfld_dsi_connector_restore;

	drm_connector_init(dev, connector, &mdfld_dsi_connector_funcs,
						DRM_MODE_CONNECTOR_LVDS);
	drm_connector_helper_add(connector, &mdfld_dsi_connector_helper_funcs);

	connector->display_info.subpixel_order = SubPixelHorizontalRGB;
	connector->display_info.width_mm = width_mm;
	connector->display_info.height_mm = height_mm;
	connector->interlace_allowed = false;
	connector->doublescan_allowed = false;

	/*attach properties*/
	drm_object_attach_property(&connector->base,
				dev->mode_config.scaling_mode_property,
				DRM_MODE_SCALE_FULLSCREEN);
	drm_object_attach_property(&connector->base,
				dev_priv->backlight_property,
				MDFLD_DSI_BRIGHTNESS_MAX_LEVEL);

	/*init DSI package sender on this output*/
	if (mdfld_dsi_pkg_sender_init(dsi_connector, pipe)) {
		DRM_ERROR("Package Sender initialization failed on pipe %d\n",
									pipe);
		goto dsi_init_err0;
	}

	encoder = mdfld_dsi_dpi_init(dev, dsi_connector, p_vid_funcs);
	if (!encoder) {
		DRM_ERROR("Create DPI encoder failed\n");
		goto dsi_init_err1;
	}
	encoder->private = dsi_config;
	dsi_config->encoder = encoder;
	encoder->base.type = (pipe == 0) ? INTEL_OUTPUT_MIPI :
		INTEL_OUTPUT_MIPI2;
	drm_connector_register(connector);
	return;

	/*TODO: add code to destroy outputs on error*/
dsi_init_err1:
	/*destroy sender*/
	mdfld_dsi_pkg_sender_destroy(dsi_connector->pkg_sender);

	drm_connector_cleanup(connector);

	kfree(dsi_config->fixed_mode);
	kfree(dsi_config);
dsi_init_err0:
	kfree(dsi_connector);
}