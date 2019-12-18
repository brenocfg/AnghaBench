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
typedef  int u32 ;
struct msdc_host {scalar_t__ base; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ MSDC_PS ; 
 struct msdc_host* mmc_priv (struct mmc_host*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int msdc_card_busy(struct mmc_host *mmc)
{
	struct msdc_host *host = mmc_priv(mmc);
	u32 status = readl(host->base + MSDC_PS);

	/* only check if data0 is low */
	return !(status & BIT(16));
}