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
typedef  int u32 ;
struct pwm_imx1_chip {scalar_t__ mmio_base; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ MX1_PWMP ; 
 scalar_t__ MX1_PWMS ; 
 int readl (scalar_t__) ; 
 struct pwm_imx1_chip* to_pwm_imx1_chip (struct pwm_chip*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int pwm_imx1_config(struct pwm_chip *chip,
			   struct pwm_device *pwm, int duty_ns, int period_ns)
{
	struct pwm_imx1_chip *imx = to_pwm_imx1_chip(chip);
	u32 max, p;

	/*
	 * The PWM subsystem allows for exact frequencies. However,
	 * I cannot connect a scope on my device to the PWM line and
	 * thus cannot provide the program the PWM controller
	 * exactly. Instead, I'm relying on the fact that the
	 * Bootloader (u-boot or WinCE+haret) has programmed the PWM
	 * function group already. So I'll just modify the PWM sample
	 * register to follow the ratio of duty_ns vs. period_ns
	 * accordingly.
	 *
	 * This is good enough for programming the brightness of
	 * the LCD backlight.
	 *
	 * The real implementation would divide PERCLK[0] first by
	 * both the prescaler (/1 .. /128) and then by CLKSEL
	 * (/2 .. /16).
	 */
	max = readl(imx->mmio_base + MX1_PWMP);
	p = max * duty_ns / period_ns;

	writel(max - p, imx->mmio_base + MX1_PWMS);

	return 0;
}