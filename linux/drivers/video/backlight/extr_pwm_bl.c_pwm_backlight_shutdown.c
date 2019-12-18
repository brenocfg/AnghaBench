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
struct pwm_bl_data {int dummy; } ;
struct platform_device {int dummy; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 struct pwm_bl_data* bl_get_data (struct backlight_device*) ; 
 struct backlight_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pwm_backlight_power_off (struct pwm_bl_data*) ; 

__attribute__((used)) static void pwm_backlight_shutdown(struct platform_device *pdev)
{
	struct backlight_device *bl = platform_get_drvdata(pdev);
	struct pwm_bl_data *pb = bl_get_data(bl);

	pwm_backlight_power_off(pb);
}