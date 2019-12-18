#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  notifier_call; } ;
struct tegra_emc {int num_timings; void* pll_m; void* backup_clk; TYPE_10__ clk_nb; void* clk; TYPE_1__* timings; void* emc_mux; void* regs; TYPE_2__* dev; int /*<<< orphan*/  clk_handshake_complete; } ;
struct resource {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* clk_get_parent (void*) ; 
 void* clk_get_sys (int /*<<< orphan*/ *,char*) ; 
 int clk_notifier_register (void*,TYPE_10__*) ; 
 int /*<<< orphan*/  clk_notifier_unregister (void*,TYPE_10__*) ; 
 int /*<<< orphan*/  clk_put (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 void* devm_clk_get (TYPE_2__*,char*) ; 
 void* devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct tegra_emc* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_emc*) ; 
 int emc_init (struct tegra_emc*,int /*<<< orphan*/ ) ; 
 int emc_setup_hw (struct tegra_emc*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ of_get_child_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_emc_clk_change_notify ; 
 struct device_node* tegra_emc_find_node_by_ram_code (TYPE_2__*) ; 
 int /*<<< orphan*/  tegra_emc_isr ; 
 int tegra_emc_load_timings_from_dt (struct tegra_emc*,struct device_node*) ; 

__attribute__((used)) static int tegra_emc_probe(struct platform_device *pdev)
{
	struct device_node *np;
	struct tegra_emc *emc;
	struct resource *res;
	int irq, err;

	/* driver has nothing to do in a case of memory timing absence */
	if (of_get_child_count(pdev->dev.of_node) == 0) {
		dev_info(&pdev->dev,
			 "EMC device tree node doesn't have memory timings\n");
		return 0;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(&pdev->dev, "interrupt not specified\n");
		dev_err(&pdev->dev, "please update your device tree\n");
		return irq;
	}

	np = tegra_emc_find_node_by_ram_code(&pdev->dev);
	if (!np)
		return -EINVAL;

	emc = devm_kzalloc(&pdev->dev, sizeof(*emc), GFP_KERNEL);
	if (!emc) {
		of_node_put(np);
		return -ENOMEM;
	}

	init_completion(&emc->clk_handshake_complete);
	emc->clk_nb.notifier_call = tegra_emc_clk_change_notify;
	emc->dev = &pdev->dev;

	err = tegra_emc_load_timings_from_dt(emc, np);
	of_node_put(np);
	if (err)
		return err;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	emc->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(emc->regs))
		return PTR_ERR(emc->regs);

	err = emc_setup_hw(emc);
	if (err)
		return err;

	err = devm_request_irq(&pdev->dev, irq, tegra_emc_isr, 0,
			       dev_name(&pdev->dev), emc);
	if (err) {
		dev_err(&pdev->dev, "failed to request IRQ#%u: %d\n", irq, err);
		return err;
	}

	emc->clk = devm_clk_get(&pdev->dev, "emc");
	if (IS_ERR(emc->clk)) {
		err = PTR_ERR(emc->clk);
		dev_err(&pdev->dev, "failed to get emc clock: %d\n", err);
		return err;
	}

	emc->pll_m = clk_get_sys(NULL, "pll_m");
	if (IS_ERR(emc->pll_m)) {
		err = PTR_ERR(emc->pll_m);
		dev_err(&pdev->dev, "failed to get pll_m clock: %d\n", err);
		return err;
	}

	emc->backup_clk = clk_get_sys(NULL, "pll_p");
	if (IS_ERR(emc->backup_clk)) {
		err = PTR_ERR(emc->backup_clk);
		dev_err(&pdev->dev, "failed to get pll_p clock: %d\n", err);
		goto put_pll_m;
	}

	emc->emc_mux = clk_get_parent(emc->clk);
	if (IS_ERR(emc->emc_mux)) {
		err = PTR_ERR(emc->emc_mux);
		dev_err(&pdev->dev, "failed to get emc_mux clock: %d\n", err);
		goto put_backup;
	}

	err = clk_notifier_register(emc->clk, &emc->clk_nb);
	if (err) {
		dev_err(&pdev->dev, "failed to register clk notifier: %d\n",
			err);
		goto put_backup;
	}

	/* set DRAM clock rate to maximum */
	err = emc_init(emc, emc->timings[emc->num_timings - 1].rate);
	if (err) {
		dev_err(&pdev->dev, "failed to initialize EMC clock rate: %d\n",
			err);
		goto unreg_notifier;
	}

	return 0;

unreg_notifier:
	clk_notifier_unregister(emc->clk, &emc->clk_nb);
put_backup:
	clk_put(emc->backup_clk);
put_pll_m:
	clk_put(emc->pll_m);

	return err;
}