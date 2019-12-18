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
typedef  int /*<<< orphan*/  u32 ;
struct mmc_host {int dummy; } ;
struct meson_host {scalar_t__ regs; } ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SD_EMMC_STATUS ; 
 int /*<<< orphan*/  STATUS_DATI ; 
 struct meson_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static int meson_mmc_card_busy(struct mmc_host *mmc)
{
	struct meson_host *host = mmc_priv(mmc);
	u32 regval;

	regval = readl(host->regs + SD_EMMC_STATUS);

	/* We are only interrested in lines 0 to 3, so mask the other ones */
	return !(FIELD_GET(STATUS_DATI, regval) & 0xf);
}