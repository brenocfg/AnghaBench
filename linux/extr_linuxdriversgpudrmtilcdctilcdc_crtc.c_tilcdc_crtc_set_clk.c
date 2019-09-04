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
struct tilcdc_drm_private {int rev; int /*<<< orphan*/  clk; } ;
struct tilcdc_crtc {unsigned long lcd_fck_rate; } ;
struct drm_device {int /*<<< orphan*/  dev; struct tilcdc_drm_private* dev_private; } ;
struct TYPE_2__ {int clock; } ;
struct drm_crtc {TYPE_1__ mode; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,unsigned long,int,unsigned int) ; 
 unsigned int DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 
 int LCDC_CLK_DIVISOR (unsigned int) ; 
 int /*<<< orphan*/  LCDC_CLK_ENABLE_REG ; 
 int /*<<< orphan*/  LCDC_CTRL_REG ; 
 int LCDC_RASTER_MODE ; 
 int LCDC_V2_CORE_CLK_EN ; 
 int LCDC_V2_DMA_CLK_EN ; 
 int LCDC_V2_LIDD_CLK_EN ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 int tilcdc_pclk_diff (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  tilcdc_set (struct drm_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tilcdc_write (struct drm_device*,int /*<<< orphan*/ ,int) ; 
 struct tilcdc_crtc* to_tilcdc_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void tilcdc_crtc_set_clk(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct tilcdc_drm_private *priv = dev->dev_private;
	struct tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);
	unsigned long clk_rate, real_rate, req_rate;
	unsigned int clkdiv;
	int ret;

	clkdiv = 2; /* first try using a standard divider of 2 */

	/* mode.clock is in KHz, set_rate wants parameter in Hz */
	req_rate = crtc->mode.clock * 1000;

	ret = clk_set_rate(priv->clk, req_rate * clkdiv);
	clk_rate = clk_get_rate(priv->clk);
	if (ret < 0 || tilcdc_pclk_diff(req_rate, clk_rate) > 5) {
		/*
		 * If we fail to set the clock rate (some architectures don't
		 * use the common clock framework yet and may not implement
		 * all the clk API calls for every clock), try the next best
		 * thing: adjusting the clock divider, unless clk_get_rate()
		 * failed as well.
		 */
		if (!clk_rate) {
			/* Nothing more we can do. Just bail out. */
			dev_err(dev->dev,
				"failed to set the pixel clock - unable to read current lcdc clock rate\n");
			return;
		}

		clkdiv = DIV_ROUND_CLOSEST(clk_rate, req_rate);

		/*
		 * Emit a warning if the real clock rate resulting from the
		 * calculated divider differs much from the requested rate.
		 *
		 * 5% is an arbitrary value - LCDs are usually quite tolerant
		 * about pixel clock rates.
		 */
		real_rate = clkdiv * req_rate;

		if (tilcdc_pclk_diff(clk_rate, real_rate) > 5) {
			dev_warn(dev->dev,
				 "effective pixel clock rate (%luHz) differs from the calculated rate (%luHz)\n",
				 clk_rate, real_rate);
		}
	}

	tilcdc_crtc->lcd_fck_rate = clk_rate;

	DBG("lcd_clk=%u, mode clock=%d, div=%u",
	    tilcdc_crtc->lcd_fck_rate, crtc->mode.clock, clkdiv);

	/* Configure the LCD clock divisor. */
	tilcdc_write(dev, LCDC_CTRL_REG, LCDC_CLK_DIVISOR(clkdiv) |
		     LCDC_RASTER_MODE);

	if (priv->rev == 2)
		tilcdc_set(dev, LCDC_CLK_ENABLE_REG,
				LCDC_V2_DMA_CLK_EN | LCDC_V2_LIDD_CLK_EN |
				LCDC_V2_CORE_CLK_EN);
}