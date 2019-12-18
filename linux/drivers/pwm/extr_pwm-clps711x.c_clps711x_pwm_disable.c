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
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct clps711x_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clps711x_pwm_update_val (struct clps711x_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clps711x_chip* to_clps711x_chip (struct pwm_chip*) ; 

__attribute__((used)) static void clps711x_pwm_disable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct clps711x_chip *priv = to_clps711x_chip(chip);

	clps711x_pwm_update_val(priv, pwm->hwpwm, 0);
}