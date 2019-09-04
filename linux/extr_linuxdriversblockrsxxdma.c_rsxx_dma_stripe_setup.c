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
struct TYPE_2__ {unsigned int lower_mask; unsigned int upper_mask; unsigned int upper_shift; unsigned int target_mask; unsigned int target_shift; } ;
struct rsxx_cardinfo {unsigned int n_targets; TYPE_1__ _stripe; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* ffs (unsigned int) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned int) ; 

__attribute__((used)) static int rsxx_dma_stripe_setup(struct rsxx_cardinfo *card,
			      unsigned int stripe_size8)
{
	if (!is_power_of_2(stripe_size8)) {
		dev_err(CARD_TO_DEV(card),
			"stripe_size is NOT a power of 2!\n");
		return -EINVAL;
	}

	card->_stripe.lower_mask = stripe_size8 - 1;

	card->_stripe.upper_mask  = ~(card->_stripe.lower_mask);
	card->_stripe.upper_shift = ffs(card->n_targets) - 1;

	card->_stripe.target_mask = card->n_targets - 1;
	card->_stripe.target_shift = ffs(stripe_size8) - 1;

	dev_dbg(CARD_TO_DEV(card), "_stripe.lower_mask   = x%016llx\n",
		card->_stripe.lower_mask);
	dev_dbg(CARD_TO_DEV(card), "_stripe.upper_shift  = x%016llx\n",
		card->_stripe.upper_shift);
	dev_dbg(CARD_TO_DEV(card), "_stripe.upper_mask   = x%016llx\n",
		card->_stripe.upper_mask);
	dev_dbg(CARD_TO_DEV(card), "_stripe.target_mask  = x%016llx\n",
		card->_stripe.target_mask);
	dev_dbg(CARD_TO_DEV(card), "_stripe.target_shift = x%016llx\n",
		card->_stripe.target_shift);

	return 0;
}