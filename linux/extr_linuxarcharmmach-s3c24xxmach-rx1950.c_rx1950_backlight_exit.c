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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_GPB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_pwm ; 
 int /*<<< orphan*/  pwm_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx1950_bl_power (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx1950_lcd_power (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx1950_backlight_exit(struct device *dev)
{
	rx1950_bl_power(0);
	rx1950_lcd_power(0);

	pwm_free(lcd_pwm);
	gpio_free(S3C2410_GPB(0));
}