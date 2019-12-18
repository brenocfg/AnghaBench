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
typedef  unsigned long u32 ;
struct vt8500_chip {int /*<<< orphan*/  clk; scalar_t__ base; } ;
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long CTRL_AUTOLOAD ; 
 int EINVAL ; 
 scalar_t__ REG_CTRL (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_DUTY (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_PERIOD (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_SCALAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_CTRL_UPDATE ; 
 int /*<<< orphan*/  STATUS_DUTY_UPDATE ; 
 int /*<<< orphan*/  STATUS_PERIOD_UPDATE ; 
 int /*<<< orphan*/  STATUS_SCALAR_UPDATE ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 unsigned long long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 int /*<<< orphan*/  pwm_busy_wait (struct vt8500_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long readl (scalar_t__) ; 
 struct vt8500_chip* to_vt8500_chip (struct pwm_chip*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int vt8500_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
		int duty_ns, int period_ns)
{
	struct vt8500_chip *vt8500 = to_vt8500_chip(chip);
	unsigned long long c;
	unsigned long period_cycles, prescale, pv, dc;
	int err;
	u32 val;

	err = clk_enable(vt8500->clk);
	if (err < 0) {
		dev_err(chip->dev, "failed to enable clock\n");
		return err;
	}

	c = clk_get_rate(vt8500->clk);
	c = c * period_ns;
	do_div(c, 1000000000);
	period_cycles = c;

	if (period_cycles < 1)
		period_cycles = 1;
	prescale = (period_cycles - 1) / 4096;
	pv = period_cycles / (prescale + 1) - 1;
	if (pv > 4095)
		pv = 4095;

	if (prescale > 1023) {
		clk_disable(vt8500->clk);
		return -EINVAL;
	}

	c = (unsigned long long)pv * duty_ns;
	do_div(c, period_ns);
	dc = c;

	writel(prescale, vt8500->base + REG_SCALAR(pwm->hwpwm));
	pwm_busy_wait(vt8500, pwm->hwpwm, STATUS_SCALAR_UPDATE);

	writel(pv, vt8500->base + REG_PERIOD(pwm->hwpwm));
	pwm_busy_wait(vt8500, pwm->hwpwm, STATUS_PERIOD_UPDATE);

	writel(dc, vt8500->base + REG_DUTY(pwm->hwpwm));
	pwm_busy_wait(vt8500, pwm->hwpwm, STATUS_DUTY_UPDATE);

	val = readl(vt8500->base + REG_CTRL(pwm->hwpwm));
	val |= CTRL_AUTOLOAD;
	writel(val, vt8500->base + REG_CTRL(pwm->hwpwm));
	pwm_busy_wait(vt8500, pwm->hwpwm, STATUS_CTRL_UPDATE);

	clk_disable(vt8500->clk);
	return 0;
}