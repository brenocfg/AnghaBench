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
struct sdricoh_host {int dummy; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R21C_STATUS ; 
 int /*<<< orphan*/  R2E4_STATUS_RESP ; 
 unsigned int STATUS_CARD_LOCKED ; 
 struct sdricoh_host* mmc_priv (struct mmc_host*) ; 
 unsigned int sdricoh_readl (struct sdricoh_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdricoh_writel (struct sdricoh_host*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ switchlocked ; 

__attribute__((used)) static int sdricoh_get_ro(struct mmc_host *mmc)
{
	struct sdricoh_host *host = mmc_priv(mmc);
	unsigned int status;

	status = sdricoh_readl(host, R21C_STATUS);
	sdricoh_writel(host, R2E4_STATUS_RESP, status);

	/* some notebooks seem to have the locked flag switched */
	if (switchlocked)
		return !(status & STATUS_CARD_LOCKED);

	return (status & STATUS_CARD_LOCKED);
}