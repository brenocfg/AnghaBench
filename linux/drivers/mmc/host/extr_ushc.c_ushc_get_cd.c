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
struct ushc_data {int last_status; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int USHC_INT_STATUS_CARD_PRESENT ; 
 struct ushc_data* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static int ushc_get_cd(struct mmc_host *mmc)
{
	struct ushc_data *ushc = mmc_priv(mmc);

	return !!(ushc->last_status & USHC_INT_STATUS_CARD_PRESENT);
}