#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; int /*<<< orphan*/ * confops; int /*<<< orphan*/ * pctlops; int /*<<< orphan*/  name; } ;
struct da850_pupd_data {int /*<<< orphan*/  pinctrl; TYPE_1__ desc; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  da850_pupd_confops ; 
 int /*<<< orphan*/  da850_pupd_pctlops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct da850_pupd_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (struct device*,TYPE_1__*,struct da850_pupd_data*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct da850_pupd_data*) ; 

__attribute__((used)) static int da850_pupd_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct da850_pupd_data *data;
	struct resource *res;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	data->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(data->base)) {
		dev_err(dev, "Could not map resource\n");
		return PTR_ERR(data->base);
	}

	data->desc.name = dev_name(dev);
	data->desc.pctlops = &da850_pupd_pctlops;
	data->desc.confops = &da850_pupd_confops;
	data->desc.owner = THIS_MODULE;

	data->pinctrl = devm_pinctrl_register(dev, &data->desc, data);
	if (IS_ERR(data->pinctrl)) {
		dev_err(dev, "Failed to register pinctrl\n");
		return PTR_ERR(data->pinctrl);
	}

	platform_set_drvdata(pdev, data);

	return 0;
}