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
struct mmc_card {unsigned int erase_size; } ;

/* Variables and functions */
 scalar_t__ is_power_of_2 (unsigned int) ; 
 unsigned int round_down (unsigned int,unsigned int) ; 
 unsigned int round_up (unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned int mmc_align_erase_size(struct mmc_card *card,
					 unsigned int *from,
					 unsigned int *to,
					 unsigned int nr)
{
	unsigned int from_new = *from, nr_new = nr, rem;

	/*
	 * When the 'card->erase_size' is power of 2, we can use round_up/down()
	 * to align the erase size efficiently.
	 */
	if (is_power_of_2(card->erase_size)) {
		unsigned int temp = from_new;

		from_new = round_up(temp, card->erase_size);
		rem = from_new - temp;

		if (nr_new > rem)
			nr_new -= rem;
		else
			return 0;

		nr_new = round_down(nr_new, card->erase_size);
	} else {
		rem = from_new % card->erase_size;
		if (rem) {
			rem = card->erase_size - rem;
			from_new += rem;
			if (nr_new > rem)
				nr_new -= rem;
			else
				return 0;
		}

		rem = nr_new % card->erase_size;
		if (rem)
			nr_new -= rem;
	}

	if (nr_new == 0)
		return 0;

	*to = from_new + nr_new;
	*from = from_new;

	return nr_new;
}