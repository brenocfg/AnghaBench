#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct soc_device_attribute {int /*<<< orphan*/  data; } ;
struct resource {int dummy; } ;
struct TYPE_8__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct dss_device {int /*<<< orphan*/ * dispc_ops; struct dispc_device* dispc; } ;
struct dispc_device {scalar_t__ irq; int /*<<< orphan*/  debugfs; int /*<<< orphan*/  syscon_pol_offset; int /*<<< orphan*/  syscon_pol; struct platform_device* pdev; int /*<<< orphan*/  base; int /*<<< orphan*/  feat; int /*<<< orphan*/  control_lock; struct dss_device* dss; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_REVISION ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FLD_GET (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _omap_dispc_initial_config (struct dispc_device*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 int /*<<< orphan*/  dispc_dump_regs ; 
 int dispc_errata_i734_wa_init (struct dispc_device*) ; 
 int dispc_init_gamma_tables (struct dispc_device*) ; 
 int /*<<< orphan*/  dispc_of_match ; 
 int /*<<< orphan*/  dispc_ops ; 
 int /*<<< orphan*/  dispc_read_reg (struct dispc_device*,int /*<<< orphan*/ ) ; 
 int dispc_runtime_get (struct dispc_device*) ; 
 int /*<<< orphan*/  dispc_runtime_put (struct dispc_device*) ; 
 int /*<<< orphan*/  dispc_soc_devices ; 
 int /*<<< orphan*/  dss_debugfs_create_file (struct dss_device*,char*,int /*<<< orphan*/ ,struct dispc_device*) ; 
 struct dss_device* dss_get_device (struct device*) ; 
 int /*<<< orphan*/  kfree (struct dispc_device*) ; 
 struct dispc_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_3__* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32_index (struct device_node*,char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dispc_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 struct soc_device_attribute* soc_device_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int dispc_bind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	const struct soc_device_attribute *soc;
	struct dss_device *dss = dss_get_device(master);
	struct dispc_device *dispc;
	u32 rev;
	int r = 0;
	struct resource *dispc_mem;
	struct device_node *np = pdev->dev.of_node;

	dispc = kzalloc(sizeof(*dispc), GFP_KERNEL);
	if (!dispc)
		return -ENOMEM;

	dispc->pdev = pdev;
	platform_set_drvdata(pdev, dispc);
	dispc->dss = dss;

	spin_lock_init(&dispc->control_lock);

	/*
	 * The OMAP3-based models can't be told apart using the compatible
	 * string, use SoC device matching.
	 */
	soc = soc_device_match(dispc_soc_devices);
	if (soc)
		dispc->feat = soc->data;
	else
		dispc->feat = of_match_device(dispc_of_match, &pdev->dev)->data;

	r = dispc_errata_i734_wa_init(dispc);
	if (r)
		goto err_free;

	dispc_mem = platform_get_resource(dispc->pdev, IORESOURCE_MEM, 0);
	dispc->base = devm_ioremap_resource(&pdev->dev, dispc_mem);
	if (IS_ERR(dispc->base)) {
		r = PTR_ERR(dispc->base);
		goto err_free;
	}

	dispc->irq = platform_get_irq(dispc->pdev, 0);
	if (dispc->irq < 0) {
		DSSERR("platform_get_irq failed\n");
		r = -ENODEV;
		goto err_free;
	}

	if (np && of_property_read_bool(np, "syscon-pol")) {
		dispc->syscon_pol = syscon_regmap_lookup_by_phandle(np, "syscon-pol");
		if (IS_ERR(dispc->syscon_pol)) {
			dev_err(&pdev->dev, "failed to get syscon-pol regmap\n");
			r = PTR_ERR(dispc->syscon_pol);
			goto err_free;
		}

		if (of_property_read_u32_index(np, "syscon-pol", 1,
				&dispc->syscon_pol_offset)) {
			dev_err(&pdev->dev, "failed to get syscon-pol offset\n");
			r = -EINVAL;
			goto err_free;
		}
	}

	r = dispc_init_gamma_tables(dispc);
	if (r)
		goto err_free;

	pm_runtime_enable(&pdev->dev);

	r = dispc_runtime_get(dispc);
	if (r)
		goto err_runtime_get;

	_omap_dispc_initial_config(dispc);

	rev = dispc_read_reg(dispc, DISPC_REVISION);
	dev_dbg(&pdev->dev, "OMAP DISPC rev %d.%d\n",
	       FLD_GET(rev, 7, 4), FLD_GET(rev, 3, 0));

	dispc_runtime_put(dispc);

	dss->dispc = dispc;
	dss->dispc_ops = &dispc_ops;

	dispc->debugfs = dss_debugfs_create_file(dss, "dispc", dispc_dump_regs,
						 dispc);

	return 0;

err_runtime_get:
	pm_runtime_disable(&pdev->dev);
err_free:
	kfree(dispc);
	return r;
}