#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_3__* dev; int /*<<< orphan*/ * ops; } ;
struct TYPE_18__ {TYPE_3__* dev; int /*<<< orphan*/ * ops; int /*<<< orphan*/  list; } ;
struct TYPE_14__ {int /*<<< orphan*/  polled; } ;
struct TYPE_15__ {TYPE_1__ connector; TYPE_3__* dev; } ;
struct tegra_dsi {int video_fifo_depth; int host_fifo_depth; int lanes; void* mipi; TYPE_5__ host; TYPE_7__ client; void* regs; void* vdd; void* clk_parent; void* clk_lp; void* clk; void* rst; int /*<<< orphan*/  format; int /*<<< orphan*/  flags; TYPE_2__ output; TYPE_3__* dev; } ;
struct resource {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  pm_domain; } ;
struct platform_device {TYPE_3__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MIPI_DSI_FMT_RGB888 ; 
 int /*<<< orphan*/  MIPI_DSI_MODE_VIDEO ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 void* devm_clk_get (TYPE_3__*,char*) ; 
 void* devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct tegra_dsi* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get (TYPE_3__*,char*) ; 
 void* devm_reset_control_get (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dsi_client_ops ; 
 int host1x_client_register (TYPE_7__*) ; 
 int mipi_dsi_host_register (TYPE_5__*) ; 
 int /*<<< orphan*/  mipi_dsi_host_unregister (TYPE_5__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_dsi*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_3__*) ; 
 int tegra_dsi_ganged_probe (struct tegra_dsi*) ; 
 int /*<<< orphan*/  tegra_dsi_host_ops ; 
 int tegra_dsi_setup_clocks (struct tegra_dsi*) ; 
 int /*<<< orphan*/  tegra_mipi_free (void*) ; 
 void* tegra_mipi_request (TYPE_3__*) ; 
 int tegra_output_probe (TYPE_2__*) ; 

__attribute__((used)) static int tegra_dsi_probe(struct platform_device *pdev)
{
	struct tegra_dsi *dsi;
	struct resource *regs;
	int err;

	dsi = devm_kzalloc(&pdev->dev, sizeof(*dsi), GFP_KERNEL);
	if (!dsi)
		return -ENOMEM;

	dsi->output.dev = dsi->dev = &pdev->dev;
	dsi->video_fifo_depth = 1920;
	dsi->host_fifo_depth = 64;

	err = tegra_dsi_ganged_probe(dsi);
	if (err < 0)
		return err;

	err = tegra_output_probe(&dsi->output);
	if (err < 0)
		return err;

	dsi->output.connector.polled = DRM_CONNECTOR_POLL_HPD;

	/*
	 * Assume these values by default. When a DSI peripheral driver
	 * attaches to the DSI host, the parameters will be taken from
	 * the attached device.
	 */
	dsi->flags = MIPI_DSI_MODE_VIDEO;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->lanes = 4;

	if (!pdev->dev.pm_domain) {
		dsi->rst = devm_reset_control_get(&pdev->dev, "dsi");
		if (IS_ERR(dsi->rst))
			return PTR_ERR(dsi->rst);
	}

	dsi->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(dsi->clk)) {
		dev_err(&pdev->dev, "cannot get DSI clock\n");
		return PTR_ERR(dsi->clk);
	}

	dsi->clk_lp = devm_clk_get(&pdev->dev, "lp");
	if (IS_ERR(dsi->clk_lp)) {
		dev_err(&pdev->dev, "cannot get low-power clock\n");
		return PTR_ERR(dsi->clk_lp);
	}

	dsi->clk_parent = devm_clk_get(&pdev->dev, "parent");
	if (IS_ERR(dsi->clk_parent)) {
		dev_err(&pdev->dev, "cannot get parent clock\n");
		return PTR_ERR(dsi->clk_parent);
	}

	dsi->vdd = devm_regulator_get(&pdev->dev, "avdd-dsi-csi");
	if (IS_ERR(dsi->vdd)) {
		dev_err(&pdev->dev, "cannot get VDD supply\n");
		return PTR_ERR(dsi->vdd);
	}

	err = tegra_dsi_setup_clocks(dsi);
	if (err < 0) {
		dev_err(&pdev->dev, "cannot setup clocks\n");
		return err;
	}

	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dsi->regs = devm_ioremap_resource(&pdev->dev, regs);
	if (IS_ERR(dsi->regs))
		return PTR_ERR(dsi->regs);

	dsi->mipi = tegra_mipi_request(&pdev->dev);
	if (IS_ERR(dsi->mipi))
		return PTR_ERR(dsi->mipi);

	dsi->host.ops = &tegra_dsi_host_ops;
	dsi->host.dev = &pdev->dev;

	err = mipi_dsi_host_register(&dsi->host);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to register DSI host: %d\n", err);
		goto mipi_free;
	}

	platform_set_drvdata(pdev, dsi);
	pm_runtime_enable(&pdev->dev);

	INIT_LIST_HEAD(&dsi->client.list);
	dsi->client.ops = &dsi_client_ops;
	dsi->client.dev = &pdev->dev;

	err = host1x_client_register(&dsi->client);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to register host1x client: %d\n",
			err);
		goto unregister;
	}

	return 0;

unregister:
	mipi_dsi_host_unregister(&dsi->host);
mipi_free:
	tegra_mipi_free(dsi->mipi);
	return err;
}