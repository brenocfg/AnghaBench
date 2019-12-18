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
struct mmc_host {int max_busy_timeout; } ;
struct mmc_card {int erase_shift; unsigned int pref_erase; unsigned int erase_size; int eg_boundary; struct mmc_host* host; } ;

/* Variables and functions */
 unsigned int MMC_ERASE_TIMEOUT_MS ; 
 unsigned int UINT_MAX ; 
 scalar_t__ mmc_card_sd (struct mmc_card*) ; 
 unsigned int mmc_erase_timeout (struct mmc_card*,unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned int mmc_do_calc_max_discard(struct mmc_card *card,
					    unsigned int arg)
{
	struct mmc_host *host = card->host;
	unsigned int max_discard, x, y, qty = 0, max_qty, min_qty, timeout;
	unsigned int last_timeout = 0;
	unsigned int max_busy_timeout = host->max_busy_timeout ?
			host->max_busy_timeout : MMC_ERASE_TIMEOUT_MS;

	if (card->erase_shift) {
		max_qty = UINT_MAX >> card->erase_shift;
		min_qty = card->pref_erase >> card->erase_shift;
	} else if (mmc_card_sd(card)) {
		max_qty = UINT_MAX;
		min_qty = card->pref_erase;
	} else {
		max_qty = UINT_MAX / card->erase_size;
		min_qty = card->pref_erase / card->erase_size;
	}

	/*
	 * We should not only use 'host->max_busy_timeout' as the limitation
	 * when deciding the max discard sectors. We should set a balance value
	 * to improve the erase speed, and it can not get too long timeout at
	 * the same time.
	 *
	 * Here we set 'card->pref_erase' as the minimal discard sectors no
	 * matter what size of 'host->max_busy_timeout', but if the
	 * 'host->max_busy_timeout' is large enough for more discard sectors,
	 * then we can continue to increase the max discard sectors until we
	 * get a balance value. In cases when the 'host->max_busy_timeout'
	 * isn't specified, use the default max erase timeout.
	 */
	do {
		y = 0;
		for (x = 1; x && x <= max_qty && max_qty - x >= qty; x <<= 1) {
			timeout = mmc_erase_timeout(card, arg, qty + x);

			if (qty + x > min_qty && timeout > max_busy_timeout)
				break;

			if (timeout < last_timeout)
				break;
			last_timeout = timeout;
			y = x;
		}
		qty += y;
	} while (y);

	if (!qty)
		return 0;

	/*
	 * When specifying a sector range to trim, chances are we might cross
	 * an erase-group boundary even if the amount of sectors is less than
	 * one erase-group.
	 * If we can only fit one erase-group in the controller timeout budget,
	 * we have to care that erase-group boundaries are not crossed by a
	 * single trim operation. We flag that special case with "eg_boundary".
	 * In all other cases we can just decrement qty and pretend that we
	 * always touch (qty + 1) erase-groups as a simple optimization.
	 */
	if (qty == 1)
		card->eg_boundary = 1;
	else
		qty--;

	/* Convert qty to sectors */
	if (card->erase_shift)
		max_discard = qty << card->erase_shift;
	else if (mmc_card_sd(card))
		max_discard = qty + 1;
	else
		max_discard = qty * card->erase_size;

	return max_discard;
}