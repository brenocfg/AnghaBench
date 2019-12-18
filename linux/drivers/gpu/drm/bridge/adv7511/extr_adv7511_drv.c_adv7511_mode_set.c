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
struct drm_display_mode {unsigned int crtc_hsync_start; unsigned int crtc_hdisplay; unsigned int crtc_vsync_start; unsigned int crtc_vdisplay; unsigned int crtc_hsync_end; unsigned int crtc_vsync_end; int flags; int /*<<< orphan*/  clock; } ;
struct adv7511 {int hsync_polarity; int vsync_polarity; scalar_t__ type; int /*<<< orphan*/  f_tmds; int /*<<< orphan*/  curr_mode; int /*<<< orphan*/  regmap; scalar_t__ embedded_sync; } ;
typedef  enum adv7511_sync_polarity { ____Placeholder_adv7511_sync_polarity } adv7511_sync_polarity ;

/* Variables and functions */
 unsigned int ADV7511_LOW_REFRESH_RATE_24HZ ; 
 unsigned int ADV7511_LOW_REFRESH_RATE_25HZ ; 
 unsigned int ADV7511_LOW_REFRESH_RATE_30HZ ; 
 unsigned int ADV7511_LOW_REFRESH_RATE_NONE ; 
 int /*<<< orphan*/  ADV7511_REG_HSYNC_PLACEMENT_MSB ; 
 int /*<<< orphan*/  ADV7511_REG_SYNC_DECODER (int) ; 
 int ADV7511_SYNC_POLARITY_HIGH ; 
 int ADV7511_SYNC_POLARITY_LOW ; 
 scalar_t__ ADV7511_SYNC_POLARITY_PASSTHROUGH ; 
 scalar_t__ ADV7533 ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int /*<<< orphan*/  adv7533_mode_set (struct adv7511*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  drm_mode_copy (int /*<<< orphan*/ *,struct drm_display_mode const*) ; 
 int drm_mode_vrefresh (struct drm_display_mode const*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int,int,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void adv7511_mode_set(struct adv7511 *adv7511,
			     const struct drm_display_mode *mode,
			     const struct drm_display_mode *adj_mode)
{
	unsigned int low_refresh_rate;
	unsigned int hsync_polarity = 0;
	unsigned int vsync_polarity = 0;

	if (adv7511->embedded_sync) {
		unsigned int hsync_offset, hsync_len;
		unsigned int vsync_offset, vsync_len;

		hsync_offset = adj_mode->crtc_hsync_start -
			       adj_mode->crtc_hdisplay;
		vsync_offset = adj_mode->crtc_vsync_start -
			       adj_mode->crtc_vdisplay;
		hsync_len = adj_mode->crtc_hsync_end -
			    adj_mode->crtc_hsync_start;
		vsync_len = adj_mode->crtc_vsync_end -
			    adj_mode->crtc_vsync_start;

		/* The hardware vsync generator has a off-by-one bug */
		vsync_offset += 1;

		regmap_write(adv7511->regmap, ADV7511_REG_HSYNC_PLACEMENT_MSB,
			     ((hsync_offset >> 10) & 0x7) << 5);
		regmap_write(adv7511->regmap, ADV7511_REG_SYNC_DECODER(0),
			     (hsync_offset >> 2) & 0xff);
		regmap_write(adv7511->regmap, ADV7511_REG_SYNC_DECODER(1),
			     ((hsync_offset & 0x3) << 6) |
			     ((hsync_len >> 4) & 0x3f));
		regmap_write(adv7511->regmap, ADV7511_REG_SYNC_DECODER(2),
			     ((hsync_len & 0xf) << 4) |
			     ((vsync_offset >> 6) & 0xf));
		regmap_write(adv7511->regmap, ADV7511_REG_SYNC_DECODER(3),
			     ((vsync_offset & 0x3f) << 2) |
			     ((vsync_len >> 8) & 0x3));
		regmap_write(adv7511->regmap, ADV7511_REG_SYNC_DECODER(4),
			     vsync_len & 0xff);

		hsync_polarity = !(adj_mode->flags & DRM_MODE_FLAG_PHSYNC);
		vsync_polarity = !(adj_mode->flags & DRM_MODE_FLAG_PVSYNC);
	} else {
		enum adv7511_sync_polarity mode_hsync_polarity;
		enum adv7511_sync_polarity mode_vsync_polarity;

		/**
		 * If the input signal is always low or always high we want to
		 * invert or let it passthrough depending on the polarity of the
		 * current mode.
		 **/
		if (adj_mode->flags & DRM_MODE_FLAG_NHSYNC)
			mode_hsync_polarity = ADV7511_SYNC_POLARITY_LOW;
		else
			mode_hsync_polarity = ADV7511_SYNC_POLARITY_HIGH;

		if (adj_mode->flags & DRM_MODE_FLAG_NVSYNC)
			mode_vsync_polarity = ADV7511_SYNC_POLARITY_LOW;
		else
			mode_vsync_polarity = ADV7511_SYNC_POLARITY_HIGH;

		if (adv7511->hsync_polarity != mode_hsync_polarity &&
		    adv7511->hsync_polarity !=
		    ADV7511_SYNC_POLARITY_PASSTHROUGH)
			hsync_polarity = 1;

		if (adv7511->vsync_polarity != mode_vsync_polarity &&
		    adv7511->vsync_polarity !=
		    ADV7511_SYNC_POLARITY_PASSTHROUGH)
			vsync_polarity = 1;
	}

	if (drm_mode_vrefresh(mode) <= 24)
		low_refresh_rate = ADV7511_LOW_REFRESH_RATE_24HZ;
	else if (drm_mode_vrefresh(mode) <= 25)
		low_refresh_rate = ADV7511_LOW_REFRESH_RATE_25HZ;
	else if (drm_mode_vrefresh(mode) <= 30)
		low_refresh_rate = ADV7511_LOW_REFRESH_RATE_30HZ;
	else
		low_refresh_rate = ADV7511_LOW_REFRESH_RATE_NONE;

	regmap_update_bits(adv7511->regmap, 0xfb,
		0x6, low_refresh_rate << 1);
	regmap_update_bits(adv7511->regmap, 0x17,
		0x60, (vsync_polarity << 6) | (hsync_polarity << 5));

	if (adv7511->type == ADV7533)
		adv7533_mode_set(adv7511, adj_mode);

	drm_mode_copy(&adv7511->curr_mode, adj_mode);

	/*
	 * TODO Test first order 4:2:2 to 4:4:4 up conversion method, which is
	 * supposed to give better results.
	 */

	adv7511->f_tmds = mode->clock;
}