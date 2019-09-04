#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tinydrm_device {int /*<<< orphan*/  drm; int /*<<< orphan*/  fb_dirty; } ;
struct spi_device_id {int driver_data; } ;
struct device {int /*<<< orphan*/  coherent_dma_mask; } ;
struct spi_device {int max_speed_hz; struct device dev; } ;
struct repaper_epd {int stage_time; int bytes_per_scan; int middle_scan; int pre_border_byte; int width; int height; int factored_stage_time; struct tinydrm_device tinydrm; void* current_frame; void* line_buffer; void* border_byte; int /*<<< orphan*/  channel_select; void* border; void* thermal; void* busy; void* reset; void* discharge; void* panel_on; struct spi_device* spi; } ;
struct of_device_id {scalar_t__ data; } ;
struct drm_display_mode {int hdisplay; int vdisplay; } ;
typedef  enum repaper_model { ____Placeholder_repaper_model } repaper_model ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,...) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VIRTUAL ; 
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
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_tinydrm_init (struct device*,struct tinydrm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int devm_tinydrm_register (struct tinydrm_device*) ; 
 int dma_coerce_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_config_reset (int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  repaper_driver ; 
 int /*<<< orphan*/  repaper_e1144cs021_cs ; 
 struct drm_display_mode repaper_e1144cs021_mode ; 
 int /*<<< orphan*/  repaper_e1190cs021_cs ; 
 struct drm_display_mode repaper_e1190cs021_mode ; 
 int /*<<< orphan*/  repaper_e2200cs021_cs ; 
 struct drm_display_mode repaper_e2200cs021_mode ; 
 int /*<<< orphan*/  repaper_e2271cs021_cs ; 
 struct drm_display_mode repaper_e2271cs021_mode ; 
 int /*<<< orphan*/  repaper_fb_dirty ; 
 int /*<<< orphan*/  repaper_fb_funcs ; 
 int /*<<< orphan*/  repaper_formats ; 
 int /*<<< orphan*/  repaper_of_match ; 
 int /*<<< orphan*/  repaper_pipe_funcs ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct tinydrm_device*) ; 
 void* thermal_zone_get_zone_by_name (char const*) ; 
 int tinydrm_display_pipe_init (struct tinydrm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_display_mode const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int repaper_probe(struct spi_device *spi)
{
	const struct drm_display_mode *mode;
	const struct spi_device_id *spi_id;
	const struct of_device_id *match;
	struct device *dev = &spi->dev;
	struct tinydrm_device *tdev;
	enum repaper_model model;
	const char *thermal_zone;
	struct repaper_epd *epd;
	size_t line_buffer_size;
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

	epd = devm_kzalloc(dev, sizeof(*epd), GFP_KERNEL);
	if (!epd)
		return -ENOMEM;

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

	tdev = &epd->tinydrm;

	ret = devm_tinydrm_init(dev, tdev, &repaper_fb_funcs, &repaper_driver);
	if (ret)
		return ret;

	tdev->fb_dirty = repaper_fb_dirty;

	ret = tinydrm_display_pipe_init(tdev, &repaper_pipe_funcs,
					DRM_MODE_CONNECTOR_VIRTUAL,
					repaper_formats,
					ARRAY_SIZE(repaper_formats), mode, 0);
	if (ret)
		return ret;

	drm_mode_config_reset(tdev->drm);
	spi_set_drvdata(spi, tdev);

	DRM_DEBUG_DRIVER("SPI speed: %uMHz\n", spi->max_speed_hz / 1000000);

	return devm_tinydrm_register(tdev);
}