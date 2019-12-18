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
struct TYPE_2__ {int mod_period; } ;
struct fsl_pwm_chip {TYPE_1__ period; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (unsigned long long,unsigned int) ; 
 unsigned int fsl_pwm_ticks_to_ns (struct fsl_pwm_chip*,unsigned int) ; 

__attribute__((used)) static unsigned int fsl_pwm_calculate_duty(struct fsl_pwm_chip *fpc,
					   unsigned int duty_ns)
{
	unsigned long long duty;

	unsigned int period = fpc->period.mod_period + 1;
	unsigned int period_ns = fsl_pwm_ticks_to_ns(fpc, period);

	duty = (unsigned long long)duty_ns * period;
	do_div(duty, period_ns);

	return (unsigned int)duty;
}