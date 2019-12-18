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
struct da8xx_fb_par {unsigned int lcdc_clk_rate; int /*<<< orphan*/  lcdc_clk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int LCD_CLK_DIVISOR (unsigned int) ; 
 int /*<<< orphan*/  LCD_CLK_ENABLE_REG ; 
 int /*<<< orphan*/  LCD_CTRL_REG ; 
 int LCD_RASTER_MODE ; 
 int LCD_V2_CORE_CLK_EN ; 
 int LCD_V2_DMA_CLK_EN ; 
 int LCD_V2_LIDD_CLK_EN ; 
 scalar_t__ LCD_VERSION_2 ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ lcd_revision ; 
 int /*<<< orphan*/  lcdc_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da8xx_fb_config_clk_divider(struct da8xx_fb_par *par,
					      unsigned lcdc_clk_div,
					      unsigned lcdc_clk_rate)
{
	int ret;

	if (par->lcdc_clk_rate != lcdc_clk_rate) {
		ret = clk_set_rate(par->lcdc_clk, lcdc_clk_rate);
		if (ret) {
			dev_err(par->dev,
				"unable to set clock rate at %u\n",
				lcdc_clk_rate);
			return ret;
		}
		par->lcdc_clk_rate = clk_get_rate(par->lcdc_clk);
	}

	/* Configure the LCD clock divisor. */
	lcdc_write(LCD_CLK_DIVISOR(lcdc_clk_div) |
			(LCD_RASTER_MODE & 0x1), LCD_CTRL_REG);

	if (lcd_revision == LCD_VERSION_2)
		lcdc_write(LCD_V2_DMA_CLK_EN | LCD_V2_LIDD_CLK_EN |
				LCD_V2_CORE_CLK_EN, LCD_CLK_ENABLE_REG);

	return 0;
}