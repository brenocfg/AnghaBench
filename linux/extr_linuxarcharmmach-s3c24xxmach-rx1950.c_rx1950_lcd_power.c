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

/* Variables and functions */
 int /*<<< orphan*/  LCD_PWM_DUTY ; 
 int /*<<< orphan*/  LCD_PWM_PERIOD ; 
 int /*<<< orphan*/  S3C2410_GPB (int) ; 
 int /*<<< orphan*/  S3C2410_GPB1_TOUT1 ; 
 int /*<<< orphan*/  S3C2410_GPC (int) ; 
 int /*<<< orphan*/  S3C2410_GPD (int) ; 
 int /*<<< orphan*/  S3C_GPIO_SFN (int) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lcd_pwm ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pwm_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_gpio_cfgpin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx1950_lcd_power(int enable)
{
	int i;
	static int enabled;
	if (enabled == enable)
		return;
	if (!enable) {

		/* GPC11-GPC15->OUTPUT */
		for (i = 11; i < 16; i++)
			gpio_direction_output(S3C2410_GPC(i), 1);

		/* Wait a bit here... */
		mdelay(100);

		/* GPD2-GPD7->OUTPUT */
		/* GPD11-GPD15->OUTPUT */
		/* GPD2-GPD7->1, GPD11-GPD15->1 */
		for (i = 2; i < 8; i++)
			gpio_direction_output(S3C2410_GPD(i), 1);
		for (i = 11; i < 16; i++)
			gpio_direction_output(S3C2410_GPD(i), 1);

		/* Wait a bit here...*/
		mdelay(100);

		/* GPB0->OUTPUT, GPB0->0 */
		gpio_direction_output(S3C2410_GPB(0), 0);

		/* GPC1-GPC4->OUTPUT, GPC1-4->0 */
		for (i = 1; i < 5; i++)
			gpio_direction_output(S3C2410_GPC(i), 0);

		/* GPC15-GPC11->0 */
		for (i = 11; i < 16; i++)
			gpio_direction_output(S3C2410_GPC(i), 0);

		/* GPD15-GPD11->0, GPD2->GPD7->0 */
		for (i = 11; i < 16; i++)
			gpio_direction_output(S3C2410_GPD(i), 0);

		for (i = 2; i < 8; i++)
			gpio_direction_output(S3C2410_GPD(i), 0);

		/* GPC6->0, GPC7->0, GPC5->0 */
		gpio_direction_output(S3C2410_GPC(6), 0);
		gpio_direction_output(S3C2410_GPC(7), 0);
		gpio_direction_output(S3C2410_GPC(5), 0);

		/* GPB1->OUTPUT, GPB1->0 */
		gpio_direction_output(S3C2410_GPB(1), 0);
		pwm_config(lcd_pwm, 0, LCD_PWM_PERIOD);
		pwm_disable(lcd_pwm);

		/* GPC0->0, GPC10->0 */
		gpio_direction_output(S3C2410_GPC(0), 0);
		gpio_direction_output(S3C2410_GPC(10), 0);
	} else {
		pwm_config(lcd_pwm, LCD_PWM_DUTY, LCD_PWM_PERIOD);
		pwm_enable(lcd_pwm);

		gpio_direction_output(S3C2410_GPC(0), 1);
		gpio_direction_output(S3C2410_GPC(5), 1);

		s3c_gpio_cfgpin(S3C2410_GPB(1), S3C2410_GPB1_TOUT1);
		gpio_direction_output(S3C2410_GPC(7), 1);

		for (i = 1; i < 5; i++)
			s3c_gpio_cfgpin(S3C2410_GPC(i), S3C_GPIO_SFN(2));

		for (i = 11; i < 16; i++)
			s3c_gpio_cfgpin(S3C2410_GPC(i), S3C_GPIO_SFN(2));

		for (i = 2; i < 8; i++)
			s3c_gpio_cfgpin(S3C2410_GPD(i), S3C_GPIO_SFN(2));

		for (i = 11; i < 16; i++)
			s3c_gpio_cfgpin(S3C2410_GPD(i), S3C_GPIO_SFN(2));

		gpio_direction_output(S3C2410_GPC(10), 1);
		gpio_direction_output(S3C2410_GPC(6), 1);
	}
	enabled = enable;
}