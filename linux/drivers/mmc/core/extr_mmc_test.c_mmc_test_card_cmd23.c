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
struct TYPE_2__ {int cmds; } ;
struct mmc_card {TYPE_1__ scr; } ;

/* Variables and functions */
 int SD_SCR_CMD23_SUPPORT ; 
 scalar_t__ mmc_card_mmc (struct mmc_card*) ; 
 scalar_t__ mmc_card_sd (struct mmc_card*) ; 

__attribute__((used)) static bool mmc_test_card_cmd23(struct mmc_card *card)
{
	return mmc_card_mmc(card) ||
	       (mmc_card_sd(card) && card->scr.cmds & SD_SCR_CMD23_SUPPORT);
}