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
struct mmc_card {int dummy; } ;

/* Variables and functions */
 int mmc_select_hs400 (struct mmc_card*) ; 

int mmc_hs200_to_hs400(struct mmc_card *card)
{
	return mmc_select_hs400(card);
}