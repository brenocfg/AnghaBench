#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct mxs_pinctrl_soc_data {int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; } ;
struct mxs_pinctrl_data {int /*<<< orphan*/  base; int /*<<< orphan*/  pctl; struct mxs_pinctrl_soc_data* soc; TYPE_2__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 struct mxs_pinctrl_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 TYPE_1__ mxs_pinctrl_desc ; 
 int mxs_pinctrl_probe_dt (struct platform_device*,struct mxs_pinctrl_data*) ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinctrl_register (TYPE_1__*,TYPE_2__*,struct mxs_pinctrl_data*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mxs_pinctrl_data*) ; 

int mxs_pinctrl_probe(struct platform_device *pdev,
		      struct mxs_pinctrl_soc_data *soc)
{
	struct device_node *np = pdev->dev.of_node;
	struct mxs_pinctrl_data *d;
	int ret;

	d = devm_kzalloc(&pdev->dev, sizeof(*d), GFP_KERNEL);
	if (!d)
		return -ENOMEM;

	d->dev = &pdev->dev;
	d->soc = soc;

	d->base = of_iomap(np, 0);
	if (!d->base)
		return -EADDRNOTAVAIL;

	mxs_pinctrl_desc.pins = d->soc->pins;
	mxs_pinctrl_desc.npins = d->soc->npins;
	mxs_pinctrl_desc.name = dev_name(&pdev->dev);

	platform_set_drvdata(pdev, d);

	ret = mxs_pinctrl_probe_dt(pdev, d);
	if (ret) {
		dev_err(&pdev->dev, "dt probe failed: %d\n", ret);
		goto err;
	}

	d->pctl = pinctrl_register(&mxs_pinctrl_desc, &pdev->dev, d);
	if (IS_ERR(d->pctl)) {
		dev_err(&pdev->dev, "Couldn't register MXS pinctrl driver\n");
		ret = PTR_ERR(d->pctl);
		goto err;
	}

	return 0;

err:
	iounmap(d->base);
	return ret;
}