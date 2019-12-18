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
struct device {int dummy; } ;
struct spi_device {struct device dev; } ;
struct repaper_epd {int enabled; int partial; int /*<<< orphan*/  channel_select; int /*<<< orphan*/  busy; scalar_t__ reset; scalar_t__ border; scalar_t__ panel_on; scalar_t__ discharge; struct spi_device* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct drm_simple_display_pipe {TYPE_1__ crtc; } ;
struct drm_plane_state {int dummy; } ;
struct drm_crtc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,...) ; 
 int REPAPER_RID_G2_COG_ID ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  drm_dev_enter (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  drm_dev_exit (int) ; 
 struct repaper_epd* drm_to_epd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  power_off (struct repaper_epd*) ; 
 int repaper_read_id (struct spi_device*) ; 
 int repaper_read_val (struct spi_device*,int) ; 
 int /*<<< orphan*/  repaper_spi_mosi_low (struct spi_device*) ; 
 int /*<<< orphan*/  repaper_write_buf (struct spi_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  repaper_write_val (struct spi_device*,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void repaper_pipe_enable(struct drm_simple_display_pipe *pipe,
				struct drm_crtc_state *crtc_state,
				struct drm_plane_state *plane_state)
{
	struct repaper_epd *epd = drm_to_epd(pipe->crtc.dev);
	struct spi_device *spi = epd->spi;
	struct device *dev = &spi->dev;
	bool dc_ok = false;
	int i, ret, idx;

	if (!drm_dev_enter(pipe->crtc.dev, &idx))
		return;

	DRM_DEBUG_DRIVER("\n");

	/* Power up sequence */
	gpiod_set_value_cansleep(epd->reset, 0);
	gpiod_set_value_cansleep(epd->panel_on, 0);
	gpiod_set_value_cansleep(epd->discharge, 0);
	if (epd->border)
		gpiod_set_value_cansleep(epd->border, 0);
	repaper_spi_mosi_low(spi);
	usleep_range(5000, 10000);

	gpiod_set_value_cansleep(epd->panel_on, 1);
	/*
	 * This delay comes from the repaper.org userspace driver, it's not
	 * mentioned in the datasheet.
	 */
	usleep_range(10000, 15000);
	gpiod_set_value_cansleep(epd->reset, 1);
	if (epd->border)
		gpiod_set_value_cansleep(epd->border, 1);
	usleep_range(5000, 10000);
	gpiod_set_value_cansleep(epd->reset, 0);
	usleep_range(5000, 10000);
	gpiod_set_value_cansleep(epd->reset, 1);
	usleep_range(5000, 10000);

	/* Wait for COG to become ready */
	for (i = 100; i > 0; i--) {
		if (!gpiod_get_value_cansleep(epd->busy))
			break;

		usleep_range(10, 100);
	}

	if (!i) {
		DRM_DEV_ERROR(dev, "timeout waiting for panel to become ready.\n");
		power_off(epd);
		goto out_exit;
	}

	repaper_read_id(spi);
	ret = repaper_read_id(spi);
	if (ret != REPAPER_RID_G2_COG_ID) {
		if (ret < 0)
			dev_err(dev, "failed to read chip (%d)\n", ret);
		else
			dev_err(dev, "wrong COG ID 0x%02x\n", ret);
		power_off(epd);
		goto out_exit;
	}

	/* Disable OE */
	repaper_write_val(spi, 0x02, 0x40);

	ret = repaper_read_val(spi, 0x0f);
	if (ret < 0 || !(ret & 0x80)) {
		if (ret < 0)
			DRM_DEV_ERROR(dev, "failed to read chip (%d)\n", ret);
		else
			DRM_DEV_ERROR(dev, "panel is reported broken\n");
		power_off(epd);
		goto out_exit;
	}

	/* Power saving mode */
	repaper_write_val(spi, 0x0b, 0x02);
	/* Channel select */
	repaper_write_buf(spi, 0x01, epd->channel_select, 8);
	/* High power mode osc */
	repaper_write_val(spi, 0x07, 0xd1);
	/* Power setting */
	repaper_write_val(spi, 0x08, 0x02);
	/* Vcom level */
	repaper_write_val(spi, 0x09, 0xc2);
	/* Power setting */
	repaper_write_val(spi, 0x04, 0x03);
	/* Driver latch on */
	repaper_write_val(spi, 0x03, 0x01);
	/* Driver latch off */
	repaper_write_val(spi, 0x03, 0x00);
	usleep_range(5000, 10000);

	/* Start chargepump */
	for (i = 0; i < 4; ++i) {
		/* Charge pump positive voltage on - VGH/VDL on */
		repaper_write_val(spi, 0x05, 0x01);
		msleep(240);

		/* Charge pump negative voltage on - VGL/VDL on */
		repaper_write_val(spi, 0x05, 0x03);
		msleep(40);

		/* Charge pump Vcom on - Vcom driver on */
		repaper_write_val(spi, 0x05, 0x0f);
		msleep(40);

		/* check DC/DC */
		ret = repaper_read_val(spi, 0x0f);
		if (ret < 0) {
			DRM_DEV_ERROR(dev, "failed to read chip (%d)\n", ret);
			power_off(epd);
			goto out_exit;
		}

		if (ret & 0x40) {
			dc_ok = true;
			break;
		}
	}

	if (!dc_ok) {
		DRM_DEV_ERROR(dev, "dc/dc failed\n");
		power_off(epd);
		goto out_exit;
	}

	/*
	 * Output enable to disable
	 * The userspace driver sets this to 0x04, but the datasheet says 0x06
	 */
	repaper_write_val(spi, 0x02, 0x04);

	epd->enabled = true;
	epd->partial = false;
out_exit:
	drm_dev_exit(idx);
}