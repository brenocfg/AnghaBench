#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct pwm_state {unsigned long long period; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;
struct atmel_pwm_chip {TYPE_2__* data; int /*<<< orphan*/  clk; } ;
struct TYPE_3__ {unsigned long long max_period; scalar_t__ max_pres; } ;
struct TYPE_4__ {TYPE_1__ cfg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 unsigned long long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int /*<<< orphan*/ ) ; 
 struct atmel_pwm_chip* to_atmel_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static int atmel_pwm_calculate_cprd_and_pres(struct pwm_chip *chip,
					     const struct pwm_state *state,
					     unsigned long *cprd, u32 *pres)
{
	struct atmel_pwm_chip *atmel_pwm = to_atmel_pwm_chip(chip);
	unsigned long long cycles = state->period;

	/* Calculate the period cycles and prescale value */
	cycles *= clk_get_rate(atmel_pwm->clk);
	do_div(cycles, NSEC_PER_SEC);

	for (*pres = 0; cycles > atmel_pwm->data->cfg.max_period; cycles >>= 1)
		(*pres)++;

	if (*pres > atmel_pwm->data->cfg.max_pres) {
		dev_err(chip->dev, "pres exceeds the maximum value\n");
		return -EINVAL;
	}

	*cprd = cycles;

	return 0;
}