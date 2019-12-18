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
struct adv7180_state {scalar_t__ irq; int /*<<< orphan*/  mutex; TYPE_1__* chip_info; } ;
struct TYPE_2__ {int (* init ) (struct adv7180_state*) ;} ;

/* Variables and functions */
 int ADV7180_ICONF1_ACTIVE_LOW ; 
 int ADV7180_ICONF1_PSYNC_ONLY ; 
 int ADV7180_IRQ3_AD_CHANGE ; 
 int ADV7180_PWR_MAN_RES ; 
 int /*<<< orphan*/  ADV7180_REG_ICONF1 ; 
 int /*<<< orphan*/  ADV7180_REG_IMR1 ; 
 int /*<<< orphan*/  ADV7180_REG_IMR2 ; 
 int /*<<< orphan*/  ADV7180_REG_IMR3 ; 
 int /*<<< orphan*/  ADV7180_REG_IMR4 ; 
 int /*<<< orphan*/  ADV7180_REG_PWR_MAN ; 
 int adv7180_program_std (struct adv7180_state*) ; 
 int /*<<< orphan*/  adv7180_set_field_mode (struct adv7180_state*) ; 
 int /*<<< orphan*/  adv7180_set_power_pin (struct adv7180_state*,int) ; 
 int adv7180_write (struct adv7180_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct adv7180_state*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int init_device(struct adv7180_state *state)
{
	int ret;

	mutex_lock(&state->mutex);

	adv7180_set_power_pin(state, true);

	adv7180_write(state, ADV7180_REG_PWR_MAN, ADV7180_PWR_MAN_RES);
	usleep_range(5000, 10000);

	ret = state->chip_info->init(state);
	if (ret)
		goto out_unlock;

	ret = adv7180_program_std(state);
	if (ret)
		goto out_unlock;

	adv7180_set_field_mode(state);

	/* register for interrupts */
	if (state->irq > 0) {
		/* config the Interrupt pin to be active low */
		ret = adv7180_write(state, ADV7180_REG_ICONF1,
						ADV7180_ICONF1_ACTIVE_LOW |
						ADV7180_ICONF1_PSYNC_ONLY);
		if (ret < 0)
			goto out_unlock;

		ret = adv7180_write(state, ADV7180_REG_IMR1, 0);
		if (ret < 0)
			goto out_unlock;

		ret = adv7180_write(state, ADV7180_REG_IMR2, 0);
		if (ret < 0)
			goto out_unlock;

		/* enable AD change interrupts interrupts */
		ret = adv7180_write(state, ADV7180_REG_IMR3,
						ADV7180_IRQ3_AD_CHANGE);
		if (ret < 0)
			goto out_unlock;

		ret = adv7180_write(state, ADV7180_REG_IMR4, 0);
		if (ret < 0)
			goto out_unlock;
	}

out_unlock:
	mutex_unlock(&state->mutex);

	return ret;
}