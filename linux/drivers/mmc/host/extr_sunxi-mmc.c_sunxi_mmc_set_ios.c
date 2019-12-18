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
struct mmc_ios {int /*<<< orphan*/  bus_width; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 struct sunxi_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  sunxi_mmc_card_power (struct sunxi_mmc_host*,struct mmc_ios*) ; 
 int /*<<< orphan*/  sunxi_mmc_set_bus_width (struct sunxi_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunxi_mmc_set_clk (struct sunxi_mmc_host*,struct mmc_ios*) ; 

__attribute__((used)) static void sunxi_mmc_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct sunxi_mmc_host *host = mmc_priv(mmc);

	sunxi_mmc_card_power(host, ios);
	sunxi_mmc_set_bus_width(host, ios->bus_width);
	sunxi_mmc_set_clk(host, ios);
}