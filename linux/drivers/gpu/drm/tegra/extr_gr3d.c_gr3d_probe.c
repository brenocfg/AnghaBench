#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct host1x_syncpt {int dummy; } ;
struct TYPE_12__ {int num_syncpts; struct host1x_syncpt** syncpts; int /*<<< orphan*/  class; TYPE_3__* dev; int /*<<< orphan*/ * ops; int /*<<< orphan*/  list; } ;
struct TYPE_9__ {TYPE_4__ base; int /*<<< orphan*/ * ops; int /*<<< orphan*/  version; int /*<<< orphan*/  list; } ;
struct gr3d {int /*<<< orphan*/  addr_regs; TYPE_1__ client; TYPE_2__* soc; void* rst_secondary; void* clk_secondary; void* rst; void* clk; } ;
struct device_node {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HOST1X_CLASS_GR3D ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  TEGRA_POWERGATE_3D ; 
 int /*<<< orphan*/  TEGRA_POWERGATE_3D1 ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 void* devm_clk_get (TYPE_3__*,char*) ; 
 void* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 void* devm_reset_control_get (TYPE_3__*,char*) ; 
 int /*<<< orphan*/ * gr3d_addr_regs ; 
 int /*<<< orphan*/  gr3d_client_ops ; 
 int /*<<< orphan*/  gr3d_ops ; 
 int host1x_client_register (TYPE_4__*) ; 
 TYPE_2__* of_device_get_match_data (TYPE_3__*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gr3d*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tegra_powergate_sequence_power_up (int /*<<< orphan*/ ,void*,void*) ; 

__attribute__((used)) static int gr3d_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct host1x_syncpt **syncpts;
	struct gr3d *gr3d;
	unsigned int i;
	int err;

	gr3d = devm_kzalloc(&pdev->dev, sizeof(*gr3d), GFP_KERNEL);
	if (!gr3d)
		return -ENOMEM;

	gr3d->soc = of_device_get_match_data(&pdev->dev);

	syncpts = devm_kzalloc(&pdev->dev, sizeof(*syncpts), GFP_KERNEL);
	if (!syncpts)
		return -ENOMEM;

	gr3d->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(gr3d->clk)) {
		dev_err(&pdev->dev, "cannot get clock\n");
		return PTR_ERR(gr3d->clk);
	}

	gr3d->rst = devm_reset_control_get(&pdev->dev, "3d");
	if (IS_ERR(gr3d->rst)) {
		dev_err(&pdev->dev, "cannot get reset\n");
		return PTR_ERR(gr3d->rst);
	}

	if (of_device_is_compatible(np, "nvidia,tegra30-gr3d")) {
		gr3d->clk_secondary = devm_clk_get(&pdev->dev, "3d2");
		if (IS_ERR(gr3d->clk_secondary)) {
			dev_err(&pdev->dev, "cannot get secondary clock\n");
			return PTR_ERR(gr3d->clk_secondary);
		}

		gr3d->rst_secondary = devm_reset_control_get(&pdev->dev,
								"3d2");
		if (IS_ERR(gr3d->rst_secondary)) {
			dev_err(&pdev->dev, "cannot get secondary reset\n");
			return PTR_ERR(gr3d->rst_secondary);
		}
	}

	err = tegra_powergate_sequence_power_up(TEGRA_POWERGATE_3D, gr3d->clk,
						gr3d->rst);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to power up 3D unit\n");
		return err;
	}

	if (gr3d->clk_secondary) {
		err = tegra_powergate_sequence_power_up(TEGRA_POWERGATE_3D1,
							gr3d->clk_secondary,
							gr3d->rst_secondary);
		if (err < 0) {
			dev_err(&pdev->dev,
				"failed to power up secondary 3D unit\n");
			return err;
		}
	}

	INIT_LIST_HEAD(&gr3d->client.base.list);
	gr3d->client.base.ops = &gr3d_client_ops;
	gr3d->client.base.dev = &pdev->dev;
	gr3d->client.base.class = HOST1X_CLASS_GR3D;
	gr3d->client.base.syncpts = syncpts;
	gr3d->client.base.num_syncpts = 1;

	INIT_LIST_HEAD(&gr3d->client.list);
	gr3d->client.version = gr3d->soc->version;
	gr3d->client.ops = &gr3d_ops;

	err = host1x_client_register(&gr3d->client.base);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to register host1x client: %d\n",
			err);
		return err;
	}

	/* initialize address register map */
	for (i = 0; i < ARRAY_SIZE(gr3d_addr_regs); i++)
		set_bit(gr3d_addr_regs[i], gr3d->addr_regs);

	platform_set_drvdata(pdev, gr3d);

	return 0;
}