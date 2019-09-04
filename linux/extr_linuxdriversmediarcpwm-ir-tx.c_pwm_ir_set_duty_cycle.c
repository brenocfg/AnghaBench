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
struct rc_dev {struct pwm_ir* priv; } ;
struct pwm_ir {int /*<<< orphan*/  duty_cycle; } ;

/* Variables and functions */

__attribute__((used)) static int pwm_ir_set_duty_cycle(struct rc_dev *dev, u32 duty_cycle)
{
	struct pwm_ir *pwm_ir = dev->priv;

	pwm_ir->duty_cycle = duty_cycle;

	return 0;
}