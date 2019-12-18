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
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct TYPE_14__ {scalar_t__ of_node; } ;
struct platform_device {int id; TYPE_2__ dev; } ;
struct of_device_id {struct dsi_module_id_data* data; } ;
struct dsi_module_id_data {scalar_t__ address; int id; } ;
struct TYPE_13__ {int /*<<< orphan*/  last_reset; } ;
struct dsi_data {scalar_t__ irq; int module_id; int num_lanes_supported; int /*<<< orphan*/  line_buffer_size; TYPE_11__* vc; struct platform_device* pdev; void* pll_base; void* phy_base; void* proto_base; int /*<<< orphan*/  te_timer; int /*<<< orphan*/  framedone_timeout_work; int /*<<< orphan*/  bus_lock; int /*<<< orphan*/  lock; TYPE_1__ irq_stats; int /*<<< orphan*/  irq_stats_lock; scalar_t__ errors; int /*<<< orphan*/  errors_lock; int /*<<< orphan*/  irq_lock; } ;
struct device {int dummy; } ;
struct TYPE_12__ {scalar_t__ vc_id; int /*<<< orphan*/ * dssdev; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_11__*) ; 
 int /*<<< orphan*/  DSI_GNQ ; 
 scalar_t__ DSI_PHY_OFFSET ; 
 scalar_t__ DSI_PHY_SZ ; 
 scalar_t__ DSI_PLL_OFFSET ; 
 scalar_t__ DSI_PLL_SZ ; 
 scalar_t__ DSI_PROTO_SZ ; 
 int /*<<< orphan*/  DSI_REVISION ; 
 int /*<<< orphan*/  DSI_VC_SOURCE_L4 ; 
 int /*<<< orphan*/  DSSERR (char*,...) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FEAT_DSI_GNQ ; 
 int /*<<< orphan*/  FLD_GET (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int REG_GET (struct platform_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_2__*,struct dsi_data*) ; 
 void* devm_ioremap (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct dsi_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct platform_device*) ; 
 int /*<<< orphan*/  dsi1_dump_irqs ; 
 int /*<<< orphan*/  dsi1_dump_regs ; 
 int /*<<< orphan*/  dsi2_dump_irqs ; 
 int /*<<< orphan*/  dsi2_dump_regs ; 
 int /*<<< orphan*/  dsi_framedone_timeout_work_callback ; 
 int dsi_get_clocks (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_get_line_buf_size (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_init_output (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_init_pll_data (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_of_match ; 
 int dsi_probe_of (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_read_reg (struct platform_device*,int /*<<< orphan*/ ) ; 
 int dsi_runtime_get (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_runtime_put (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_te_timeout ; 
 int /*<<< orphan*/  dsi_uninit_output (struct platform_device*) ; 
 int /*<<< orphan*/  dss_debugfs_create_file (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ dss_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,scalar_t__) ; 
 int of_platform_populate (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  omap_dsi_irq_handler ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int dsi_bind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *dsidev = to_platform_device(dev);
	u32 rev;
	int r, i;
	struct dsi_data *dsi;
	struct resource *dsi_mem;
	struct resource *res;
	struct resource temp_res;

	dsi = devm_kzalloc(&dsidev->dev, sizeof(*dsi), GFP_KERNEL);
	if (!dsi)
		return -ENOMEM;

	dsi->pdev = dsidev;
	dev_set_drvdata(&dsidev->dev, dsi);

	spin_lock_init(&dsi->irq_lock);
	spin_lock_init(&dsi->errors_lock);
	dsi->errors = 0;

#ifdef CONFIG_FB_OMAP2_DSS_COLLECT_IRQ_STATS
	spin_lock_init(&dsi->irq_stats_lock);
	dsi->irq_stats.last_reset = jiffies;
#endif

	mutex_init(&dsi->lock);
	sema_init(&dsi->bus_lock, 1);

	INIT_DEFERRABLE_WORK(&dsi->framedone_timeout_work,
			     dsi_framedone_timeout_work_callback);

#ifdef DSI_CATCH_MISSING_TE
	timer_setup(&dsi->te_timer, dsi_te_timeout, 0);
#endif

	res = platform_get_resource_byname(dsidev, IORESOURCE_MEM, "proto");
	if (!res) {
		res = platform_get_resource(dsidev, IORESOURCE_MEM, 0);
		if (!res) {
			DSSERR("can't get IORESOURCE_MEM DSI\n");
			return -EINVAL;
		}

		temp_res.start = res->start;
		temp_res.end = temp_res.start + DSI_PROTO_SZ - 1;
		res = &temp_res;
	}

	dsi_mem = res;

	dsi->proto_base = devm_ioremap(&dsidev->dev, res->start,
		resource_size(res));
	if (!dsi->proto_base) {
		DSSERR("can't ioremap DSI protocol engine\n");
		return -ENOMEM;
	}

	res = platform_get_resource_byname(dsidev, IORESOURCE_MEM, "phy");
	if (!res) {
		res = platform_get_resource(dsidev, IORESOURCE_MEM, 0);
		if (!res) {
			DSSERR("can't get IORESOURCE_MEM DSI\n");
			return -EINVAL;
		}

		temp_res.start = res->start + DSI_PHY_OFFSET;
		temp_res.end = temp_res.start + DSI_PHY_SZ - 1;
		res = &temp_res;
	}

	dsi->phy_base = devm_ioremap(&dsidev->dev, res->start,
		resource_size(res));
	if (!dsi->phy_base) {
		DSSERR("can't ioremap DSI PHY\n");
		return -ENOMEM;
	}

	res = platform_get_resource_byname(dsidev, IORESOURCE_MEM, "pll");
	if (!res) {
		res = platform_get_resource(dsidev, IORESOURCE_MEM, 0);
		if (!res) {
			DSSERR("can't get IORESOURCE_MEM DSI\n");
			return -EINVAL;
		}

		temp_res.start = res->start + DSI_PLL_OFFSET;
		temp_res.end = temp_res.start + DSI_PLL_SZ - 1;
		res = &temp_res;
	}

	dsi->pll_base = devm_ioremap(&dsidev->dev, res->start,
		resource_size(res));
	if (!dsi->pll_base) {
		DSSERR("can't ioremap DSI PLL\n");
		return -ENOMEM;
	}

	dsi->irq = platform_get_irq(dsi->pdev, 0);
	if (dsi->irq < 0) {
		DSSERR("platform_get_irq failed\n");
		return -ENODEV;
	}

	r = devm_request_irq(&dsidev->dev, dsi->irq, omap_dsi_irq_handler,
			     IRQF_SHARED, dev_name(&dsidev->dev), dsi->pdev);
	if (r < 0) {
		DSSERR("request_irq failed\n");
		return r;
	}

	if (dsidev->dev.of_node) {
		const struct of_device_id *match;
		const struct dsi_module_id_data *d;

		match = of_match_node(dsi_of_match, dsidev->dev.of_node);
		if (!match) {
			DSSERR("unsupported DSI module\n");
			return -ENODEV;
		}

		d = match->data;

		while (d->address != 0 && d->address != dsi_mem->start)
			d++;

		if (d->address == 0) {
			DSSERR("unsupported DSI module\n");
			return -ENODEV;
		}

		dsi->module_id = d->id;
	} else {
		dsi->module_id = dsidev->id;
	}

	/* DSI VCs initialization */
	for (i = 0; i < ARRAY_SIZE(dsi->vc); i++) {
		dsi->vc[i].source = DSI_VC_SOURCE_L4;
		dsi->vc[i].dssdev = NULL;
		dsi->vc[i].vc_id = 0;
	}

	r = dsi_get_clocks(dsidev);
	if (r)
		return r;

	dsi_init_pll_data(dsidev);

	pm_runtime_enable(&dsidev->dev);

	r = dsi_runtime_get(dsidev);
	if (r)
		goto err_runtime_get;

	rev = dsi_read_reg(dsidev, DSI_REVISION);
	dev_dbg(&dsidev->dev, "OMAP DSI rev %d.%d\n",
	       FLD_GET(rev, 7, 4), FLD_GET(rev, 3, 0));

	/* DSI on OMAP3 doesn't have register DSI_GNQ, set number
	 * of data to 3 by default */
	if (dss_has_feature(FEAT_DSI_GNQ))
		/* NB_DATA_LANES */
		dsi->num_lanes_supported = 1 + REG_GET(dsidev, DSI_GNQ, 11, 9);
	else
		dsi->num_lanes_supported = 3;

	dsi->line_buffer_size = dsi_get_line_buf_size(dsidev);

	dsi_init_output(dsidev);

	if (dsidev->dev.of_node) {
		r = dsi_probe_of(dsidev);
		if (r) {
			DSSERR("Invalid DSI DT data\n");
			goto err_probe_of;
		}

		r = of_platform_populate(dsidev->dev.of_node, NULL, NULL,
			&dsidev->dev);
		if (r)
			DSSERR("Failed to populate DSI child devices: %d\n", r);
	}

	dsi_runtime_put(dsidev);

	if (dsi->module_id == 0)
		dss_debugfs_create_file("dsi1_regs", dsi1_dump_regs);
	else if (dsi->module_id == 1)
		dss_debugfs_create_file("dsi2_regs", dsi2_dump_regs);

#ifdef CONFIG_FB_OMAP2_DSS_COLLECT_IRQ_STATS
	if (dsi->module_id == 0)
		dss_debugfs_create_file("dsi1_irqs", dsi1_dump_irqs);
	else if (dsi->module_id == 1)
		dss_debugfs_create_file("dsi2_irqs", dsi2_dump_irqs);
#endif

	return 0;

err_probe_of:
	dsi_uninit_output(dsidev);
	dsi_runtime_put(dsidev);

err_runtime_get:
	pm_runtime_disable(&dsidev->dev);
	return r;
}