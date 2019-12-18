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
typedef  scalar_t__ u32 ;
struct sun4i_tcon {int /*<<< orphan*/  regs; int /*<<< orphan*/  sclk1; TYPE_1__* quirks; } ;
struct drm_display_mode {int crtc_clock; int flags; unsigned int crtc_htotal; unsigned int crtc_hsync_start; unsigned int htotal; unsigned int crtc_vtotal; unsigned int crtc_vsync_start; unsigned int vtotal; unsigned int crtc_hsync_end; unsigned int crtc_vsync_end; int /*<<< orphan*/  crtc_vdisplay; int /*<<< orphan*/  crtc_hdisplay; } ;
struct TYPE_2__ {int /*<<< orphan*/  has_channel_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,unsigned int,unsigned int) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int /*<<< orphan*/  SUN4I_TCON1_BASIC0_REG ; 
 int SUN4I_TCON1_BASIC0_X (int /*<<< orphan*/ ) ; 
 int SUN4I_TCON1_BASIC0_Y (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_TCON1_BASIC1_REG ; 
 int SUN4I_TCON1_BASIC1_X (int /*<<< orphan*/ ) ; 
 int SUN4I_TCON1_BASIC1_Y (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_TCON1_BASIC2_REG ; 
 int SUN4I_TCON1_BASIC2_X (int /*<<< orphan*/ ) ; 
 int SUN4I_TCON1_BASIC2_Y (int /*<<< orphan*/ ) ; 
 int SUN4I_TCON1_BASIC3_H_BACKPORCH (unsigned int) ; 
 int SUN4I_TCON1_BASIC3_H_TOTAL (unsigned int) ; 
 int /*<<< orphan*/  SUN4I_TCON1_BASIC3_REG ; 
 int /*<<< orphan*/  SUN4I_TCON1_BASIC4_REG ; 
 int SUN4I_TCON1_BASIC4_V_BACKPORCH (unsigned int) ; 
 int SUN4I_TCON1_BASIC4_V_TOTAL (unsigned int) ; 
 int SUN4I_TCON1_BASIC5_H_SYNC (unsigned int) ; 
 int /*<<< orphan*/  SUN4I_TCON1_BASIC5_REG ; 
 int SUN4I_TCON1_BASIC5_V_SYNC (unsigned int) ; 
 scalar_t__ SUN4I_TCON1_CTL_CLK_DELAY (int /*<<< orphan*/ ) ; 
 scalar_t__ SUN4I_TCON1_CTL_CLK_DELAY_MASK ; 
 scalar_t__ SUN4I_TCON1_CTL_INTERLACE_ENABLE ; 
 int /*<<< orphan*/  SUN4I_TCON1_CTL_REG ; 
 scalar_t__ SUN4I_TCON_GCTL_IOMAP_MASK ; 
 scalar_t__ SUN4I_TCON_GCTL_IOMAP_TCON1 ; 
 int /*<<< orphan*/  SUN4I_TCON_GCTL_REG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sun4i_tcon_get_clk_delay (struct drm_display_mode const*,int) ; 

__attribute__((used)) static void sun4i_tcon1_mode_set(struct sun4i_tcon *tcon,
				 const struct drm_display_mode *mode)
{
	unsigned int bp, hsync, vsync, vtotal;
	u8 clk_delay;
	u32 val;

	WARN_ON(!tcon->quirks->has_channel_1);

	/* Configure the dot clock */
	clk_set_rate(tcon->sclk1, mode->crtc_clock * 1000);

	/* Adjust clock delay */
	clk_delay = sun4i_tcon_get_clk_delay(mode, 1);
	regmap_update_bits(tcon->regs, SUN4I_TCON1_CTL_REG,
			   SUN4I_TCON1_CTL_CLK_DELAY_MASK,
			   SUN4I_TCON1_CTL_CLK_DELAY(clk_delay));

	/* Set interlaced mode */
	if (mode->flags & DRM_MODE_FLAG_INTERLACE)
		val = SUN4I_TCON1_CTL_INTERLACE_ENABLE;
	else
		val = 0;
	regmap_update_bits(tcon->regs, SUN4I_TCON1_CTL_REG,
			   SUN4I_TCON1_CTL_INTERLACE_ENABLE,
			   val);

	/* Set the input resolution */
	regmap_write(tcon->regs, SUN4I_TCON1_BASIC0_REG,
		     SUN4I_TCON1_BASIC0_X(mode->crtc_hdisplay) |
		     SUN4I_TCON1_BASIC0_Y(mode->crtc_vdisplay));

	/* Set the upscaling resolution */
	regmap_write(tcon->regs, SUN4I_TCON1_BASIC1_REG,
		     SUN4I_TCON1_BASIC1_X(mode->crtc_hdisplay) |
		     SUN4I_TCON1_BASIC1_Y(mode->crtc_vdisplay));

	/* Set the output resolution */
	regmap_write(tcon->regs, SUN4I_TCON1_BASIC2_REG,
		     SUN4I_TCON1_BASIC2_X(mode->crtc_hdisplay) |
		     SUN4I_TCON1_BASIC2_Y(mode->crtc_vdisplay));

	/* Set horizontal display timings */
	bp = mode->crtc_htotal - mode->crtc_hsync_start;
	DRM_DEBUG_DRIVER("Setting horizontal total %d, backporch %d\n",
			 mode->htotal, bp);
	regmap_write(tcon->regs, SUN4I_TCON1_BASIC3_REG,
		     SUN4I_TCON1_BASIC3_H_TOTAL(mode->crtc_htotal) |
		     SUN4I_TCON1_BASIC3_H_BACKPORCH(bp));

	bp = mode->crtc_vtotal - mode->crtc_vsync_start;
	DRM_DEBUG_DRIVER("Setting vertical total %d, backporch %d\n",
			 mode->crtc_vtotal, bp);

	/*
	 * The vertical resolution needs to be doubled in all
	 * cases. We could use crtc_vtotal and always multiply by two,
	 * but that leads to a rounding error in interlace when vtotal
	 * is odd.
	 *
	 * This happens with TV's PAL for example, where vtotal will
	 * be 625, crtc_vtotal 312, and thus crtc_vtotal * 2 will be
	 * 624, which apparently confuses the hardware.
	 *
	 * To work around this, we will always use vtotal, and
	 * multiply by two only if we're not in interlace.
	 */
	vtotal = mode->vtotal;
	if (!(mode->flags & DRM_MODE_FLAG_INTERLACE))
		vtotal = vtotal * 2;

	/* Set vertical display timings */
	regmap_write(tcon->regs, SUN4I_TCON1_BASIC4_REG,
		     SUN4I_TCON1_BASIC4_V_TOTAL(vtotal) |
		     SUN4I_TCON1_BASIC4_V_BACKPORCH(bp));

	/* Set Hsync and Vsync length */
	hsync = mode->crtc_hsync_end - mode->crtc_hsync_start;
	vsync = mode->crtc_vsync_end - mode->crtc_vsync_start;
	DRM_DEBUG_DRIVER("Setting HSYNC %d, VSYNC %d\n", hsync, vsync);
	regmap_write(tcon->regs, SUN4I_TCON1_BASIC5_REG,
		     SUN4I_TCON1_BASIC5_V_SYNC(vsync) |
		     SUN4I_TCON1_BASIC5_H_SYNC(hsync));

	/* Map output pins to channel 1 */
	regmap_update_bits(tcon->regs, SUN4I_TCON_GCTL_REG,
			   SUN4I_TCON_GCTL_IOMAP_MASK,
			   SUN4I_TCON_GCTL_IOMAP_TCON1);
}