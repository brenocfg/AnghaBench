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
struct TYPE_2__ {scalar_t__ period; } ;
struct pwm_device {TYPE_1__ args; } ;
struct pwm_chip {int of_pwm_n_cells; scalar_t__ npwm; } ;
struct of_phandle_args {int args_count; scalar_t__* args; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct pwm_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct pwm_device*) ; 
 struct pwm_device* pwm_request_from_chip (struct pwm_chip*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pwm_device *
of_pwm_simple_xlate(struct pwm_chip *pc, const struct of_phandle_args *args)
{
	struct pwm_device *pwm;

	/* sanity check driver support */
	if (pc->of_pwm_n_cells < 2)
		return ERR_PTR(-EINVAL);

	/* all cells are required */
	if (args->args_count != pc->of_pwm_n_cells)
		return ERR_PTR(-EINVAL);

	if (args->args[0] >= pc->npwm)
		return ERR_PTR(-EINVAL);

	pwm = pwm_request_from_chip(pc, args->args[0], NULL);
	if (IS_ERR(pwm))
		return pwm;

	pwm->args.period = args->args[1];

	return pwm;
}