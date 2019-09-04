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
typedef  int u8 ;
typedef  int u32 ;
struct sun4i_tcon {int dclk_min_div; int dclk_max_div; int /*<<< orphan*/  regs; } ;
struct mipi_dsi_device {int lanes; int /*<<< orphan*/  format; } ;
struct drm_display_mode {int htotal; int crtc_vtotal; int crtc_vdisplay; int crtc_htotal; int crtc_clock; int /*<<< orphan*/  vdisplay; scalar_t__ hdisplay; } ;

/* Variables and functions */
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int SUN4I_TCON0_CPU_IF_MODE_DSI ; 
 int /*<<< orphan*/  SUN4I_TCON0_CPU_IF_REG ; 
 int SUN4I_TCON0_CPU_IF_TRI_EN ; 
 int SUN4I_TCON0_CPU_IF_TRI_FIFO_EN ; 
 int SUN4I_TCON0_CPU_IF_TRI_FIFO_FLUSH ; 
 int SUN4I_TCON0_CPU_TRI0_BLOCK_SIZE (scalar_t__) ; 
 int SUN4I_TCON0_CPU_TRI0_BLOCK_SPACE (int) ; 
 int /*<<< orphan*/  SUN4I_TCON0_CPU_TRI0_REG ; 
 int SUN4I_TCON0_CPU_TRI1_BLOCK_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_TCON0_CPU_TRI1_REG ; 
 int /*<<< orphan*/  SUN4I_TCON0_CPU_TRI2_REG ; 
 int SUN4I_TCON0_CPU_TRI2_START_DELAY (int) ; 
 int SUN4I_TCON0_CPU_TRI2_TRANS_START_SET (int) ; 
 int /*<<< orphan*/  SUN4I_TCON0_CTL_IF_8080 ; 
 int /*<<< orphan*/  SUN4I_TCON0_CTL_IF_MASK ; 
 int /*<<< orphan*/  SUN4I_TCON0_CTL_REG ; 
 int /*<<< orphan*/  SUN4I_TCON0_DCLK_REG ; 
 int /*<<< orphan*/  SUN4I_TCON0_IO_TRI_REG ; 
 int SUN4I_TCON_ECC_FIFO_EN ; 
 int /*<<< orphan*/  SUN4I_TCON_ECC_FIFO_REG ; 
 int SUN4I_TCON_SAFE_PERIOD_MODE (int) ; 
 int SUN4I_TCON_SAFE_PERIOD_NUM (int) ; 
 int /*<<< orphan*/  SUN4I_TCON_SAFE_PERIOD_REG ; 
 int mipi_dsi_pixel_format_to_bpp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sun4i_tcon0_mode_set_common (struct sun4i_tcon*,struct drm_display_mode const*) ; 

__attribute__((used)) static void sun4i_tcon0_mode_set_cpu(struct sun4i_tcon *tcon,
				     struct mipi_dsi_device *device,
				     const struct drm_display_mode *mode)
{
	u8 bpp = mipi_dsi_pixel_format_to_bpp(device->format);
	u8 lanes = device->lanes;
	u32 block_space, start_delay;
	u32 tcon_div;

	tcon->dclk_min_div = 4;
	tcon->dclk_max_div = 127;

	sun4i_tcon0_mode_set_common(tcon, mode);

	regmap_update_bits(tcon->regs, SUN4I_TCON0_CTL_REG,
			   SUN4I_TCON0_CTL_IF_MASK,
			   SUN4I_TCON0_CTL_IF_8080);

	regmap_write(tcon->regs, SUN4I_TCON_ECC_FIFO_REG,
		     SUN4I_TCON_ECC_FIFO_EN);

	regmap_write(tcon->regs, SUN4I_TCON0_CPU_IF_REG,
		     SUN4I_TCON0_CPU_IF_MODE_DSI |
		     SUN4I_TCON0_CPU_IF_TRI_FIFO_FLUSH |
		     SUN4I_TCON0_CPU_IF_TRI_FIFO_EN |
		     SUN4I_TCON0_CPU_IF_TRI_EN);

	/*
	 * This looks suspicious, but it works...
	 *
	 * The datasheet says that this should be set higher than 20 *
	 * pixel cycle, but it's not clear what a pixel cycle is.
	 */
	regmap_read(tcon->regs, SUN4I_TCON0_DCLK_REG, &tcon_div);
	tcon_div &= GENMASK(6, 0);
	block_space = mode->htotal * bpp / (tcon_div * lanes);
	block_space -= mode->hdisplay + 40;

	regmap_write(tcon->regs, SUN4I_TCON0_CPU_TRI0_REG,
		     SUN4I_TCON0_CPU_TRI0_BLOCK_SPACE(block_space) |
		     SUN4I_TCON0_CPU_TRI0_BLOCK_SIZE(mode->hdisplay));

	regmap_write(tcon->regs, SUN4I_TCON0_CPU_TRI1_REG,
		     SUN4I_TCON0_CPU_TRI1_BLOCK_NUM(mode->vdisplay));

	start_delay = (mode->crtc_vtotal - mode->crtc_vdisplay - 10 - 1);
	start_delay = start_delay * mode->crtc_htotal * 149;
	start_delay = start_delay / (mode->crtc_clock / 1000) / 8;
	regmap_write(tcon->regs, SUN4I_TCON0_CPU_TRI2_REG,
		     SUN4I_TCON0_CPU_TRI2_TRANS_START_SET(10) |
		     SUN4I_TCON0_CPU_TRI2_START_DELAY(start_delay));

	/*
	 * The Allwinner BSP has a comment that the period should be
	 * the display clock * 15, but uses an hardcoded 3000...
	 */
	regmap_write(tcon->regs, SUN4I_TCON_SAFE_PERIOD_REG,
		     SUN4I_TCON_SAFE_PERIOD_NUM(3000) |
		     SUN4I_TCON_SAFE_PERIOD_MODE(3));

	/* Enable the output on the pins */
	regmap_write(tcon->regs, SUN4I_TCON0_IO_TRI_REG,
		     0xe0000000);
}