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
struct pwm_sifive_ddata {int /*<<< orphan*/  lock; int /*<<< orphan*/  user_count; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct pwm_sifive_ddata* pwm_sifive_chip_to_ddata (struct pwm_chip*) ; 

__attribute__((used)) static void pwm_sifive_free(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct pwm_sifive_ddata *ddata = pwm_sifive_chip_to_ddata(chip);

	mutex_lock(&ddata->lock);
	ddata->user_count--;
	mutex_unlock(&ddata->lock);
}