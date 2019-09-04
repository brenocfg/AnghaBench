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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  ext_ctrl; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP1610_DMA_LCD_CCR ; 
 int /*<<< orphan*/  OMAP1610_DMA_LCD_CTRL ; 
 scalar_t__ cpu_is_omap15xx () ; 
 TYPE_1__ lcd_dma ; 
 int omap_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writew (int,int /*<<< orphan*/ ) ; 

void omap_stop_lcd_dma(void)
{
	u16 w;

	lcd_dma.active = 0;
	if (cpu_is_omap15xx() || !lcd_dma.ext_ctrl)
		return;

	w = omap_readw(OMAP1610_DMA_LCD_CCR);
	w &= ~(1 << 7);
	omap_writew(w, OMAP1610_DMA_LCD_CCR);

	w = omap_readw(OMAP1610_DMA_LCD_CTRL);
	w &= ~(1 << 8);
	omap_writew(w, OMAP1610_DMA_LCD_CTRL);
}