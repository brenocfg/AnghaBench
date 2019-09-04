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
struct panel_drv_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPID_CMD_WRITE_DISP_BRIGHTNESS ; 
 int /*<<< orphan*/  acx565akm_write (struct panel_drv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  enable_backlight_ctrl (struct panel_drv_data*,int) ; 

__attribute__((used)) static void acx565akm_set_brightness(struct panel_drv_data *ddata, int level)
{
	int bv;

	bv = level | (1 << 8);
	acx565akm_write(ddata, MIPID_CMD_WRITE_DISP_BRIGHTNESS, (u8 *)&bv, 2);

	if (level)
		enable_backlight_ctrl(ddata, 1);
	else
		enable_backlight_ctrl(ddata, 0);
}