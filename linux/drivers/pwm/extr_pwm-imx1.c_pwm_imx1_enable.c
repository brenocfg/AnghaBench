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
typedef  int /*<<< orphan*/  u32 ;
struct pwm_imx1_chip {scalar_t__ mmio_base; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ MX1_PWMC ; 
 int /*<<< orphan*/  MX1_PWMC_EN ; 
 int pwm_imx1_clk_prepare_enable (struct pwm_chip*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct pwm_imx1_chip* to_pwm_imx1_chip (struct pwm_chip*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pwm_imx1_enable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct pwm_imx1_chip *imx = to_pwm_imx1_chip(chip);
	u32 value;
	int ret;

	ret = pwm_imx1_clk_prepare_enable(chip);
	if (ret < 0)
		return ret;

	value = readl(imx->mmio_base + MX1_PWMC);
	value |= MX1_PWMC_EN;
	writel(value, imx->mmio_base + MX1_PWMC);

	return 0;
}