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
struct replicator_drvdata {struct coresight_platform_data* atclk; struct coresight_platform_data* csdev; struct device* dev; } ;
struct device {struct coresight_platform_data* platform_data; struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct coresight_platform_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  link_subtype; } ;
struct coresight_desc {struct device* dev; struct coresight_platform_data* pdata; int /*<<< orphan*/ * ops; TYPE_1__ subtype; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORESIGHT_DEV_SUBTYPE_LINK_SPLIT ; 
 int /*<<< orphan*/  CORESIGHT_DEV_TYPE_LINK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct coresight_platform_data*) ; 
 int PTR_ERR (struct coresight_platform_data*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct coresight_platform_data*) ; 
 int clk_prepare_enable (struct coresight_platform_data*) ; 
 struct coresight_platform_data* coresight_register (struct coresight_desc*) ; 
 struct coresight_platform_data* devm_clk_get (struct device*,char*) ; 
 struct replicator_drvdata* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct coresight_platform_data* of_get_coresight_platform_data (struct device*,struct device_node*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct replicator_drvdata*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  replicator_cs_ops ; 

__attribute__((used)) static int replicator_probe(struct platform_device *pdev)
{
	int ret;
	struct device *dev = &pdev->dev;
	struct coresight_platform_data *pdata = NULL;
	struct replicator_drvdata *drvdata;
	struct coresight_desc desc = { 0 };
	struct device_node *np = pdev->dev.of_node;

	if (np) {
		pdata = of_get_coresight_platform_data(dev, np);
		if (IS_ERR(pdata))
			return PTR_ERR(pdata);
		pdev->dev.platform_data = pdata;
	}

	drvdata = devm_kzalloc(dev, sizeof(*drvdata), GFP_KERNEL);
	if (!drvdata)
		return -ENOMEM;

	drvdata->dev = &pdev->dev;
	drvdata->atclk = devm_clk_get(&pdev->dev, "atclk"); /* optional */
	if (!IS_ERR(drvdata->atclk)) {
		ret = clk_prepare_enable(drvdata->atclk);
		if (ret)
			return ret;
	}
	pm_runtime_get_noresume(&pdev->dev);
	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);
	platform_set_drvdata(pdev, drvdata);

	desc.type = CORESIGHT_DEV_TYPE_LINK;
	desc.subtype.link_subtype = CORESIGHT_DEV_SUBTYPE_LINK_SPLIT;
	desc.ops = &replicator_cs_ops;
	desc.pdata = pdev->dev.platform_data;
	desc.dev = &pdev->dev;
	drvdata->csdev = coresight_register(&desc);
	if (IS_ERR(drvdata->csdev)) {
		ret = PTR_ERR(drvdata->csdev);
		goto out_disable_pm;
	}

	pm_runtime_put(&pdev->dev);

	return 0;

out_disable_pm:
	if (!IS_ERR(drvdata->atclk))
		clk_disable_unprepare(drvdata->atclk);
	pm_runtime_put_noidle(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	return ret;
}