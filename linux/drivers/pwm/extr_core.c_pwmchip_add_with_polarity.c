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
struct TYPE_3__ {int polarity; } ;
struct pwm_device {unsigned int pwm; unsigned int hwpwm; TYPE_1__ state; struct pwm_chip* chip; } ;
struct pwm_chip {unsigned int npwm; int base; int /*<<< orphan*/  list; TYPE_2__* ops; struct pwm_device* pwms; int /*<<< orphan*/  dev; } ;
typedef  enum pwm_polarity { ____Placeholder_pwm_polarity } pwm_polarity ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_state ) (struct pwm_chip*,struct pwm_device*,TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int alloc_pwms (int,unsigned int) ; 
 int /*<<< orphan*/  allocated_pwms ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct pwm_device* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_pwmchip_add (struct pwm_chip*) ; 
 int /*<<< orphan*/  pwm_chips ; 
 int /*<<< orphan*/  pwm_lock ; 
 int /*<<< orphan*/  pwm_ops_check (TYPE_2__*) ; 
 int /*<<< orphan*/  pwm_tree ; 
 int /*<<< orphan*/  pwmchip_sysfs_export (struct pwm_chip*) ; 
 int /*<<< orphan*/  radix_tree_insert (int /*<<< orphan*/ *,unsigned int,struct pwm_device*) ; 
 int /*<<< orphan*/  stub1 (struct pwm_chip*,struct pwm_device*,TYPE_1__*) ; 

int pwmchip_add_with_polarity(struct pwm_chip *chip,
			      enum pwm_polarity polarity)
{
	struct pwm_device *pwm;
	unsigned int i;
	int ret;

	if (!chip || !chip->dev || !chip->ops || !chip->npwm)
		return -EINVAL;

	if (!pwm_ops_check(chip->ops))
		return -EINVAL;

	mutex_lock(&pwm_lock);

	ret = alloc_pwms(chip->base, chip->npwm);
	if (ret < 0)
		goto out;

	chip->pwms = kcalloc(chip->npwm, sizeof(*pwm), GFP_KERNEL);
	if (!chip->pwms) {
		ret = -ENOMEM;
		goto out;
	}

	chip->base = ret;

	for (i = 0; i < chip->npwm; i++) {
		pwm = &chip->pwms[i];

		pwm->chip = chip;
		pwm->pwm = chip->base + i;
		pwm->hwpwm = i;
		pwm->state.polarity = polarity;

		if (chip->ops->get_state)
			chip->ops->get_state(chip, pwm, &pwm->state);

		radix_tree_insert(&pwm_tree, pwm->pwm, pwm);
	}

	bitmap_set(allocated_pwms, chip->base, chip->npwm);

	INIT_LIST_HEAD(&chip->list);
	list_add(&chip->list, &pwm_chips);

	ret = 0;

	if (IS_ENABLED(CONFIG_OF))
		of_pwmchip_add(chip);

out:
	mutex_unlock(&pwm_lock);

	if (!ret)
		pwmchip_sysfs_export(chip);

	return ret;
}