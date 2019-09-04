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
struct mmp_camera {TYPE_2__* pdev; scalar_t__ power_regs; } ;
struct mcam_camera {int dummy; } ;
struct TYPE_3__ {struct mmp_camera_platform_data* platform_data; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ REG_CCIC_CRCR ; 
 scalar_t__ REG_CCIC_DCGCR ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mcam_clk_disable (struct mcam_camera*) ; 
 struct mmp_camera* mcam_to_cam (struct mcam_camera*) ; 

__attribute__((used)) static void mmpcam_power_down(struct mcam_camera *mcam)
{
	struct mmp_camera *cam = mcam_to_cam(mcam);
	struct mmp_camera_platform_data *pdata;
/*
 * Turn off clocks and set reset lines
 */
	iowrite32(0, cam->power_regs + REG_CCIC_DCGCR);
	iowrite32(0, cam->power_regs + REG_CCIC_CRCR);
/*
 * Shut down the sensor.
 */
	pdata = cam->pdev->dev.platform_data;
	gpio_set_value(pdata->sensor_power_gpio, 0);
	gpio_set_value(pdata->sensor_reset_gpio, 0);

	mcam_clk_disable(mcam);
}