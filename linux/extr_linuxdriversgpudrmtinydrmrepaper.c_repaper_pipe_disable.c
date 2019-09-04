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
struct tinydrm_device {int /*<<< orphan*/  dirty_lock; } ;
struct spi_device {int dummy; } ;
struct repaper_epd {int enabled; unsigned int height; scalar_t__ border; struct spi_device* spi; } ;
struct drm_simple_display_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  REPAPER_COMPENSATE ; 
 int /*<<< orphan*/  REPAPER_NORMAL ; 
 struct repaper_epd* epd_from_tinydrm (struct tinydrm_device*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tinydrm_device* pipe_to_tinydrm (struct drm_simple_display_pipe*) ; 
 int /*<<< orphan*/  power_off (struct repaper_epd*) ; 
 int /*<<< orphan*/  repaper_one_line (struct repaper_epd*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repaper_write_val (struct spi_device*,int,int) ; 

__attribute__((used)) static void repaper_pipe_disable(struct drm_simple_display_pipe *pipe)
{
	struct tinydrm_device *tdev = pipe_to_tinydrm(pipe);
	struct repaper_epd *epd = epd_from_tinydrm(tdev);
	struct spi_device *spi = epd->spi;
	unsigned int line;

	DRM_DEBUG_DRIVER("\n");

	mutex_lock(&tdev->dirty_lock);
	epd->enabled = false;
	mutex_unlock(&tdev->dirty_lock);

	/* Nothing frame */
	for (line = 0; line < epd->height; line++)
		repaper_one_line(epd, 0x7fffu, NULL, 0x00, NULL,
				 REPAPER_COMPENSATE);

	/* 2.7" */
	if (epd->border) {
		/* Dummy line */
		repaper_one_line(epd, 0x7fffu, NULL, 0x00, NULL,
				 REPAPER_COMPENSATE);
		msleep(25);
		gpiod_set_value_cansleep(epd->border, 0);
		msleep(200);
		gpiod_set_value_cansleep(epd->border, 1);
	} else {
		/* Border dummy line */
		repaper_one_line(epd, 0x7fffu, NULL, 0x00, NULL,
				 REPAPER_NORMAL);
		msleep(200);
	}

	/* not described in datasheet */
	repaper_write_val(spi, 0x0b, 0x00);
	/* Latch reset turn on */
	repaper_write_val(spi, 0x03, 0x01);
	/* Power off charge pump Vcom */
	repaper_write_val(spi, 0x05, 0x03);
	/* Power off charge pump neg voltage */
	repaper_write_val(spi, 0x05, 0x01);
	msleep(120);
	/* Discharge internal */
	repaper_write_val(spi, 0x04, 0x80);
	/* turn off all charge pumps */
	repaper_write_val(spi, 0x05, 0x00);
	/* Turn off osc */
	repaper_write_val(spi, 0x07, 0x01);
	msleep(50);

	power_off(epd);
}