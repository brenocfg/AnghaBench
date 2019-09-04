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
struct pwm_device {int dummy; } ;
struct ir_rx51 {int freq; int duty_cycle; struct pwm_device* pwm; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  pwm_config (struct pwm_device*,int,int) ; 

__attribute__((used)) static int init_timing_params(struct ir_rx51 *ir_rx51)
{
	struct pwm_device *pwm = ir_rx51->pwm;
	int duty, period = DIV_ROUND_CLOSEST(NSEC_PER_SEC, ir_rx51->freq);

	duty = DIV_ROUND_CLOSEST(ir_rx51->duty_cycle * period, 100);

	pwm_config(pwm, duty, period);

	return 0;
}