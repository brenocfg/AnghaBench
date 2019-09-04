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
struct toshsd_host {scalar_t__ ioaddr; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ SD_CARDSTATUS ; 
 int SD_CARD_PRESENT_0 ; 
 int ioread16 (scalar_t__) ; 
 struct toshsd_host* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static int toshsd_get_cd(struct mmc_host *mmc)
{
	struct toshsd_host *host = mmc_priv(mmc);

	return !!(ioread16(host->ioaddr + SD_CARDSTATUS) & SD_CARD_PRESENT_0);
}