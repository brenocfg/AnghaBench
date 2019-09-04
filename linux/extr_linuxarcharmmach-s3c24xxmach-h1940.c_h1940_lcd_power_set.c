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
struct plat_lcd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H1940_LATCH_LCD_P0 ; 
 int /*<<< orphan*/  H1940_LATCH_LCD_P1 ; 
 int /*<<< orphan*/  H1940_LATCH_LCD_P2 ; 
 int /*<<< orphan*/  H1940_LATCH_LCD_P3 ; 
 int /*<<< orphan*/  H1940_LATCH_LCD_P4 ; 
 int /*<<< orphan*/  S3C2410_GPC (int) ; 
 int /*<<< orphan*/  S3C_GPIO_SFN (int) ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  s3c_gpio_cfgpin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void h1940_lcd_power_set(struct plat_lcd_data *pd,
					unsigned int power)
{
	int value, retries = 100;

	if (!power) {
		gpio_set_value(S3C2410_GPC(0), 0);
		/* wait for 3ac */
		do {
			value = gpio_get_value(S3C2410_GPC(6));
		} while (value && retries--);

		gpio_set_value(H1940_LATCH_LCD_P2, 0);
		gpio_set_value(H1940_LATCH_LCD_P3, 0);
		gpio_set_value(H1940_LATCH_LCD_P4, 0);

		gpio_direction_output(S3C2410_GPC(1), 0);
		gpio_direction_output(S3C2410_GPC(4), 0);

		gpio_set_value(H1940_LATCH_LCD_P1, 0);
		gpio_set_value(H1940_LATCH_LCD_P0, 0);

		gpio_set_value(S3C2410_GPC(5), 0);

	} else {
		gpio_set_value(H1940_LATCH_LCD_P0, 1);
		gpio_set_value(H1940_LATCH_LCD_P1, 1);

		gpio_direction_input(S3C2410_GPC(1));
		gpio_direction_input(S3C2410_GPC(4));
		mdelay(10);
		s3c_gpio_cfgpin(S3C2410_GPC(1), S3C_GPIO_SFN(2));
		s3c_gpio_cfgpin(S3C2410_GPC(4), S3C_GPIO_SFN(2));

		gpio_set_value(S3C2410_GPC(5), 1);
		gpio_set_value(S3C2410_GPC(0), 1);

		gpio_set_value(H1940_LATCH_LCD_P3, 1);
		gpio_set_value(H1940_LATCH_LCD_P2, 1);
		gpio_set_value(H1940_LATCH_LCD_P4, 1);
	}
}