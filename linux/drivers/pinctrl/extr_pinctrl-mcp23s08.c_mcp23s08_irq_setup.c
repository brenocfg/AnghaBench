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
struct gpio_chip {int /*<<< orphan*/  parent; } ;
struct mcp23s08 {int /*<<< orphan*/  irq; scalar_t__ irq_active_high; struct gpio_chip chip; } ;

/* Variables and functions */
 unsigned long IRQF_ONESHOT ; 
 unsigned long IRQF_SHARED ; 
 unsigned long IRQF_TRIGGER_HIGH ; 
 unsigned long IRQF_TRIGGER_LOW ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct mcp23s08*) ; 
 int /*<<< orphan*/  mcp23s08_irq ; 

__attribute__((used)) static int mcp23s08_irq_setup(struct mcp23s08 *mcp)
{
	struct gpio_chip *chip = &mcp->chip;
	int err;
	unsigned long irqflags = IRQF_ONESHOT | IRQF_SHARED;

	if (mcp->irq_active_high)
		irqflags |= IRQF_TRIGGER_HIGH;
	else
		irqflags |= IRQF_TRIGGER_LOW;

	err = devm_request_threaded_irq(chip->parent, mcp->irq, NULL,
					mcp23s08_irq,
					irqflags, dev_name(chip->parent), mcp);
	if (err != 0) {
		dev_err(chip->parent, "unable to request IRQ#%d: %d\n",
			mcp->irq, err);
		return err;
	}

	return 0;
}