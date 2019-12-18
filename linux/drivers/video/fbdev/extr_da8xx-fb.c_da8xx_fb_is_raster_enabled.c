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
 int /*<<< orphan*/  LCD_RASTER_CTRL_REG ; 
 int LCD_RASTER_ENABLE ; 
 int lcdc_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool da8xx_fb_is_raster_enabled(void)
{
	return !!(lcdc_read(LCD_RASTER_CTRL_REG) & LCD_RASTER_ENABLE);
}