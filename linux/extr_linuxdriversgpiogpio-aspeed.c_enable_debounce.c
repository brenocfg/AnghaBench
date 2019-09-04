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
typedef  scalar_t__ u32 ;
struct gpio_chip {int /*<<< orphan*/  parent; } ;
struct aspeed_gpio {scalar_t__ base; scalar_t__* timer_users; int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ WARN (int,char*) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configure_timer (struct aspeed_gpio*,unsigned int,int) ; 
 scalar_t__* debounce_timers ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned long,...) ; 
 struct aspeed_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 scalar_t__ ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  register_allocated_timer (struct aspeed_gpio*,unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ timer_allocation_registered (struct aspeed_gpio*,unsigned int) ; 
 int unregister_allocated_timer (struct aspeed_gpio*,unsigned int) ; 
 int usecs_to_cycles (struct aspeed_gpio*,unsigned long,scalar_t__*) ; 

__attribute__((used)) static int enable_debounce(struct gpio_chip *chip, unsigned int offset,
				    unsigned long usecs)
{
	struct aspeed_gpio *gpio = gpiochip_get_data(chip);
	u32 requested_cycles;
	unsigned long flags;
	int rc;
	int i;

	if (!gpio->clk)
		return -EINVAL;

	rc = usecs_to_cycles(gpio, usecs, &requested_cycles);
	if (rc < 0) {
		dev_warn(chip->parent, "Failed to convert %luus to cycles at %luHz: %d\n",
				usecs, clk_get_rate(gpio->clk), rc);
		return rc;
	}

	spin_lock_irqsave(&gpio->lock, flags);

	if (timer_allocation_registered(gpio, offset)) {
		rc = unregister_allocated_timer(gpio, offset);
		if (rc < 0)
			goto out;
	}

	/* Try to find a timer already configured for the debounce period */
	for (i = 1; i < ARRAY_SIZE(debounce_timers); i++) {
		u32 cycles;

		cycles = ioread32(gpio->base + debounce_timers[i]);
		if (requested_cycles == cycles)
			break;
	}

	if (i == ARRAY_SIZE(debounce_timers)) {
		int j;

		/*
		 * As there are no timers configured for the requested debounce
		 * period, find an unused timer instead
		 */
		for (j = 1; j < ARRAY_SIZE(gpio->timer_users); j++) {
			if (gpio->timer_users[j] == 0)
				break;
		}

		if (j == ARRAY_SIZE(gpio->timer_users)) {
			dev_warn(chip->parent,
					"Debounce timers exhausted, cannot debounce for period %luus\n",
					usecs);

			rc = -EPERM;

			/*
			 * We already adjusted the accounting to remove @offset
			 * as a user of its previous timer, so also configure
			 * the hardware so @offset has timers disabled for
			 * consistency.
			 */
			configure_timer(gpio, offset, 0);
			goto out;
		}

		i = j;

		iowrite32(requested_cycles, gpio->base + debounce_timers[i]);
	}

	if (WARN(i == 0, "Cannot register index of disabled timer\n")) {
		rc = -EINVAL;
		goto out;
	}

	register_allocated_timer(gpio, offset, i);
	configure_timer(gpio, offset, i);

out:
	spin_unlock_irqrestore(&gpio->lock, flags);

	return rc;
}