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
struct TYPE_2__ {int /*<<< orphan*/  lcd_ck; int /*<<< orphan*/  fbdev; int /*<<< orphan*/  ext_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_LCDC_IRQ ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_fbmem () ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_palette_ram () ; 
 TYPE_1__ lcdc ; 
 int /*<<< orphan*/  omap_free_lcd_dma () ; 

__attribute__((used)) static void omap_lcdc_cleanup(void)
{
	if (!lcdc.ext_mode)
		free_palette_ram();
	free_fbmem();
	omap_free_lcd_dma();
	free_irq(OMAP_LCDC_IRQ, lcdc.fbdev);
	clk_disable(lcdc.lcd_ck);
	clk_put(lcdc.lcd_ck);
}