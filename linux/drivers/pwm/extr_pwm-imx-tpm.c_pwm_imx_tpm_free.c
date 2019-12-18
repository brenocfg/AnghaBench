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
struct pwm_chip {int dummy; } ;
struct imx_tpm_pwm_chip {int /*<<< orphan*/  lock; int /*<<< orphan*/  user_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct imx_tpm_pwm_chip* to_imx_tpm_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static void pwm_imx_tpm_free(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct imx_tpm_pwm_chip *tpm = to_imx_tpm_pwm_chip(chip);

	mutex_lock(&tpm->lock);
	tpm->user_count--;
	mutex_unlock(&tpm->lock);
}