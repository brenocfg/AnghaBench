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

/* Variables and functions */
 int /*<<< orphan*/  LCD_RASTER_TIMING_0_REG ; 
 int /*<<< orphan*/  LCD_RASTER_TIMING_2_REG ; 
 scalar_t__ LCD_VERSION_2 ; 
 scalar_t__ lcd_revision ; 
 int lcdc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lcd_cfg_horizontal_sync(int back_porch, int pulse_width,
		int front_porch)
{
	u32 reg;

	reg = lcdc_read(LCD_RASTER_TIMING_0_REG) & 0x3ff;
	reg |= (((back_porch-1) & 0xff) << 24)
	    | (((front_porch-1) & 0xff) << 16)
	    | (((pulse_width-1) & 0x3f) << 10);
	lcdc_write(reg, LCD_RASTER_TIMING_0_REG);

	/*
	 * LCDC Version 2 adds some extra bits that increase the allowable
	 * size of the horizontal timing registers.
	 * remember that the registers use 0 to represent 1 so all values
	 * that get set into register need to be decremented by 1
	 */
	if (lcd_revision == LCD_VERSION_2) {
		/* Mask off the bits we want to change */
		reg = lcdc_read(LCD_RASTER_TIMING_2_REG) & ~0x780000ff;
		reg |= ((front_porch-1) & 0x300) >> 8;
		reg |= ((back_porch-1) & 0x300) >> 4;
		reg |= ((pulse_width-1) & 0x3c0) << 21;
		lcdc_write(reg, LCD_RASTER_TIMING_2_REG);
	}
}