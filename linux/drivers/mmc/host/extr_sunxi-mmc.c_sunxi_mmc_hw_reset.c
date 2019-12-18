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
struct sunxi_mmc_host {int dummy; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_HWRST ; 
 struct sunxi_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_writel (struct sunxi_mmc_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sunxi_mmc_hw_reset(struct mmc_host *mmc)
{
	struct sunxi_mmc_host *host = mmc_priv(mmc);
	mmc_writel(host, REG_HWRST, 0);
	udelay(10);
	mmc_writel(host, REG_HWRST, 1);
	udelay(300);
}