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
struct lm3630a_chip {int /*<<< orphan*/  pwmd; TYPE_1__* pdata; } ;
struct TYPE_2__ {unsigned int pwm_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  pwm_config (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pwm_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lm3630a_pwm_ctrl(struct lm3630a_chip *pchip, int br, int br_max)
{
	unsigned int period = pchip->pdata->pwm_period;
	unsigned int duty = br * period / br_max;

	pwm_config(pchip->pwmd, duty, period);
	if (duty)
		pwm_enable(pchip->pwmd);
	else
		pwm_disable(pchip->pwmd);
}