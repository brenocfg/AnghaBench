#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct soc_device_attribute {TYPE_2__* data; } ;
struct resource {scalar_t__ start; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct dsi_module_id_data {scalar_t__ address; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  last_reset; } ;
struct dsi_data {scalar_t__ irq; int num_lanes_supported; TYPE_2__* data; TYPE_4__* vc; int /*<<< orphan*/  syscon; int /*<<< orphan*/  module_id; void* vdds_dsi_reg; void* pll_base; void* phy_base; void* proto_base; int /*<<< orphan*/  te_timer; int /*<<< orphan*/  framedone_timeout_work; int /*<<< orphan*/  bus_lock; int /*<<< orphan*/  lock; TYPE_1__ irq_stats; int /*<<< orphan*/  irq_stats_lock; scalar_t__ errors; int /*<<< orphan*/  errors_lock; int /*<<< orphan*/  irq_lock; struct device* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_8__ {scalar_t__ vc_id; int /*<<< orphan*/ * dssdev; int /*<<< orphan*/  source; } ;
struct TYPE_7__ {TYPE_2__* data; } ;
struct TYPE_6__ {scalar_t__ model; int quirks; struct dsi_module_id_data* modules; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  DSI_GNQ ; 
 scalar_t__ DSI_MODEL_OMAP4 ; 
 scalar_t__ DSI_MODEL_OMAP5 ; 
 int DSI_QUIRK_GNQ ; 
 int /*<<< orphan*/  DSI_VC_SOURCE_L4 ; 
 int /*<<< orphan*/  DSSERR (char*,...) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int REG_GET (struct dsi_data*,int /*<<< orphan*/ ,int,int) ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct dsi_data*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct dsi_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get (struct device*,char*) ; 
 int devm_request_irq (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_component_ops ; 
 int /*<<< orphan*/  dsi_framedone_timeout_work_callback ; 
 int dsi_get_clocks (struct dsi_data*) ; 
 int dsi_init_output (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_of_match ; 
 int dsi_probe_of (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_runtime_get (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_runtime_put (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_soc_devices ; 
 int /*<<< orphan*/  dsi_te_timeout ; 
 int /*<<< orphan*/  dsi_uninit_output (struct dsi_data*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct device_node* of_find_node_by_name (int /*<<< orphan*/ *,char*) ; 
 TYPE_3__* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_platform_depopulate (struct device*) ; 
 int of_platform_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  omap_dsi_irq_handler ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 struct soc_device_attribute* soc_device_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (struct device_node*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi_probe(struct platform_device *pdev)
{
	const struct soc_device_attribute *soc;
	const struct dsi_module_id_data *d;
	struct device *dev = &pdev->dev;
	struct dsi_data *dsi;
	struct resource *dsi_mem;
	struct resource *res;
	unsigned int i;
	int r;

	dsi = devm_kzalloc(dev, sizeof(*dsi), GFP_KERNEL);
	if (!dsi)
		return -ENOMEM;

	dsi->dev = dev;
	dev_set_drvdata(dev, dsi);

	spin_lock_init(&dsi->irq_lock);
	spin_lock_init(&dsi->errors_lock);
	dsi->errors = 0;

#ifdef CONFIG_OMAP2_DSS_COLLECT_IRQ_STATS
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

	dsi_mem = platform_get_resource_byname(pdev, IORESOURCE_MEM, "proto");
	dsi->proto_base = devm_ioremap_resource(dev, dsi_mem);
	if (IS_ERR(dsi->proto_base))
		return PTR_ERR(dsi->proto_base);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "phy");
	dsi->phy_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(dsi->phy_base))
		return PTR_ERR(dsi->phy_base);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "pll");
	dsi->pll_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(dsi->pll_base))
		return PTR_ERR(dsi->pll_base);

	dsi->irq = platform_get_irq(pdev, 0);
	if (dsi->irq < 0) {
		DSSERR("platform_get_irq failed\n");
		return -ENODEV;
	}

	r = devm_request_irq(dev, dsi->irq, omap_dsi_irq_handler,
			     IRQF_SHARED, dev_name(dev), dsi);
	if (r < 0) {
		DSSERR("request_irq failed\n");
		return r;
	}

	dsi->vdds_dsi_reg = devm_regulator_get(dev, "vdd");
	if (IS_ERR(dsi->vdds_dsi_reg)) {
		if (PTR_ERR(dsi->vdds_dsi_reg) != -EPROBE_DEFER)
			DSSERR("can't get DSI VDD regulator\n");
		return PTR_ERR(dsi->vdds_dsi_reg);
	}

	soc = soc_device_match(dsi_soc_devices);
	if (soc)
		dsi->data = soc->data;
	else
		dsi->data = of_match_node(dsi_of_match, dev->of_node)->data;

	d = dsi->data->modules;
	while (d->address != 0 && d->address != dsi_mem->start)
		d++;

	if (d->address == 0) {
		DSSERR("unsupported DSI module\n");
		return -ENODEV;
	}

	dsi->module_id = d->id;

	if (dsi->data->model == DSI_MODEL_OMAP4 ||
	    dsi->data->model == DSI_MODEL_OMAP5) {
		struct device_node *np;

		/*
		 * The OMAP4/5 display DT bindings don't reference the padconf
		 * syscon. Our only option to retrieve it is to find it by name.
		 */
		np = of_find_node_by_name(NULL,
			dsi->data->model == DSI_MODEL_OMAP4 ?
			"omap4_padconf_global" : "omap5_padconf_global");
		if (!np)
			return -ENODEV;

		dsi->syscon = syscon_node_to_regmap(np);
		of_node_put(np);
	}

	/* DSI VCs initialization */
	for (i = 0; i < ARRAY_SIZE(dsi->vc); i++) {
		dsi->vc[i].source = DSI_VC_SOURCE_L4;
		dsi->vc[i].dssdev = NULL;
		dsi->vc[i].vc_id = 0;
	}

	r = dsi_get_clocks(dsi);
	if (r)
		return r;

	pm_runtime_enable(dev);

	/* DSI on OMAP3 doesn't have register DSI_GNQ, set number
	 * of data to 3 by default */
	if (dsi->data->quirks & DSI_QUIRK_GNQ) {
		dsi_runtime_get(dsi);
		/* NB_DATA_LANES */
		dsi->num_lanes_supported = 1 + REG_GET(dsi, DSI_GNQ, 11, 9);
		dsi_runtime_put(dsi);
	} else {
		dsi->num_lanes_supported = 3;
	}

	r = of_platform_populate(dev->of_node, NULL, NULL, dev);
	if (r) {
		DSSERR("Failed to populate DSI child devices: %d\n", r);
		goto err_pm_disable;
	}

	r = dsi_init_output(dsi);
	if (r)
		goto err_of_depopulate;

	r = dsi_probe_of(dsi);
	if (r) {
		DSSERR("Invalid DSI DT data\n");
		goto err_uninit_output;
	}

	r = component_add(&pdev->dev, &dsi_component_ops);
	if (r)
		goto err_uninit_output;

	return 0;

err_uninit_output:
	dsi_uninit_output(dsi);
err_of_depopulate:
	of_platform_depopulate(dev);
err_pm_disable:
	pm_runtime_disable(dev);
	return r;
}