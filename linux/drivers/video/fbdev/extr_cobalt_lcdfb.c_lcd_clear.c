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
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCD_CLEAR ; 
 int /*<<< orphan*/  LCD_PRERESET ; 
 int /*<<< orphan*/  LCD_RESET ; 
 int /*<<< orphan*/  lcd_write_control (struct fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void lcd_clear(struct fb_info *info)
{
	int i;

	for (i = 0; i < 4; i++) {
		udelay(150);

		lcd_write_control(info, LCD_PRERESET);
	}

	udelay(150);

	lcd_write_control(info, LCD_CLEAR);

	udelay(150);

	lcd_write_control(info, LCD_RESET);
}