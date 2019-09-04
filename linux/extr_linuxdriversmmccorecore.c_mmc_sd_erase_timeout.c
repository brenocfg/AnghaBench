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
struct TYPE_2__ {int erase_timeout; unsigned int erase_offset; } ;
struct mmc_card {TYPE_1__ ssr; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int mmc_sd_erase_timeout(struct mmc_card *card,
					 unsigned int arg,
					 unsigned int qty)
{
	unsigned int erase_timeout;

	if (card->ssr.erase_timeout) {
		/* Erase timeout specified in SD Status Register (SSR) */
		erase_timeout = card->ssr.erase_timeout * qty +
				card->ssr.erase_offset;
	} else {
		/*
		 * Erase timeout not specified in SD Status Register (SSR) so
		 * use 250ms per write block.
		 */
		erase_timeout = 250 * qty;
	}

	/* Must not be less than 1 second */
	if (erase_timeout < 1000)
		erase_timeout = 1000;

	return erase_timeout;
}