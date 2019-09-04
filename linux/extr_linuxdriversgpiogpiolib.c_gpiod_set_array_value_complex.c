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
struct gpio_desc {int /*<<< orphan*/  flags; TYPE_1__* gdev; } ;
struct gpio_chip {scalar_t__ ngpio; int /*<<< orphan*/  can_sleep; } ;
struct TYPE_2__ {struct gpio_chip* chip; } ;

/* Variables and functions */
 int BITS_TO_LONGS (scalar_t__) ; 
 int ENOMEM ; 
 scalar_t__ FASTPATH_NGPIO ; 
 int /*<<< orphan*/  FLAG_ACTIVE_LOW ; 
 int /*<<< orphan*/  FLAG_OPEN_DRAIN ; 
 int /*<<< orphan*/  FLAG_OPEN_SOURCE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  __set_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  bitmap_zero (unsigned long*,scalar_t__) ; 
 int /*<<< orphan*/  desc_to_gpio (struct gpio_desc*) ; 
 int gpio_chip_hwgpio (struct gpio_desc*) ; 
 int /*<<< orphan*/  gpio_chip_set_multiple (struct gpio_chip*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  gpio_set_open_drain_value_commit (struct gpio_desc*,int) ; 
 int /*<<< orphan*/  gpio_set_open_source_value_commit (struct gpio_desc*,int) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 unsigned long* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_gpio_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int gpiod_set_array_value_complex(bool raw, bool can_sleep,
				   unsigned int array_size,
				   struct gpio_desc **desc_array,
				   int *value_array)
{
	int i = 0;

	while (i < array_size) {
		struct gpio_chip *chip = desc_array[i]->gdev->chip;
		unsigned long fastpath[2 * BITS_TO_LONGS(FASTPATH_NGPIO)];
		unsigned long *mask, *bits;
		int count = 0;

		if (likely(chip->ngpio <= FASTPATH_NGPIO)) {
			mask = fastpath;
		} else {
			mask = kmalloc_array(2 * BITS_TO_LONGS(chip->ngpio),
					   sizeof(*mask),
					   can_sleep ? GFP_KERNEL : GFP_ATOMIC);
			if (!mask)
				return -ENOMEM;
		}

		bits = mask + BITS_TO_LONGS(chip->ngpio);
		bitmap_zero(mask, chip->ngpio);

		if (!can_sleep)
			WARN_ON(chip->can_sleep);

		do {
			struct gpio_desc *desc = desc_array[i];
			int hwgpio = gpio_chip_hwgpio(desc);
			int value = value_array[i];

			if (!raw && test_bit(FLAG_ACTIVE_LOW, &desc->flags))
				value = !value;
			trace_gpio_value(desc_to_gpio(desc), 0, value);
			/*
			 * collect all normal outputs belonging to the same chip
			 * open drain and open source outputs are set individually
			 */
			if (test_bit(FLAG_OPEN_DRAIN, &desc->flags) && !raw) {
				gpio_set_open_drain_value_commit(desc, value);
			} else if (test_bit(FLAG_OPEN_SOURCE, &desc->flags) && !raw) {
				gpio_set_open_source_value_commit(desc, value);
			} else {
				__set_bit(hwgpio, mask);
				if (value)
					__set_bit(hwgpio, bits);
				else
					__clear_bit(hwgpio, bits);
				count++;
			}
			i++;
		} while ((i < array_size) &&
			 (desc_array[i]->gdev->chip == chip));
		/* push collected bits to outputs */
		if (count != 0)
			gpio_chip_set_multiple(chip, mask, bits);

		if (mask != fastpath)
			kfree(mask);
	}
	return 0;
}