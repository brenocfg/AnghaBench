#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mmp_camera_platform_data {int /*<<< orphan*/  sensor_reset_gpio; int /*<<< orphan*/  sensor_power_gpio; } ;
struct mmp_camera {TYPE_2__* pdev; } ;
struct mcam_camera {int dummy; } ;
struct TYPE_3__ {struct mmp_camera_platform_data* platform_data; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CLKCTRL ; 
 int /*<<< orphan*/  REG_CTRL1 ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mcam_clk_enable (struct mcam_camera*) ; 
 int /*<<< orphan*/  mcam_reg_clear_bit (struct mcam_camera*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mcam_reg_write (struct mcam_camera*,int /*<<< orphan*/ ,int) ; 
 struct mmp_camera* mcam_to_cam (struct mcam_camera*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmpcam_power_up_ctlr (struct mmp_camera*) ; 

__attribute__((used)) static int mmpcam_power_up(struct mcam_camera *mcam)
{
	struct mmp_camera *cam = mcam_to_cam(mcam);
	struct mmp_camera_platform_data *pdata;

/*
 * Turn on power and clocks to the controller.
 */
	mmpcam_power_up_ctlr(cam);
/*
 * Provide power to the sensor.
 */
	mcam_reg_write(mcam, REG_CLKCTRL, 0x60000002);
	pdata = cam->pdev->dev.platform_data;
	gpio_set_value(pdata->sensor_power_gpio, 1);
	mdelay(5);
	mcam_reg_clear_bit(mcam, REG_CTRL1, 0x10000000);
	gpio_set_value(pdata->sensor_reset_gpio, 0); /* reset is active low */
	mdelay(5);
	gpio_set_value(pdata->sensor_reset_gpio, 1); /* reset is active low */
	mdelay(5);

	mcam_clk_enable(mcam);

	return 0;
}