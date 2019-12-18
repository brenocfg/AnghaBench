#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct pwm_lpss_chip {TYPE_1__* info; } ;
struct pwm_device {int dummy; } ;
struct TYPE_2__ {unsigned long clk_rate; int /*<<< orphan*/  base_unit_bits; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 unsigned long long DIV_ROUND_CLOSEST_ULL (unsigned long long,unsigned long) ; 
 unsigned long long NSEC_PER_SEC ; 
 unsigned long PWM_BASE_UNIT_SHIFT ; 
 unsigned long PWM_ON_TIME_DIV_MASK ; 
 unsigned long PWM_SW_UPDATE ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 unsigned long pwm_lpss_read (struct pwm_device*) ; 
 int /*<<< orphan*/  pwm_lpss_write (struct pwm_device*,unsigned long) ; 

__attribute__((used)) static void pwm_lpss_prepare(struct pwm_lpss_chip *lpwm, struct pwm_device *pwm,
			     int duty_ns, int period_ns)
{
	unsigned long long on_time_div;
	unsigned long c = lpwm->info->clk_rate, base_unit_range;
	unsigned long long base_unit, freq = NSEC_PER_SEC;
	u32 orig_ctrl, ctrl;

	do_div(freq, period_ns);

	/*
	 * The equation is:
	 * base_unit = round(base_unit_range * freq / c)
	 */
	base_unit_range = BIT(lpwm->info->base_unit_bits) - 1;
	freq *= base_unit_range;

	base_unit = DIV_ROUND_CLOSEST_ULL(freq, c);

	on_time_div = 255ULL * duty_ns;
	do_div(on_time_div, period_ns);
	on_time_div = 255ULL - on_time_div;

	orig_ctrl = ctrl = pwm_lpss_read(pwm);
	ctrl &= ~PWM_ON_TIME_DIV_MASK;
	ctrl &= ~(base_unit_range << PWM_BASE_UNIT_SHIFT);
	base_unit &= base_unit_range;
	ctrl |= (u32) base_unit << PWM_BASE_UNIT_SHIFT;
	ctrl |= on_time_div;

	if (orig_ctrl != ctrl) {
		pwm_lpss_write(pwm, ctrl);
		pwm_lpss_write(pwm, ctrl | PWM_SW_UPDATE);
	}
}