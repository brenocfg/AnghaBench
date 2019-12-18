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
struct pwm_device {int /*<<< orphan*/  pwm; } ;
struct pwm_chip {unsigned int npwm; struct pwm_device* pwms; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  allocated_pwms ; 
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct pwm_device*) ; 
 int /*<<< orphan*/  pwm_tree ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_pwms(struct pwm_chip *chip)
{
	unsigned int i;

	for (i = 0; i < chip->npwm; i++) {
		struct pwm_device *pwm = &chip->pwms[i];

		radix_tree_delete(&pwm_tree, pwm->pwm);
	}

	bitmap_clear(allocated_pwms, chip->base, chip->npwm);

	kfree(chip->pwms);
	chip->pwms = NULL;
}