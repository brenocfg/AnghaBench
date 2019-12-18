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
struct gpiomm_gpio {scalar_t__ base; } ;
struct gpio_chip {int /*<<< orphan*/  ngpio; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (size_t const*) ; 
 unsigned int BITS_PER_LONG ; 
 size_t BIT_WORD (unsigned int) ; 
 unsigned long GENMASK (unsigned int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_zero (unsigned long*,int /*<<< orphan*/ ) ; 
 struct gpiomm_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned long inb (scalar_t__) ; 

__attribute__((used)) static int gpiomm_gpio_get_multiple(struct gpio_chip *chip, unsigned long *mask,
	unsigned long *bits)
{
	struct gpiomm_gpio *const gpiommgpio = gpiochip_get_data(chip);
	size_t i;
	static const size_t ports[] = { 0, 1, 2, 4, 5, 6 };
	const unsigned int gpio_reg_size = 8;
	unsigned int bits_offset;
	size_t word_index;
	unsigned int word_offset;
	unsigned long word_mask;
	const unsigned long port_mask = GENMASK(gpio_reg_size - 1, 0);
	unsigned long port_state;

	/* clear bits array to a clean slate */
	bitmap_zero(bits, chip->ngpio);

	/* get bits are evaluated a gpio port register at a time */
	for (i = 0; i < ARRAY_SIZE(ports); i++) {
		/* gpio offset in bits array */
		bits_offset = i * gpio_reg_size;

		/* word index for bits array */
		word_index = BIT_WORD(bits_offset);

		/* gpio offset within current word of bits array */
		word_offset = bits_offset % BITS_PER_LONG;

		/* mask of get bits for current gpio within current word */
		word_mask = mask[word_index] & (port_mask << word_offset);
		if (!word_mask) {
			/* no get bits in this port so skip to next one */
			continue;
		}

		/* read bits from current gpio port */
		port_state = inb(gpiommgpio->base + ports[i]);

		/* store acquired bits at respective bits array offset */
		bits[word_index] |= (port_state << word_offset) & word_mask;
	}

	return 0;
}