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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct sun4i_tcon {int dclk_min_div; int dclk_max_div; int /*<<< orphan*/  regs; TYPE_1__* quirks; } ;
struct drm_display_mode {unsigned int crtc_htotal; unsigned int crtc_hsync_start; unsigned int crtc_vtotal; unsigned int crtc_vsync_start; unsigned int crtc_hsync_end; unsigned int crtc_vsync_end; int flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  has_channel_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,unsigned int,unsigned int) ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int SUN4I_TCON0_BASIC1_H_BACKPORCH (unsigned int) ; 
 int SUN4I_TCON0_BASIC1_H_TOTAL (unsigned int) ; 
 int /*<<< orphan*/  SUN4I_TCON0_BASIC1_REG ; 
 int /*<<< orphan*/  SUN4I_TCON0_BASIC2_REG ; 
 int SUN4I_TCON0_BASIC2_V_BACKPORCH (unsigned int) ; 
 int SUN4I_TCON0_BASIC2_V_TOTAL (int) ; 
 int SUN4I_TCON0_BASIC3_H_SYNC (unsigned int) ; 
 int /*<<< orphan*/  SUN4I_TCON0_BASIC3_REG ; 
 int SUN4I_TCON0_BASIC3_V_SYNC (unsigned int) ; 
 int SUN4I_TCON0_CTL_CLK_DELAY (int /*<<< orphan*/ ) ; 
 int SUN4I_TCON0_CTL_CLK_DELAY_MASK ; 
 int /*<<< orphan*/  SUN4I_TCON0_CTL_REG ; 
 int SUN4I_TCON0_IO_POL_HSYNC_POSITIVE ; 
 int /*<<< orphan*/  SUN4I_TCON0_IO_POL_REG ; 
 int SUN4I_TCON0_IO_POL_VSYNC_POSITIVE ; 
 int /*<<< orphan*/  SUN4I_TCON0_IO_TRI_REG ; 
 int SUN4I_TCON_GCTL_IOMAP_MASK ; 
 int SUN4I_TCON_GCTL_IOMAP_TCON0 ; 
 int /*<<< orphan*/  SUN4I_TCON_GCTL_REG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sun4i_tcon0_mode_set_common (struct sun4i_tcon*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  sun4i_tcon_get_clk_delay (struct drm_display_mode const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4i_tcon0_mode_set_rgb(struct sun4i_tcon *tcon,
				     const struct drm_display_mode *mode)
{
	unsigned int bp, hsync, vsync;
	u8 clk_delay;
	u32 val = 0;

	WARN_ON(!tcon->quirks->has_channel_0);

	tcon->dclk_min_div = 6;
	tcon->dclk_max_div = 127;
	sun4i_tcon0_mode_set_common(tcon, mode);

	/* Adjust clock delay */
	clk_delay = sun4i_tcon_get_clk_delay(mode, 0);
	regmap_update_bits(tcon->regs, SUN4I_TCON0_CTL_REG,
			   SUN4I_TCON0_CTL_CLK_DELAY_MASK,
			   SUN4I_TCON0_CTL_CLK_DELAY(clk_delay));

	/*
	 * This is called a backporch in the register documentation,
	 * but it really is the back porch + hsync
	 */
	bp = mode->crtc_htotal - mode->crtc_hsync_start;
	DRM_DEBUG_DRIVER("Setting horizontal total %d, backporch %d\n",
			 mode->crtc_htotal, bp);

	/* Set horizontal display timings */
	regmap_write(tcon->regs, SUN4I_TCON0_BASIC1_REG,
		     SUN4I_TCON0_BASIC1_H_TOTAL(mode->crtc_htotal) |
		     SUN4I_TCON0_BASIC1_H_BACKPORCH(bp));

	/*
	 * This is called a backporch in the register documentation,
	 * but it really is the back porch + hsync
	 */
	bp = mode->crtc_vtotal - mode->crtc_vsync_start;
	DRM_DEBUG_DRIVER("Setting vertical total %d, backporch %d\n",
			 mode->crtc_vtotal, bp);

	/* Set vertical display timings */
	regmap_write(tcon->regs, SUN4I_TCON0_BASIC2_REG,
		     SUN4I_TCON0_BASIC2_V_TOTAL(mode->crtc_vtotal * 2) |
		     SUN4I_TCON0_BASIC2_V_BACKPORCH(bp));

	/* Set Hsync and Vsync length */
	hsync = mode->crtc_hsync_end - mode->crtc_hsync_start;
	vsync = mode->crtc_vsync_end - mode->crtc_vsync_start;
	DRM_DEBUG_DRIVER("Setting HSYNC %d, VSYNC %d\n", hsync, vsync);
	regmap_write(tcon->regs, SUN4I_TCON0_BASIC3_REG,
		     SUN4I_TCON0_BASIC3_V_SYNC(vsync) |
		     SUN4I_TCON0_BASIC3_H_SYNC(hsync));

	/* Setup the polarity of the various signals */
	if (mode->flags & DRM_MODE_FLAG_PHSYNC)
		val |= SUN4I_TCON0_IO_POL_HSYNC_POSITIVE;

	if (mode->flags & DRM_MODE_FLAG_PVSYNC)
		val |= SUN4I_TCON0_IO_POL_VSYNC_POSITIVE;

	regmap_update_bits(tcon->regs, SUN4I_TCON0_IO_POL_REG,
			   SUN4I_TCON0_IO_POL_HSYNC_POSITIVE | SUN4I_TCON0_IO_POL_VSYNC_POSITIVE,
			   val);

	/* Map output pins to channel 0 */
	regmap_update_bits(tcon->regs, SUN4I_TCON_GCTL_REG,
			   SUN4I_TCON_GCTL_IOMAP_MASK,
			   SUN4I_TCON_GCTL_IOMAP_TCON0);

	/* Enable the output on the pins */
	regmap_write(tcon->regs, SUN4I_TCON0_IO_TRI_REG, 0);
}