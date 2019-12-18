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
struct pwm_device {scalar_t__ hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct fsl_pwm_chip {int /*<<< orphan*/  ipg_clk; int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; TYPE_1__* soc; } ;
struct TYPE_2__ {scalar_t__ has_enable_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 int /*<<< orphan*/  FTM_SC ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsl_pwm_chip* to_fsl_chip (struct pwm_chip*) ; 

__attribute__((used)) static void fsl_pwm_free(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct fsl_pwm_chip *fpc = to_fsl_chip(chip);

	if (fpc->soc->has_enable_bits) {
		mutex_lock(&fpc->lock);
		regmap_update_bits(fpc->regmap, FTM_SC, BIT(pwm->hwpwm + 16),
				   0);
		mutex_unlock(&fpc->lock);
	}

	clk_disable_unprepare(fpc->ipg_clk);
}