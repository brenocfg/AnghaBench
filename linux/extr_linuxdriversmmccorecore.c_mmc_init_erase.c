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
struct TYPE_4__ {int capacity; int read_blkbits; } ;
struct TYPE_3__ {int au; } ;
struct mmc_card {int erase_size; int pref_erase; TYPE_2__ csd; TYPE_1__ ssr; void* erase_shift; } ;

/* Variables and functions */
 void* ffs (int) ; 
 scalar_t__ is_power_of_2 (int) ; 
 scalar_t__ mmc_card_sd (struct mmc_card*) ; 

void mmc_init_erase(struct mmc_card *card)
{
	unsigned int sz;

	if (is_power_of_2(card->erase_size))
		card->erase_shift = ffs(card->erase_size) - 1;
	else
		card->erase_shift = 0;

	/*
	 * It is possible to erase an arbitrarily large area of an SD or MMC
	 * card.  That is not desirable because it can take a long time
	 * (minutes) potentially delaying more important I/O, and also the
	 * timeout calculations become increasingly hugely over-estimated.
	 * Consequently, 'pref_erase' is defined as a guide to limit erases
	 * to that size and alignment.
	 *
	 * For SD cards that define Allocation Unit size, limit erases to one
	 * Allocation Unit at a time.
	 * For MMC, have a stab at ai good value and for modern cards it will
	 * end up being 4MiB. Note that if the value is too small, it can end
	 * up taking longer to erase. Also note, erase_size is already set to
	 * High Capacity Erase Size if available when this function is called.
	 */
	if (mmc_card_sd(card) && card->ssr.au) {
		card->pref_erase = card->ssr.au;
		card->erase_shift = ffs(card->ssr.au) - 1;
	} else if (card->erase_size) {
		sz = (card->csd.capacity << (card->csd.read_blkbits - 9)) >> 11;
		if (sz < 128)
			card->pref_erase = 512 * 1024 / 512;
		else if (sz < 512)
			card->pref_erase = 1024 * 1024 / 512;
		else if (sz < 1024)
			card->pref_erase = 2 * 1024 * 1024 / 512;
		else
			card->pref_erase = 4 * 1024 * 1024 / 512;
		if (card->pref_erase < card->erase_size)
			card->pref_erase = card->erase_size;
		else {
			sz = card->pref_erase % card->erase_size;
			if (sz)
				card->pref_erase += card->erase_size - sz;
		}
	} else
		card->pref_erase = 0;
}