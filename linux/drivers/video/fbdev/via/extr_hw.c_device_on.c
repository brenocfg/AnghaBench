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
 int viafb_DVI_ON ; 
 int viafb_LCD_ON ; 
 int /*<<< orphan*/  viafb_dvi_enable () ; 
 int /*<<< orphan*/  viafb_lcd_enable () ; 

__attribute__((used)) static void device_on(void)
{
	if (viafb_DVI_ON == 1)
		viafb_dvi_enable();
	if (viafb_LCD_ON == 1)
		viafb_lcd_enable();
}