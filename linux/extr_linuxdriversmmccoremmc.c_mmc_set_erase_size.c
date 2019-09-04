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
struct TYPE_4__ {int /*<<< orphan*/  erase_size; } ;
struct TYPE_3__ {int erase_group_def; int /*<<< orphan*/  hc_erase_size; } ;
struct mmc_card {TYPE_2__ csd; int /*<<< orphan*/  erase_size; TYPE_1__ ext_csd; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_init_erase (struct mmc_card*) ; 

__attribute__((used)) static void mmc_set_erase_size(struct mmc_card *card)
{
	if (card->ext_csd.erase_group_def & 1)
		card->erase_size = card->ext_csd.hc_erase_size;
	else
		card->erase_size = card->csd.erase_size;

	mmc_init_erase(card);
}