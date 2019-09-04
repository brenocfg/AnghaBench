#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct priv {int /*<<< orphan*/  bus; int /*<<< orphan*/  base; TYPE_1__* mem; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int chameleon_parse_cells (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct resource* devm_request_mem_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcb_alloc_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcb_bus_add_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcb_release_bus (int /*<<< orphan*/ ) ; 
 TYPE_1__* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct priv*) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 

__attribute__((used)) static int mcb_lpc_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct priv *priv;
	int ret = 0;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!priv->mem) {
		dev_err(&pdev->dev, "No Memory resource\n");
		return -ENODEV;
	}

	res = devm_request_mem_region(&pdev->dev, priv->mem->start,
				      resource_size(priv->mem),
				      KBUILD_MODNAME);
	if (!res) {
		dev_err(&pdev->dev, "Failed to request IO memory\n");
		return -EBUSY;
	}

	priv->base = devm_ioremap(&pdev->dev, priv->mem->start,
				  resource_size(priv->mem));
	if (!priv->base) {
		dev_err(&pdev->dev, "Cannot ioremap\n");
		return -ENOMEM;
	}

	platform_set_drvdata(pdev, priv);

	priv->bus = mcb_alloc_bus(&pdev->dev);
	if (IS_ERR(priv->bus))
		return PTR_ERR(priv->bus);

	ret = chameleon_parse_cells(priv->bus, priv->mem->start, priv->base);
	if (ret < 0) {
		mcb_release_bus(priv->bus);
		return ret;
	}

	dev_dbg(&pdev->dev, "Found %d cells\n", ret);

	mcb_bus_add_devices(priv->bus);

	return 0;

}