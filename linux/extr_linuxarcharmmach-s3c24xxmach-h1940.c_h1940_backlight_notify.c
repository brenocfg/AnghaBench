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
 int /*<<< orphan*/  H1940_LATCH_MAX1698_nSHUTDOWN ; 
 int /*<<< orphan*/  S3C2410_GPB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C2410_GPB0_TOUT0 ; 
 int /*<<< orphan*/  S3C_GPIO_PULL_NONE ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s3c_gpio_cfgpin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_gpio_setpull (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int h1940_backlight_notify(struct device *dev, int brightness)
{
	if (!brightness) {
		gpio_direction_output(S3C2410_GPB(0), 1);
		gpio_set_value(H1940_LATCH_MAX1698_nSHUTDOWN, 0);
	} else {
		gpio_direction_output(S3C2410_GPB(0), 0);
		s3c_gpio_setpull(S3C2410_GPB(0), S3C_GPIO_PULL_NONE);
		s3c_gpio_cfgpin(S3C2410_GPB(0), S3C2410_GPB0_TOUT0);
		gpio_set_value(H1940_LATCH_MAX1698_nSHUTDOWN, 1);
	}
	return brightness;
}