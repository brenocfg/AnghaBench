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
struct device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  num_resources; int /*<<< orphan*/  resource; struct device dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct ci_hdrc_usb2_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  ci_pdev; } ;
struct ci_hdrc_platform_data {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct ci_hdrc_platform_data ci_default_pdata ; 
 int /*<<< orphan*/  ci_hdrc_add_device (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ci_hdrc_platform_data*) ; 
 int /*<<< orphan*/  ci_hdrc_usb2_of_match ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct ci_hdrc_platform_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct ci_hdrc_platform_data* devm_kmalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct ci_hdrc_usb2_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ci_hdrc_usb2_priv*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_no_callbacks (struct device*) ; 

__attribute__((used)) static int ci_hdrc_usb2_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ci_hdrc_usb2_priv *priv;
	struct ci_hdrc_platform_data *ci_pdata = dev_get_platdata(dev);
	int ret;
	const struct of_device_id *match;

	if (!ci_pdata) {
		ci_pdata = devm_kmalloc(dev, sizeof(*ci_pdata), GFP_KERNEL);
		if (!ci_pdata)
			return -ENOMEM;
		*ci_pdata = ci_default_pdata;	/* struct copy */
	}

	match = of_match_device(ci_hdrc_usb2_of_match, &pdev->dev);
	if (match && match->data) {
		/* struct copy */
		*ci_pdata = *(struct ci_hdrc_platform_data *)match->data;
	}

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->clk = devm_clk_get(dev, NULL);
	if (!IS_ERR(priv->clk)) {
		ret = clk_prepare_enable(priv->clk);
		if (ret) {
			dev_err(dev, "failed to enable the clock: %d\n", ret);
			return ret;
		}
	}

	ci_pdata->name = dev_name(dev);

	priv->ci_pdev = ci_hdrc_add_device(dev, pdev->resource,
					   pdev->num_resources, ci_pdata);
	if (IS_ERR(priv->ci_pdev)) {
		ret = PTR_ERR(priv->ci_pdev);
		if (ret != -EPROBE_DEFER)
			dev_err(dev,
				"failed to register ci_hdrc platform device: %d\n",
				ret);
		goto clk_err;
	}

	platform_set_drvdata(pdev, priv);

	pm_runtime_no_callbacks(dev);
	pm_runtime_enable(dev);

	return 0;

clk_err:
	if (!IS_ERR(priv->clk))
		clk_disable_unprepare(priv->clk);
	return ret;
}