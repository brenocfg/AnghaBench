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
struct msdc_host {scalar_t__ base; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ EMMC_IOCON ; 
 struct msdc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  sdr_clr_bits (scalar_t__,int) ; 
 int /*<<< orphan*/  sdr_set_bits (scalar_t__,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void msdc_hw_reset(struct mmc_host *mmc)
{
	struct msdc_host *host = mmc_priv(mmc);

	sdr_set_bits(host->base + EMMC_IOCON, 1);
	udelay(10); /* 10us is enough */
	sdr_clr_bits(host->base + EMMC_IOCON, 1);
}