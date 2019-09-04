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
typedef  int u32 ;
typedef  int u16 ;
struct sun6i_dsi {int /*<<< orphan*/  regs; struct mipi_dsi_device* device; } ;
struct mipi_dsi_device {int /*<<< orphan*/  format; } ;
struct drm_display_mode {int hsync_end; int hdisplay; } ;

/* Variables and functions */
 int SUN6I_DSI_TCON_DRQ_ENABLE_MODE ; 
 int /*<<< orphan*/  SUN6I_DSI_TCON_DRQ_REG ; 
 int SUN6I_DSI_TCON_DRQ_SET (int) ; 
 int mipi_dsi_pixel_format_to_bpp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sun6i_dsi_setup_burst(struct sun6i_dsi *dsi,
				  struct drm_display_mode *mode)
{
	struct mipi_dsi_device *device = dsi->device;
	u32 val = 0;

	if ((mode->hsync_end - mode->hdisplay) > 20) {
		/* Maaaaaagic */
		u16 drq = (mode->hsync_end - mode->hdisplay) - 20;

		drq *= mipi_dsi_pixel_format_to_bpp(device->format);
		drq /= 32;

		val = (SUN6I_DSI_TCON_DRQ_ENABLE_MODE |
		       SUN6I_DSI_TCON_DRQ_SET(drq));
	}

	regmap_write(dsi->regs, SUN6I_DSI_TCON_DRQ_REG, val);
}