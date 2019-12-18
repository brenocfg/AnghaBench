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
struct pwm_bl_data {int /*<<< orphan*/  pwm; scalar_t__ legacy; int /*<<< orphan*/  (* exit ) (int /*<<< orphan*/ *) ;} ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_device_unregister (struct backlight_device*) ; 
 struct pwm_bl_data* bl_get_data (struct backlight_device*) ; 
 struct backlight_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pwm_backlight_power_off (struct pwm_bl_data*) ; 
 int /*<<< orphan*/  pwm_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pwm_backlight_remove(struct platform_device *pdev)
{
	struct backlight_device *bl = platform_get_drvdata(pdev);
	struct pwm_bl_data *pb = bl_get_data(bl);

	backlight_device_unregister(bl);
	pwm_backlight_power_off(pb);

	if (pb->exit)
		pb->exit(&pdev->dev);
	if (pb->legacy)
		pwm_free(pb->pwm);

	return 0;
}