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
struct mmc_ios {int /*<<< orphan*/  clock; } ;
struct dw_mci {int /*<<< orphan*/  ciu_clk; int /*<<< orphan*/  bus_hz; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_mci_k3_set_ios(struct dw_mci *host, struct mmc_ios *ios)
{
	int ret;

	ret = clk_set_rate(host->ciu_clk, ios->clock);
	if (ret)
		dev_warn(host->dev, "failed to set rate %uHz\n", ios->clock);

	host->bus_hz = clk_get_rate(host->ciu_clk);
}