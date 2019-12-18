#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct mux_control {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  np; TYPE_1__* ctlr; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ops; struct device* dev; } ;
struct am654_hbmc_priv {struct mux_control* mux_ctrl; TYPE_2__ hbdev; TYPE_1__ ctlr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mux_control*) ; 
 int PTR_ERR (struct mux_control*) ; 
 int /*<<< orphan*/  am654_hbmc_ops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct am654_hbmc_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct mux_control* devm_mux_control_get (struct device*,int /*<<< orphan*/ *) ; 
 int hyperbus_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  mux_control_deselect (struct mux_control*) ; 
 int mux_control_select (struct mux_control*,int) ; 
 int /*<<< orphan*/  of_get_next_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct am654_hbmc_priv*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 

__attribute__((used)) static int am654_hbmc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct am654_hbmc_priv *priv;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	platform_set_drvdata(pdev, priv);

	if (of_property_read_bool(dev->of_node, "mux-controls")) {
		struct mux_control *control = devm_mux_control_get(dev, NULL);

		if (IS_ERR(control))
			return PTR_ERR(control);

		ret = mux_control_select(control, 1);
		if (ret) {
			dev_err(dev, "Failed to select HBMC mux\n");
			return ret;
		}
		priv->mux_ctrl = control;
	}

	pm_runtime_enable(dev);
	ret = pm_runtime_get_sync(dev);
	if (ret < 0) {
		pm_runtime_put_noidle(dev);
		goto disable_pm;
	}

	priv->ctlr.dev = dev;
	priv->ctlr.ops = &am654_hbmc_ops;
	priv->hbdev.ctlr = &priv->ctlr;
	priv->hbdev.np = of_get_next_child(dev->of_node, NULL);
	ret = hyperbus_register_device(&priv->hbdev);
	if (ret) {
		dev_err(dev, "failed to register controller\n");
		pm_runtime_put_sync(&pdev->dev);
		goto disable_pm;
	}

	return 0;
disable_pm:
	pm_runtime_disable(dev);
	if (priv->mux_ctrl)
		mux_control_deselect(priv->mux_ctrl);
	return ret;
}