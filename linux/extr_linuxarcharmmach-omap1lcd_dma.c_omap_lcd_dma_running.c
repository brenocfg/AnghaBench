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

/* Variables and functions */
 int /*<<< orphan*/  OMAP1610_DMA_LCD_CCR ; 
 int OMAP_DMA_CCR_EN ; 
 int /*<<< orphan*/  OMAP_LCDC_CONTROL ; 
 int OMAP_LCDC_CTRL_LCD_EN ; 
 scalar_t__ cpu_is_omap15xx () ; 
 scalar_t__ cpu_is_omap16xx () ; 
 int omap_readw (int /*<<< orphan*/ ) ; 

int omap_lcd_dma_running(void)
{
	/*
	 * On OMAP1510, internal LCD controller will start the transfer
	 * when it gets enabled, so assume DMA running if LCD enabled.
	 */
	if (cpu_is_omap15xx())
		if (omap_readw(OMAP_LCDC_CONTROL) & OMAP_LCDC_CTRL_LCD_EN)
			return 1;

	/* Check if LCD DMA is running */
	if (cpu_is_omap16xx())
		if (omap_readw(OMAP1610_DMA_LCD_CCR) & OMAP_DMA_CCR_EN)
			return 1;

	return 0;
}