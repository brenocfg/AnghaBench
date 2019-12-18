#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  entity; } ;
struct TYPE_5__ {int /*<<< orphan*/  num_data_lanes; } ;
struct csi_state {scalar_t__ irq; int /*<<< orphan*/  lock; TYPE_2__ mipi_sd; int /*<<< orphan*/  clk_frequency; scalar_t__ wrap_clk; int /*<<< orphan*/  hs_settle; TYPE_1__ bus; int /*<<< orphan*/  events; struct device* dev; int /*<<< orphan*/  regs; struct platform_device* pdev; int /*<<< orphan*/  slock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct csi_state* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct csi_state*) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mipi_csis_clk_disable (struct csi_state*) ; 
 int mipi_csis_clk_enable (struct csi_state*) ; 
 int mipi_csis_clk_get (struct csi_state*) ; 
 int /*<<< orphan*/  mipi_csis_debugfs_exit (struct csi_state*) ; 
 int /*<<< orphan*/  mipi_csis_debugfs_init (struct csi_state*) ; 
 int /*<<< orphan*/  mipi_csis_events ; 
 int /*<<< orphan*/  mipi_csis_irq_handler ; 
 int mipi_csis_parse_dt (struct platform_device*,struct csi_state*) ; 
 int /*<<< orphan*/  mipi_csis_phy_init (struct csi_state*) ; 
 int /*<<< orphan*/  mipi_csis_phy_reset (struct csi_state*) ; 
 int mipi_csis_pm_resume (struct device*,int) ; 
 int mipi_csis_subdev_init (TYPE_2__*,struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mipi_csis_subdev_ops ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enabled (struct device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (TYPE_2__*) ; 

__attribute__((used)) static int mipi_csis_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *mem_res;
	struct csi_state *state;
	int ret;

	state = devm_kzalloc(dev, sizeof(*state), GFP_KERNEL);
	if (!state)
		return -ENOMEM;

	spin_lock_init(&state->slock);

	state->pdev = pdev;
	state->dev = dev;

	ret = mipi_csis_parse_dt(pdev, state);
	if (ret < 0) {
		dev_err(dev, "Failed to parse device tree: %d\n", ret);
		return ret;
	}

	mipi_csis_phy_init(state);
	mipi_csis_phy_reset(state);

	mem_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	state->regs = devm_ioremap_resource(dev, mem_res);
	if (IS_ERR(state->regs))
		return PTR_ERR(state->regs);

	state->irq = platform_get_irq(pdev, 0);
	if (state->irq < 0)
		return state->irq;

	ret = mipi_csis_clk_get(state);
	if (ret < 0)
		return ret;

	ret = mipi_csis_clk_enable(state);
	if (ret < 0) {
		dev_err(state->dev, "failed to enable clocks: %d\n", ret);
		return ret;
	}

	ret = devm_request_irq(dev, state->irq, mipi_csis_irq_handler,
			       0, dev_name(dev), state);
	if (ret) {
		dev_err(dev, "Interrupt request failed\n");
		goto disable_clock;
	}

	platform_set_drvdata(pdev, &state->mipi_sd);

	mutex_init(&state->lock);
	ret = mipi_csis_subdev_init(&state->mipi_sd, pdev,
				    &mipi_csis_subdev_ops);
	if (ret < 0)
		goto disable_clock;

	memcpy(state->events, mipi_csis_events, sizeof(state->events));

	mipi_csis_debugfs_init(state);
	pm_runtime_enable(dev);
	if (!pm_runtime_enabled(dev)) {
		ret = mipi_csis_pm_resume(dev, true);
		if (ret < 0)
			goto unregister_all;
	}

	dev_info(&pdev->dev, "lanes: %d, hs_settle: %d, wclk: %d, freq: %u\n",
		 state->bus.num_data_lanes, state->hs_settle,
		 state->wrap_clk ? 1 : 0, state->clk_frequency);

	return 0;

unregister_all:
	mipi_csis_debugfs_exit(state);
	media_entity_cleanup(&state->mipi_sd.entity);
	v4l2_async_unregister_subdev(&state->mipi_sd);
disable_clock:
	mipi_csis_clk_disable(state);
	mutex_destroy(&state->lock);

	return ret;
}