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
struct TYPE_2__ {int /*<<< orphan*/  period; } ;
struct pwm_device {TYPE_1__ args; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int clps711x_get_duty(struct pwm_device *pwm, unsigned int v)
{
	/* Duty cycle 0..15 max */
	return DIV_ROUND_CLOSEST(v * 0xf, pwm->args.period);
}