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
struct TYPE_6__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  route_free; TYPE_2__* dev; } ;
struct lpc18xx_dmamux_data {TYPE_1__ dmarouter; int /*<<< orphan*/  lock; int /*<<< orphan*/  muxes; int /*<<< orphan*/  dma_master_requests; int /*<<< orphan*/  dma_mux_requests; int /*<<< orphan*/  reg; } ;
struct lpc18xx_dmamux {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_kcalloc (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct lpc18xx_dmamux_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc18xx_dmamux_free ; 
 int /*<<< orphan*/  lpc18xx_dmamux_reserve ; 
 int of_dma_router_register (struct device_node*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lpc18xx_dmamux_data*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_compatible (char*) ; 

__attribute__((used)) static int lpc18xx_dmamux_probe(struct platform_device *pdev)
{
	struct device_node *dma_np, *np = pdev->dev.of_node;
	struct lpc18xx_dmamux_data *dmamux;
	int ret;

	dmamux = devm_kzalloc(&pdev->dev, sizeof(*dmamux), GFP_KERNEL);
	if (!dmamux)
		return -ENOMEM;

	dmamux->reg = syscon_regmap_lookup_by_compatible("nxp,lpc1850-creg");
	if (IS_ERR(dmamux->reg)) {
		dev_err(&pdev->dev, "syscon lookup failed\n");
		return PTR_ERR(dmamux->reg);
	}

	ret = of_property_read_u32(np, "dma-requests",
				   &dmamux->dma_mux_requests);
	if (ret) {
		dev_err(&pdev->dev, "missing dma-requests property\n");
		return ret;
	}

	dma_np = of_parse_phandle(np, "dma-masters", 0);
	if (!dma_np) {
		dev_err(&pdev->dev, "can't get dma master\n");
		return -ENODEV;
	}

	ret = of_property_read_u32(dma_np, "dma-requests",
				   &dmamux->dma_master_requests);
	of_node_put(dma_np);
	if (ret) {
		dev_err(&pdev->dev, "missing master dma-requests property\n");
		return ret;
	}

	dmamux->muxes = devm_kcalloc(&pdev->dev, dmamux->dma_master_requests,
				     sizeof(struct lpc18xx_dmamux),
				     GFP_KERNEL);
	if (!dmamux->muxes)
		return -ENOMEM;

	spin_lock_init(&dmamux->lock);
	platform_set_drvdata(pdev, dmamux);
	dmamux->dmarouter.dev = &pdev->dev;
	dmamux->dmarouter.route_free = lpc18xx_dmamux_free;

	return of_dma_router_register(np, lpc18xx_dmamux_reserve,
				      &dmamux->dmarouter);
}