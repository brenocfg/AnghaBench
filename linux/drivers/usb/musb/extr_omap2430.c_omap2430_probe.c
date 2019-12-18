#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int /*<<< orphan*/  flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/ * dma_mask; struct TYPE_9__* parent; struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; TYPE_1__* resource; } ;
struct omap_musb_board_data {int /*<<< orphan*/  interface_type; } ;
struct omap2430_glue {TYPE_2__* dev; int /*<<< orphan*/  omap_musb_mailbox_work; TYPE_2__* control_otghs; int /*<<< orphan*/  status; struct platform_device* musb; } ;
struct musb_hdrc_platform_data {int /*<<< orphan*/ * platform_ops; struct musb_hdrc_config* config; struct omap_musb_board_data* board_data; int /*<<< orphan*/  power; int /*<<< orphan*/  mode; } ;
struct musb_hdrc_config {int multipoint; int /*<<< orphan*/  ram_bits; int /*<<< orphan*/  num_eps; } ;
struct device_node {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct resource*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 TYPE_2__* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB_UNKNOWN ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 struct omap2430_glue* _glue ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct musb_hdrc_platform_data* dev_get_platdata (TYPE_2__*) ; 
 void* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct resource*,int,int) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  omap2430_dmamask ; 
 int /*<<< orphan*/  omap2430_ops ; 
 int /*<<< orphan*/  omap_musb_mailbox_work ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_data (struct platform_device*,struct musb_hdrc_platform_data*,int) ; 
 int platform_device_add_resources (struct platform_device*,struct resource*,int) ; 
 struct platform_device* platform_device_alloc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct omap2430_glue*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 

__attribute__((used)) static int omap2430_probe(struct platform_device *pdev)
{
	struct resource			musb_resources[3];
	struct musb_hdrc_platform_data	*pdata = dev_get_platdata(&pdev->dev);
	struct omap_musb_board_data	*data;
	struct platform_device		*musb;
	struct omap2430_glue		*glue;
	struct device_node		*np = pdev->dev.of_node;
	struct musb_hdrc_config		*config;
	struct device_node		*control_node;
	struct platform_device		*control_pdev;
	int				ret = -ENOMEM, val;

	if (!np)
		return -ENODEV;

	glue = devm_kzalloc(&pdev->dev, sizeof(*glue), GFP_KERNEL);
	if (!glue)
		goto err0;

	musb = platform_device_alloc("musb-hdrc", PLATFORM_DEVID_AUTO);
	if (!musb) {
		dev_err(&pdev->dev, "failed to allocate musb device\n");
		goto err0;
	}

	musb->dev.parent		= &pdev->dev;
	musb->dev.dma_mask		= &omap2430_dmamask;
	musb->dev.coherent_dma_mask	= omap2430_dmamask;

	glue->dev			= &pdev->dev;
	glue->musb			= musb;
	glue->status			= MUSB_UNKNOWN;
	glue->control_otghs = ERR_PTR(-ENODEV);

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		goto err2;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		goto err2;

	config = devm_kzalloc(&pdev->dev, sizeof(*config), GFP_KERNEL);
	if (!config)
		goto err2;

	of_property_read_u32(np, "mode", (u32 *)&pdata->mode);
	of_property_read_u32(np, "interface-type",
			(u32 *)&data->interface_type);
	of_property_read_u32(np, "num-eps", (u32 *)&config->num_eps);
	of_property_read_u32(np, "ram-bits", (u32 *)&config->ram_bits);
	of_property_read_u32(np, "power", (u32 *)&pdata->power);

	ret = of_property_read_u32(np, "multipoint", &val);
	if (!ret && val)
		config->multipoint = true;

	pdata->board_data	= data;
	pdata->config		= config;

	control_node = of_parse_phandle(np, "ctrl-module", 0);
	if (control_node) {
		control_pdev = of_find_device_by_node(control_node);
		if (!control_pdev) {
			dev_err(&pdev->dev, "Failed to get control device\n");
			ret = -EINVAL;
			goto err2;
		}
		glue->control_otghs = &control_pdev->dev;
	}

	pdata->platform_ops		= &omap2430_ops;

	platform_set_drvdata(pdev, glue);

	/*
	 * REVISIT if we ever have two instances of the wrapper, we will be
	 * in big trouble
	 */
	_glue	= glue;

	INIT_WORK(&glue->omap_musb_mailbox_work, omap_musb_mailbox_work);

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

	musb_resources[2].name = pdev->resource[2].name;
	musb_resources[2].start = pdev->resource[2].start;
	musb_resources[2].end = pdev->resource[2].end;
	musb_resources[2].flags = pdev->resource[2].flags;

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

	pm_runtime_enable(glue->dev);

	ret = platform_device_add(musb);
	if (ret) {
		dev_err(&pdev->dev, "failed to register musb device\n");
		goto err3;
	}

	return 0;

err3:
	pm_runtime_disable(glue->dev);

err2:
	platform_device_put(musb);

err0:
	return ret;
}