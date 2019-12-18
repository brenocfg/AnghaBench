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
typedef  int /*<<< orphan*/  u32 ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct mipi_dsi_host {int /*<<< orphan*/ * ops; struct device* dev; } ;
struct mcde_dsi {struct mipi_dsi_host dsi_host; scalar_t__ regs; scalar_t__ prcmu; struct device* dev; } ;

/* Variables and functions */
 scalar_t__ DSI_ID_REG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 scalar_t__ devm_ioremap_resource (struct device*,struct resource*) ; 
 struct mcde_dsi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcde_dsi_component_ops ; 
 int /*<<< orphan*/  mcde_dsi_host_ops ; 
 int mipi_dsi_host_register (struct mipi_dsi_host*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mcde_dsi*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 scalar_t__ syscon_regmap_lookup_by_compatible (char*) ; 

__attribute__((used)) static int mcde_dsi_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct mcde_dsi *d;
	struct mipi_dsi_host *host;
	struct resource *res;
	u32 dsi_id;
	int ret;

	d = devm_kzalloc(dev, sizeof(*d), GFP_KERNEL);
	if (!d)
		return -ENOMEM;
	d->dev = dev;
	platform_set_drvdata(pdev, d);

	/* Get a handle on the PRCMU so we can do reset */
	d->prcmu =
		syscon_regmap_lookup_by_compatible("stericsson,db8500-prcmu");
	if (IS_ERR(d->prcmu)) {
		dev_err(dev, "no PRCMU regmap\n");
		return PTR_ERR(d->prcmu);
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	d->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(d->regs)) {
		dev_err(dev, "no DSI regs\n");
		return PTR_ERR(d->regs);
	}

	dsi_id = readl(d->regs + DSI_ID_REG);
	dev_info(dev, "HW revision 0x%08x\n", dsi_id);

	host = &d->dsi_host;
	host->dev = dev;
	host->ops = &mcde_dsi_host_ops;
	ret = mipi_dsi_host_register(host);
	if (ret < 0) {
		dev_err(dev, "failed to register DSI host: %d\n", ret);
		return ret;
	}
	dev_info(dev, "registered DSI host\n");

	platform_set_drvdata(pdev, d);
	return component_add(dev, &mcde_dsi_component_ops);
}