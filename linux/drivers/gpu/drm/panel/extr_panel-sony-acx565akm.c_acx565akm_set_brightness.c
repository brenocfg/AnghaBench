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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct acx565akm_panel {int dummy; } ;

/* Variables and functions */
 int CTRL_DISP_BACKLIGHT_ON ; 
 int CTRL_DISP_BRIGHTNESS_CTRL_ON ; 
 int /*<<< orphan*/  MIPI_DCS_GET_CONTROL_DISPLAY ; 
 int /*<<< orphan*/  MIPI_DCS_SET_DISPLAY_BRIGHTNESS ; 
 int /*<<< orphan*/  MIPI_DCS_WRITE_CONTROL_DISPLAY ; 
 int /*<<< orphan*/  acx565akm_read (struct acx565akm_panel*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  acx565akm_write (struct acx565akm_panel*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void acx565akm_set_brightness(struct acx565akm_panel *lcd, int level)
{
	u16 ctrl;
	int bv;

	bv = level | (1 << 8);
	acx565akm_write(lcd, MIPI_DCS_SET_DISPLAY_BRIGHTNESS, (u8 *)&bv, 2);

	acx565akm_read(lcd, MIPI_DCS_GET_CONTROL_DISPLAY, (u8 *)&ctrl, 1);
	if (level)
		ctrl |= CTRL_DISP_BRIGHTNESS_CTRL_ON |
			CTRL_DISP_BACKLIGHT_ON;
	else
		ctrl &= ~(CTRL_DISP_BRIGHTNESS_CTRL_ON |
			  CTRL_DISP_BACKLIGHT_ON);

	ctrl |= 1 << 8;
	acx565akm_write(lcd, MIPI_DCS_WRITE_CONTROL_DISPLAY, (u8 *)&ctrl, 2);
}