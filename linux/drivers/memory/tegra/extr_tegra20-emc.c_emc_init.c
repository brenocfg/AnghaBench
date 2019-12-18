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
struct tegra_emc {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; int /*<<< orphan*/  pll_m; int /*<<< orphan*/  emc_mux; int /*<<< orphan*/  backup_clk; } ;

/* Variables and functions */
 int clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int emc_init(struct tegra_emc *emc, unsigned long rate)
{
	int err;

	err = clk_set_parent(emc->emc_mux, emc->backup_clk);
	if (err) {
		dev_err(emc->dev,
			"failed to reparent to backup source: %d\n", err);
		return err;
	}

	err = clk_set_rate(emc->pll_m, rate);
	if (err) {
		dev_err(emc->dev,
			"failed to change pll_m rate: %d\n", err);
		return err;
	}

	err = clk_set_parent(emc->emc_mux, emc->pll_m);
	if (err) {
		dev_err(emc->dev,
			"failed to reparent to pll_m: %d\n", err);
		return err;
	}

	err = clk_set_rate(emc->clk, rate);
	if (err) {
		dev_err(emc->dev,
			"failed to change emc rate: %d\n", err);
		return err;
	}

	return 0;
}