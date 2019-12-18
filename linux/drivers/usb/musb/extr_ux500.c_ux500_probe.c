#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ux500_glue {struct clk* clk; struct platform_device* musb; TYPE_2__* dev; } ;
struct resource {int /*<<< orphan*/  flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/ * dma_mask; struct TYPE_7__* parent; struct musb_hdrc_platform_data* platform_data; struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; TYPE_1__* resource; } ;
struct musb_hdrc_platform_data {int /*<<< orphan*/ * config; int /*<<< orphan*/ * platform_ops; } ;
struct device_node {int dummy; } ;
struct clk {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct resource*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct musb_hdrc_platform_data* dev_get_platdata (TYPE_2__*) ; 
 struct clk* devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 struct ux500_glue* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct resource*,int,int) ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_data (struct platform_device*,struct musb_hdrc_platform_data*,int) ; 
 int platform_device_add_resources (struct platform_device*,struct resource*,int) ; 
 struct platform_device* platform_device_alloc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ux500_glue*) ; 
 int /*<<< orphan*/  ux500_musb_hdrc_config ; 
 struct musb_hdrc_platform_data* ux500_of_probe (struct platform_device*,struct device_node*) ; 
 int /*<<< orphan*/  ux500_ops ; 

__attribute__((used)) static int ux500_probe(struct platform_device *pdev)
{
	struct resource musb_resources[2];
	struct musb_hdrc_platform_data	*pdata = dev_get_platdata(&pdev->dev);
	struct device_node		*np = pdev->dev.of_node;
	struct platform_device		*musb;
	struct ux500_glue		*glue;
	struct clk			*clk;
	int				ret = -ENOMEM;

	if (!pdata) {
		if (np) {
			pdata = ux500_of_probe(pdev, np);
			if (!pdata)
				goto err0;

			pdev->dev.platform_data = pdata;
		} else {
			dev_err(&pdev->dev, "no pdata or device tree found\n");
			goto err0;
		}
	}

	glue = devm_kzalloc(&pdev->dev, sizeof(*glue), GFP_KERNEL);
	if (!glue)
		goto err0;

	musb = platform_device_alloc("musb-hdrc", PLATFORM_DEVID_AUTO);
	if (!musb) {
		dev_err(&pdev->dev, "failed to allocate musb device\n");
		goto err0;
	}

	clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(clk)) {
		dev_err(&pdev->dev, "failed to get clock\n");
		ret = PTR_ERR(clk);
		goto err1;
	}

	ret = clk_prepare_enable(clk);
	if (ret) {
		dev_err(&pdev->dev, "failed to enable clock\n");
		goto err1;
	}

	musb->dev.parent		= &pdev->dev;
	musb->dev.dma_mask		= &pdev->dev.coherent_dma_mask;
	musb->dev.coherent_dma_mask	= pdev->dev.coherent_dma_mask;

	glue->dev			= &pdev->dev;
	glue->musb			= musb;
	glue->clk			= clk;

	pdata->platform_ops		= &ux500_ops;
	pdata->config 			= &ux500_musb_hdrc_config;

	platform_set_drvdata(pdev, glue);

	memset(musb_resources, 0x00, sizeof(*musb_resources) *
			ARRAY_SIZE(musb_resources));

	musb_resources[0].name = pdev->resource[0].name;
	musb_resources[0].start = pdev->resource[0].start;
	musb_resources[0].end = pdev->resource[0].end;
	musb_resources[0].flags = pdev->resource[0].flags;

	musb_resources[1].name = pdev->resource[1].name;
	musb_resources[1].start = pdev->resource[1].start;
	musb_resources[1].end = pdev->resource[1].end;
	musb_resources[1].flags = pdev->resource[1].flags;

	ret = platform_device_add_resources(musb, musb_resources,
			ARRAY_SIZE(musb_resources));
	if (ret) {
		dev_err(&pdev->dev, "failed to add resources\n");
		goto err2;
	}

	ret = platform_device_add_data(musb, pdata, sizeof(*pdata));
	if (ret) {
		dev_err(&pdev->dev, "failed to add platform_data\n");
		goto err2;
	}

	ret = platform_device_add(musb);
	if (ret) {
		dev_err(&pdev->dev, "failed to register musb device\n");
		goto err2;
	}

	return 0;

err2:
	clk_disable_unprepare(clk);

err1:
	platform_device_put(musb);

err0:
	return ret;
}