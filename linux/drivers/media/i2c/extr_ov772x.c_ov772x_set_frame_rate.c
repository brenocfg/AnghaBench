#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ov772x_win_size {unsigned int sizeimage; } ;
struct ov772x_priv {int /*<<< orphan*/  regmap; int /*<<< orphan*/  clk; } ;
struct ov772x_color_format {int com7; } ;
struct TYPE_3__ {unsigned int mult; int com4; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CLKRC ; 
 int CLKRC_DIV (unsigned int) ; 
 int CLKRC_RESERVED ; 
 int /*<<< orphan*/  COM4 ; 
 int COM4_RESERVED ; 
 unsigned int DIV_ROUND_CLOSEST (unsigned long,unsigned int) ; 
#define  OFMT_BRAW 130 
 int OFMT_MASK ; 
#define  OFMT_RGB 129 
#define  OFMT_YUV 128 
 unsigned int abs (unsigned int) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 TYPE_1__* ov772x_pll ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ov772x_set_frame_rate(struct ov772x_priv *priv,
				 unsigned int fps,
				 const struct ov772x_color_format *cfmt,
				 const struct ov772x_win_size *win)
{
	unsigned long fin = clk_get_rate(priv->clk);
	unsigned int best_diff;
	unsigned int fsize;
	unsigned int pclk;
	unsigned int diff;
	unsigned int i;
	u8 clkrc = 0;
	u8 com4 = 0;
	int ret;

	/* Use image size (with blankings) to calculate desired pixel clock. */
	switch (cfmt->com7 & OFMT_MASK) {
	case OFMT_BRAW:
		fsize = win->sizeimage;
		break;
	case OFMT_RGB:
	case OFMT_YUV:
	default:
		fsize = win->sizeimage * 2;
		break;
	}

	pclk = fps * fsize;

	/*
	 * Pixel clock generation circuit is pretty simple:
	 *
	 * Fin -> [ / CLKRC_div] -> [ * PLL_mult] -> pclk
	 *
	 * Try to approximate the desired pixel clock testing all available
	 * PLL multipliers (1x, 4x, 6x, 8x) and calculate corresponding
	 * divisor with:
	 *
	 * div = PLL_mult * Fin / pclk
	 *
	 * and re-calculate the pixel clock using it:
	 *
	 * pclk = Fin * PLL_mult / CLKRC_div
	 *
	 * Choose the PLL_mult and CLKRC_div pair that gives a pixel clock
	 * closer to the desired one.
	 *
	 * The desired pixel clock is calculated using a known frame size
	 * (blanking included) and FPS.
	 */
	best_diff = ~0L;
	for (i = 0; i < ARRAY_SIZE(ov772x_pll); i++) {
		unsigned int pll_mult = ov772x_pll[i].mult;
		unsigned int pll_out = pll_mult * fin;
		unsigned int t_pclk;
		unsigned int div;

		if (pll_out < pclk)
			continue;

		div = DIV_ROUND_CLOSEST(pll_out, pclk);
		t_pclk = DIV_ROUND_CLOSEST(fin * pll_mult, div);
		diff = abs(pclk - t_pclk);
		if (diff < best_diff) {
			best_diff = diff;
			clkrc = CLKRC_DIV(div);
			com4 = ov772x_pll[i].com4;
		}
	}

	ret = regmap_write(priv->regmap, COM4, com4 | COM4_RESERVED);
	if (ret < 0)
		return ret;

	ret = regmap_write(priv->regmap, CLKRC, clkrc | CLKRC_RESERVED);
	if (ret < 0)
		return ret;

	return 0;
}