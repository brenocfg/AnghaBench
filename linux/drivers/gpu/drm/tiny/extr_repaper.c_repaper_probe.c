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
struct spi_device_id {int driver_data; } ;
struct device {int /*<<< orphan*/  coherent_dma_mask; } ;
struct spi_device {int max_speed_hz; struct device dev; } ;
struct TYPE_2__ {int min_width; int max_width; int min_height; int max_height; int /*<<< orphan*/ * funcs; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct repaper_epd {int stage_time; int bytes_per_scan; int middle_scan; int pre_border_byte; int width; int height; int factored_stage_time; int /*<<< orphan*/  connector; int /*<<< orphan*/  pipe; void* current_frame; void* line_buffer; struct drm_display_mode const* mode; void* border_byte; int /*<<< orphan*/  channel_select; void* border; void* thermal; void* busy; void* reset; void* discharge; void* panel_on; struct spi_device* spi; struct drm_device drm; } ;
struct of_device_id {scalar_t__ data; } ;
struct drm_display_mode {int hdisplay; int vdisplay; } ;
typedef  enum repaper_model { ____Placeholder_repaper_model } repaper_model ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,...) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_SPI ; 
#define  E1144CS021 131 
#define  E1190CS021 130 
#define  E2200CS021 129 
#define  E2271CS021 128 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* REPAPER_BORDER_BYTE_NONE ; 
 void* REPAPER_BORDER_BYTE_SET ; 
 void* REPAPER_BORDER_BYTE_ZERO ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int /*<<< orphan*/  device_property_read_string (struct device*,char*,char const**) ; 
 int devm_drm_dev_init (struct device*,struct drm_device*,int /*<<< orphan*/ *) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int dma_coerce_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_connector_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fbdev_generic_setup (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int drm_simple_display_pipe_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct repaper_epd*) ; 
 struct repaper_epd* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  repaper_connector_funcs ; 
 int /*<<< orphan*/  repaper_connector_hfuncs ; 
 int /*<<< orphan*/  repaper_driver ; 
 int /*<<< orphan*/  repaper_e1144cs021_cs ; 
 struct drm_display_mode repaper_e1144cs021_mode ; 
 int /*<<< orphan*/  repaper_e1190cs021_cs ; 
 struct drm_display_mode repaper_e1190cs021_mode ; 
 int /*<<< orphan*/  repaper_e2200cs021_cs ; 
 struct drm_display_mode repaper_e2200cs021_mode ; 
 int /*<<< orphan*/  repaper_e2271cs021_cs ; 
 struct drm_display_mode repaper_e2271cs021_mode ; 
 int /*<<< orphan*/  repaper_formats ; 
 int /*<<< orphan*/  repaper_mode_config_funcs ; 
 int /*<<< orphan*/  repaper_of_match ; 
 int /*<<< orphan*/  repaper_pipe_funcs ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct drm_device*) ; 
 void* thermal_zone_get_zone_by_name (char const*) ; 

__attribute__((used)) static int repaper_probe(struct spi_device *spi)
{
	const struct drm_display_mode *mode;
	const struct spi_device_id *spi_id;
	const struct of_device_id *match;
	struct device *dev = &spi->dev;
	enum repaper_model model;
	const char *thermal_zone;
	struct repaper_epd *epd;
	size_t line_buffer_size;
	struct drm_device *drm;
	int ret;

	match = of_match_device(repaper_of_match, dev);
	if (match) {
		model = (enum repaper_model)match->data;
	} else {
		spi_id = spi_get_device_id(spi);
		model = spi_id->driver_data;
	}

	/* The SPI device is used to allocate dma memory */
	if (!dev->coherent_dma_mask) {
		ret = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(32));
		if (ret) {
			dev_warn(dev, "Failed to set dma mask %d\n", ret);
			return ret;
		}
	}

	epd = kzalloc(sizeof(*epd), GFP_KERNEL);
	if (!epd)
		return -ENOMEM;

	drm = &epd->drm;

	ret = devm_drm_dev_init(dev, drm, &repaper_driver);
	if (ret) {
		kfree(epd);
		return ret;
	}

	drm_mode_config_init(drm);
	drm->mode_config.funcs = &repaper_mode_config_funcs;

	epd->spi = spi;

	epd->panel_on = devm_gpiod_get(dev, "panel-on", GPIOD_OUT_LOW);
	if (IS_ERR(epd->panel_on)) {
		ret = PTR_ERR(epd->panel_on);
		if (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dev, "Failed to get gpio 'panel-on'\n");
		return ret;
	}

	epd->discharge = devm_gpiod_get(dev, "discharge", GPIOD_OUT_LOW);
	if (IS_ERR(epd->discharge)) {
		ret = PTR_ERR(epd->discharge);
		if (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dev, "Failed to get gpio 'discharge'\n");
		return ret;
	}

	epd->reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(epd->reset)) {
		ret = PTR_ERR(epd->reset);
		if (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dev, "Failed to get gpio 'reset'\n");
		return ret;
	}

	epd->busy = devm_gpiod_get(dev, "busy", GPIOD_IN);
	if (IS_ERR(epd->busy)) {
		ret = PTR_ERR(epd->busy);
		if (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dev, "Failed to get gpio 'busy'\n");
		return ret;
	}

	if (!device_property_read_string(dev, "pervasive,thermal-zone",
					 &thermal_zone)) {
		epd->thermal = thermal_zone_get_zone_by_name(thermal_zone);
		if (IS_ERR(epd->thermal)) {
			DRM_DEV_ERROR(dev, "Failed to get thermal zone: %s\n", thermal_zone);
			return PTR_ERR(epd->thermal);
		}
	}

	switch (model) {
	case E1144CS021:
		mode = &repaper_e1144cs021_mode;
		epd->channel_select = repaper_e1144cs021_cs;
		epd->stage_time = 480;
		epd->bytes_per_scan = 96 / 4;
		epd->middle_scan = true; /* data-scan-data */
		epd->pre_border_byte = false;
		epd->border_byte = REPAPER_BORDER_BYTE_ZERO;
		break;

	case E1190CS021:
		mode = &repaper_e1190cs021_mode;
		epd->channel_select = repaper_e1190cs021_cs;
		epd->stage_time = 480;
		epd->bytes_per_scan = 128 / 4 / 2;
		epd->middle_scan = false; /* scan-data-scan */
		epd->pre_border_byte = false;
		epd->border_byte = REPAPER_BORDER_BYTE_SET;
		break;

	case E2200CS021:
		mode = &repaper_e2200cs021_mode;
		epd->channel_select = repaper_e2200cs021_cs;
		epd->stage_time = 480;
		epd->bytes_per_scan = 96 / 4;
		epd->middle_scan = true; /* data-scan-data */
		epd->pre_border_byte = true;
		epd->border_byte = REPAPER_BORDER_BYTE_NONE;
		break;

	case E2271CS021:
		epd->border = devm_gpiod_get(dev, "border", GPIOD_OUT_LOW);
		if (IS_ERR(epd->border)) {
			ret = PTR_ERR(epd->border);
			if (ret != -EPROBE_DEFER)
				DRM_DEV_ERROR(dev, "Failed to get gpio 'border'\n");
			return ret;
		}

		mode = &repaper_e2271cs021_mode;
		epd->channel_select = repaper_e2271cs021_cs;
		epd->stage_time = 630;
		epd->bytes_per_scan = 176 / 4;
		epd->middle_scan = true; /* data-scan-data */
		epd->pre_border_byte = true;
		epd->border_byte = REPAPER_BORDER_BYTE_NONE;
		break;

	default:
		return -ENODEV;
	}

	epd->mode = mode;
	epd->width = mode->hdisplay;
	epd->height = mode->vdisplay;
	epd->factored_stage_time = epd->stage_time;

	line_buffer_size = 2 * epd->width / 8 + epd->bytes_per_scan + 2;
	epd->line_buffer = devm_kzalloc(dev, line_buffer_size, GFP_KERNEL);
	if (!epd->line_buffer)
		return -ENOMEM;

	epd->current_frame = devm_kzalloc(dev, epd->width * epd->height / 8,
					  GFP_KERNEL);
	if (!epd->current_frame)
		return -ENOMEM;

	drm->mode_config.min_width = mode->hdisplay;
	drm->mode_config.max_width = mode->hdisplay;
	drm->mode_config.min_height = mode->vdisplay;
	drm->mode_config.max_height = mode->vdisplay;

	drm_connector_helper_add(&epd->connector, &repaper_connector_hfuncs);
	ret = drm_connector_init(drm, &epd->connector, &repaper_connector_funcs,
				 DRM_MODE_CONNECTOR_SPI);
	if (ret)
		return ret;

	ret = drm_simple_display_pipe_init(drm, &epd->pipe, &repaper_pipe_funcs,
					   repaper_formats, ARRAY_SIZE(repaper_formats),
					   NULL, &epd->connector);
	if (ret)
		return ret;

	drm_mode_config_reset(drm);

	ret = drm_dev_register(drm, 0);
	if (ret)
		return ret;

	spi_set_drvdata(spi, drm);

	DRM_DEBUG_DRIVER("SPI speed: %uMHz\n", spi->max_speed_hz / 1000000);

	drm_fbdev_generic_setup(drm, 0);

	return 0;
}