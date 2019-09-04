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
struct gpio_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  label; TYPE_1__* gdev; } ;
struct gpio_chip {int /*<<< orphan*/  (* free ) (struct gpio_chip*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  can_sleep; } ;
struct TYPE_2__ {struct gpio_chip* chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_ACTIVE_LOW ; 
 int /*<<< orphan*/  FLAG_IS_HOGGED ; 
 int /*<<< orphan*/  FLAG_OPEN_DRAIN ; 
 int /*<<< orphan*/  FLAG_OPEN_SOURCE ; 
 int /*<<< orphan*/  FLAG_REQUESTED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  desc_set_label (struct gpio_desc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_chip_hwgpio (struct gpio_desc*) ; 
 int /*<<< orphan*/  gpio_lock ; 
 int /*<<< orphan*/  gpiod_unexport (struct gpio_desc*) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  might_sleep_if (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct gpio_chip*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool gpiod_free_commit(struct gpio_desc *desc)
{
	bool			ret = false;
	unsigned long		flags;
	struct gpio_chip	*chip;

	might_sleep();

	gpiod_unexport(desc);

	spin_lock_irqsave(&gpio_lock, flags);

	chip = desc->gdev->chip;
	if (chip && test_bit(FLAG_REQUESTED, &desc->flags)) {
		if (chip->free) {
			spin_unlock_irqrestore(&gpio_lock, flags);
			might_sleep_if(chip->can_sleep);
			chip->free(chip, gpio_chip_hwgpio(desc));
			spin_lock_irqsave(&gpio_lock, flags);
		}
		kfree_const(desc->label);
		desc_set_label(desc, NULL);
		clear_bit(FLAG_ACTIVE_LOW, &desc->flags);
		clear_bit(FLAG_REQUESTED, &desc->flags);
		clear_bit(FLAG_OPEN_DRAIN, &desc->flags);
		clear_bit(FLAG_OPEN_SOURCE, &desc->flags);
		clear_bit(FLAG_IS_HOGGED, &desc->flags);
		ret = true;
	}

	spin_unlock_irqrestore(&gpio_lock, flags);
	return ret;
}