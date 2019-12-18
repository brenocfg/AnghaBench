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
struct lcd_device {int dummy; } ;

/* Variables and functions */
 int AMS_DELTA_LCD_POWER ; 
 int AMS_DELTA_MAX_CONTRAST ; 
 int FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  OMAP_PWL_CLK_ENABLE ; 
 int /*<<< orphan*/  OMAP_PWL_ENABLE ; 
 int ams_delta_lcd ; 
 int /*<<< orphan*/  omap_writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ams_delta_lcd_set_power(struct lcd_device *dev, int power)
{
	if (power == FB_BLANK_UNBLANK) {
		if (!(ams_delta_lcd & AMS_DELTA_LCD_POWER)) {
			omap_writeb(ams_delta_lcd & AMS_DELTA_MAX_CONTRAST,
					OMAP_PWL_ENABLE);
			omap_writeb(1, OMAP_PWL_CLK_ENABLE);
			ams_delta_lcd |= AMS_DELTA_LCD_POWER;
		}
	} else {
		if (ams_delta_lcd & AMS_DELTA_LCD_POWER) {
			omap_writeb(0, OMAP_PWL_ENABLE);
			omap_writeb(0, OMAP_PWL_CLK_ENABLE);
			ams_delta_lcd &= ~AMS_DELTA_LCD_POWER;
		}
	}
	return 0;
}