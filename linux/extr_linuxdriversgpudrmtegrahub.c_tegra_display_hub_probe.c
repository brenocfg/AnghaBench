#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tegra_windowgroup {unsigned int index; void* rst; scalar_t__ usecount; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dev; int /*<<< orphan*/ * ops; int /*<<< orphan*/  list; } ;
struct tegra_display_hub {TYPE_2__ client; void* rst; struct tegra_windowgroup* wgrps; TYPE_1__* soc; void* clk_hub; void* clk_dsc; void* clk_disp; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  id ;
struct TYPE_3__ {unsigned int num_wgrps; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct tegra_windowgroup* devm_kcalloc (int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ ) ; 
 struct tegra_display_hub* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* devm_reset_control_get (int /*<<< orphan*/ *,char*) ; 
 int host1x_client_register (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_display_hub*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int reset_control_assert (void*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  tegra_display_hub_ops ; 

__attribute__((used)) static int tegra_display_hub_probe(struct platform_device *pdev)
{
	struct tegra_display_hub *hub;
	unsigned int i;
	int err;

	hub = devm_kzalloc(&pdev->dev, sizeof(*hub), GFP_KERNEL);
	if (!hub)
		return -ENOMEM;

	hub->soc = of_device_get_match_data(&pdev->dev);

	hub->clk_disp = devm_clk_get(&pdev->dev, "disp");
	if (IS_ERR(hub->clk_disp)) {
		err = PTR_ERR(hub->clk_disp);
		return err;
	}

	hub->clk_dsc = devm_clk_get(&pdev->dev, "dsc");
	if (IS_ERR(hub->clk_dsc)) {
		err = PTR_ERR(hub->clk_dsc);
		return err;
	}

	hub->clk_hub = devm_clk_get(&pdev->dev, "hub");
	if (IS_ERR(hub->clk_hub)) {
		err = PTR_ERR(hub->clk_hub);
		return err;
	}

	hub->rst = devm_reset_control_get(&pdev->dev, "misc");
	if (IS_ERR(hub->rst)) {
		err = PTR_ERR(hub->rst);
		return err;
	}

	hub->wgrps = devm_kcalloc(&pdev->dev, hub->soc->num_wgrps,
				  sizeof(*hub->wgrps), GFP_KERNEL);
	if (!hub->wgrps)
		return -ENOMEM;

	for (i = 0; i < hub->soc->num_wgrps; i++) {
		struct tegra_windowgroup *wgrp = &hub->wgrps[i];
		char id[8];

		snprintf(id, sizeof(id), "wgrp%u", i);
		mutex_init(&wgrp->lock);
		wgrp->usecount = 0;
		wgrp->index = i;

		wgrp->rst = devm_reset_control_get(&pdev->dev, id);
		if (IS_ERR(wgrp->rst))
			return PTR_ERR(wgrp->rst);

		err = reset_control_assert(wgrp->rst);
		if (err < 0)
			return err;
	}

	/* XXX: enable clock across reset? */
	err = reset_control_assert(hub->rst);
	if (err < 0)
		return err;

	platform_set_drvdata(pdev, hub);
	pm_runtime_enable(&pdev->dev);

	INIT_LIST_HEAD(&hub->client.list);
	hub->client.ops = &tegra_display_hub_ops;
	hub->client.dev = &pdev->dev;

	err = host1x_client_register(&hub->client);
	if (err < 0)
		dev_err(&pdev->dev, "failed to register host1x client: %d\n",
			err);

	return err;
}