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
struct resource {int dummy; } ;
struct private_data {void* imem; void* dmem; void* regs; int /*<<< orphan*/  lock; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct platform_device {struct device dev; } ;
struct init_data {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int brcmstb_dpfe_download_firmware (struct platform_device*,struct init_data*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct private_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpfe_groups ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct private_data*) ; 
 int sysfs_create_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmstb_dpfe_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct private_data *priv;
	struct init_data init;
	struct resource *res;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	mutex_init(&priv->lock);
	platform_set_drvdata(pdev, priv);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dpfe-cpu");
	priv->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->regs)) {
		dev_err(dev, "couldn't map DCPU registers\n");
		return -ENODEV;
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dpfe-dmem");
	priv->dmem = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->dmem)) {
		dev_err(dev, "Couldn't map DCPU data memory\n");
		return -ENOENT;
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dpfe-imem");
	priv->imem = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->imem)) {
		dev_err(dev, "Couldn't map DCPU instruction memory\n");
		return -ENOENT;
	}

	ret = brcmstb_dpfe_download_firmware(pdev, &init);
	if (ret)
		return ret;

	ret = sysfs_create_groups(&pdev->dev.kobj, dpfe_groups);
	if (!ret)
		dev_info(dev, "registered.\n");

	return ret;
}