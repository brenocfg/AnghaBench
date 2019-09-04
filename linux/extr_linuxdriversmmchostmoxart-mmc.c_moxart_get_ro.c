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
struct moxart_host {scalar_t__ base; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ REG_STATUS ; 
 int WRITE_PROT ; 
 struct moxart_host* mmc_priv (struct mmc_host*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int moxart_get_ro(struct mmc_host *mmc)
{
	struct moxart_host *host = mmc_priv(mmc);

	return !!(readl(host->base + REG_STATUS) & WRITE_PROT);
}