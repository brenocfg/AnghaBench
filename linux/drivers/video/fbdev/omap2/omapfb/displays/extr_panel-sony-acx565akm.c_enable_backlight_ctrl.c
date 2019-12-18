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
struct panel_drv_data {int dummy; } ;

/* Variables and functions */
 int CTRL_DISP_BACKLIGHT_ON ; 
 int CTRL_DISP_BRIGHTNESS_CTRL_ON ; 
 int /*<<< orphan*/  MIPID_CMD_READ_CTRL_DISP ; 
 int /*<<< orphan*/  MIPID_CMD_WRITE_CTRL_DISP ; 
 int /*<<< orphan*/  acx565akm_read (struct panel_drv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  acx565akm_write (struct panel_drv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void enable_backlight_ctrl(struct panel_drv_data *ddata, int enable)
{
	u16 ctrl;

	acx565akm_read(ddata, MIPID_CMD_READ_CTRL_DISP, (u8 *)&ctrl, 1);
	if (enable) {
		ctrl |= CTRL_DISP_BRIGHTNESS_CTRL_ON |
			CTRL_DISP_BACKLIGHT_ON;
	} else {
		ctrl &= ~(CTRL_DISP_BRIGHTNESS_CTRL_ON |
			  CTRL_DISP_BACKLIGHT_ON);
	}

	ctrl |= 1 << 8;
	acx565akm_write(ddata, MIPID_CMD_WRITE_CTRL_DISP, (u8 *)&ctrl, 2);
}